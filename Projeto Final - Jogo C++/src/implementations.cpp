#include "audio_engine.hpp"
#include "game_manager.hpp"
#include "mode_read_name.hpp"
#include "score_renderer.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <string>

std::unique_ptr<GameManager> GameManager::instance;

// ============================================================
//  Utilitario interno: desenha textura com ancoragem personalizada
// ============================================================

// Desenha uma textura com altura targetHeight, centralizada horizontalmente em x,
// e com a coordenada y alinhada ao ponto de ancoragem vertical anchorY:
// - anchorY = 0.0f: topo da imagem em y
// - anchorY = 0.5f: centro da imagem em y (comportamento original)
// - anchorY = 1.0f: base da imagem em y
static void drawTextureAligned(Texture2D tex, float x, float y, float targetHeight, float anchorY, Color tint = WHITE) {
    if (tex.id == 0) return;
    float targetWidth = targetHeight * static_cast<float>(tex.width) / static_cast<float>(tex.height);
    float drawY = y - targetHeight * anchorY;
    Rectangle src{0.f, 0.f, static_cast<float>(tex.width), static_cast<float>(tex.height)};
    Rectangle dst{x - targetWidth * 0.5f, drawY,targetWidth, targetHeight};
    DrawTexturePro(tex, src, dst, {0.f, 0.f}, 0.f, tint);
}

// Versao antiga mantida para compatibilidade (centraliza pela ancora 0.5)
static void drawTextureCentered(Texture2D tex, float cx, float cy, float targetHeight, Color tint = WHITE) {
    drawTextureAligned(tex, cx, cy, targetHeight, 0.5f, tint);
}

// ============================================================
//  AudioEngine
// ============================================================

// Gera um som raylib em memoria carregando o arquivo .wav mais proximo
// ao pitch pedido e ajustando o pitch via SetSoundPitch.
Sound AudioEngine::generateTone(float freq, float durationSec) const {
    if (freq <= 0.0f) return generateRest(durationSec);

    // Recupera o pitch MIDI a partir da frequencia
    int midiPitch = static_cast<int>(std::round(69.0f + 12.0f * std::log2(freq / 440.0f)));

    static const char* names[7] = {"C","D","E","F","G","A","B"};
    static const int   semis[7] = {0,2,4,5,7,9,11};

    int pitchClass = ((midiPitch % 12) + 12) % 12;
    int octave     = midiPitch / 12 - 1;

    // Procura a nota natural mais proxima em semitons
    int bestIdx = 0, bestDiff = 99, bestAdj = 0;
    for (int i = 0; i < 7; ++i) {
        for (int adj = -1; adj <= 1; ++adj) {
            int diff = pitchClass - (semis[i] + adj * 12);
            if (std::abs(diff) < std::abs(bestDiff)) {
                bestDiff = diff; bestIdx = i; bestAdj = adj;
            }
        }
    }

    int sampleOctave = octave - bestAdj;
    sampleOctave = std::max(2, std::min(sampleOctave, 5));

    std::string path = "assets/sounds/" + std::string(names[bestIdx]) +
                       std::to_string(sampleOctave) + ".wav";
    Sound sound = LoadSound(path.c_str());

    float pitchRatio = std::pow(2.0f, static_cast<float>(bestDiff) / 12.0f);
    SetSoundPitch(sound, pitchRatio);
    SetSoundVolume(sound, masterVolume);
    return sound;
}

// Gera um buffer de silencio com a duracao pedida para representar pausas.
Sound AudioEngine::generateRest(float durationSec) const {
    int sampleCount = static_cast<int>(sampleRate_ * durationSec);
    if (sampleCount <= 0) sampleCount = 1;

    Wave wave{};
    wave.frameCount = static_cast<unsigned int>(sampleCount);
    wave.sampleRate = static_cast<unsigned int>(sampleRate_);
    wave.sampleSize = 16;
    wave.channels   = 1;
    wave.data       = std::calloc(sampleCount, sizeof(short));

    Sound sound = LoadSoundFromWave(wave);
    std::free(wave.data);
    return sound;
}

// ============================================================
//  Funcoes auxiliares estaticas de mapeamento musical
// ============================================================

// Converte uma classe de pitch cromatica para o indice da nota natural C..B.
static int naturalLetterIndex(int pitchClass) {
    switch ((pitchClass % 12 + 12) % 12) {
        case 0: case 1: return 0;  // C
        case 2: case 3: return 1;  // D
        case 4:         return 2;  // E
        case 5: case 6: return 3;  // F
        case 7: case 8: return 4;  // G
        case 9: case 10: return 5; // A
        case 11:         return 6; // B
        default:         return 0;
    }
}

// Transforma MIDI em uma numeracao diatonica continua por oitava.
static int diatonicNumber(int midiPitch) {
    int octave = midiPitch / 12 - 1;
    return octave * 7 + naturalLetterIndex(midiPitch);
}

// Faz o caminho inverso: numeracao diatonica para um MIDI natural.
static int midiFromDiatonicNumber(int diatonic) {
    static const int pitchClasses[] = {0, 2, 4, 5, 7, 9, 11};
    int octave = diatonic / 7;
    int letter = diatonic % 7;
    if (letter < 0) {
        letter += 7;
        --octave;
    }
    return (octave + 1) * 12 + pitchClasses[letter];
}

// Retorna a nota de referencia usada para ancorar cada clave na pauta.
static int clefAnchorPitch(ClefType clef) {
    switch (clef) {
        case ClefType::BASS:   return 53;   // F3 na 4a linha
        case ClefType::TREBLE:
        default:               return 67;   // G4 na 2a linha
    }
}

// Retorna o slot (contado de baixo) da nota de referencia na pauta.
static float clefAnchorSlot(ClefType clef) {
    switch (clef) {
        case ClefType::BASS:   return 6.0f; // 4a linha
        case ClefType::TREBLE:
        default:               return 2.0f; // 2a linha
    }
}

// Calcula em qual slot da pauta um MIDI deve aparecer para a clave.
static float noteSlotForClef(int midiPitch, ClefType clef) {
    int steps = diatonicNumber(midiPitch) - diatonicNumber(clefAnchorPitch(clef));
    return clefAnchorSlot(clef) + static_cast<float>(steps);
}

// Converte o numero de slot (de baixo para cima) em coordenada Y de tela.
static float staffYFromBottomSlot(float top, float lineSpacing, float slot) {
    float bottom = top + 4.0f * lineSpacing;
    return bottom - slot * (lineSpacing / 2.0f);
}

// ============================================================
//  ScoreRenderer — metodos de desenho
// ============================================================

// Desenha as cinco linhas horizontais da pauta.
void ScoreRenderer::drawStaff(float x, float width) const {
    for (int i = 0; i < 5; ++i) {
        float y = layout.origin.y + i * layout.lineSpacing;
        DrawLineEx({x, y}, {x + width, y}, 1.0f, BLACK);
    }
}

// Desenha a imagem da clave, redimensionando conforme o espaco entre linhas.
void ScoreRenderer::drawClef(ClefType clef, float x) const {
    float top = layout.origin.y;
    float ls = layout.lineSpacing;
    float bottom = top + 4.0f * ls;
    auto yForSlot = [&](float slot) {
        return bottom - slot * (ls / 2.0f);
    };

    const bool isBass = clef == ClefType::BASS;
    const Texture2D& texture = isBass ? claveFa : claveSol;
    if (texture.id == 0) return;

    const float targetHeight = isBass ? ls * 3.0f : ls * 5.5f;
    const float targetWidth  = targetHeight * static_cast<float>(texture.width) / static_cast<float>(texture.height);
    const float targetY = isBass ? yForSlot(5.5f) - targetHeight * 0.48f : yForSlot(3.0f) - targetHeight * 0.55f;

    Rectangle source{0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    Rectangle dest{x - targetWidth * 0.52f, targetY, targetWidth, targetHeight};
    DrawTexturePro(texture, source, dest, {0.0f, 0.0f}, 0.0f, WHITE);
}

// Desenha linhas suplementares para notas acima ou abaixo da pauta.
void ScoreRenderer::drawLedgerLines(const Note& n, float x, ClefType clef) const {
    float slot = noteSlotForClef(n.pitch(), clef);
    const float top = layout.origin.y;
    const float ls = layout.lineSpacing;
    const float width = 24.0f;

    if (slot < 0.0f) {
        int lowestEvenSlot = static_cast<int>(std::floor(slot / 2.0f)) * 2;
        for (int s = lowestEvenSlot; s <= -2; s += 2) {
            float y = staffYFromBottomSlot(top, ls, static_cast<float>(s));
            DrawLineEx({x - width * 0.5f, y}, {x + width * 0.5f, y}, 1.0f, BLACK);
        }
    } else if (slot > 8.0f) {
        int highestEvenSlot = static_cast<int>(std::ceil(slot / 2.0f)) * 2;
        for (int s = 10; s <= highestEvenSlot; s += 2) {
            float y = staffYFromBottomSlot(top, ls, static_cast<float>(s));
            DrawLineEx({x - width * 0.5f, y}, {x + width * 0.5f, y}, 1.0f, BLACK);
        }
    }
}

// Desenha a cabeca da nota — usa textura quando disponivel, primitiva como fallback.
// As notas cuja textura ja inclui haste e bandeirola (minima, seminima, colcheia)
// nao chamam drawStem/drawFlag; isso e controlado em drawExercise via noteHasTexture().
void ScoreRenderer::drawNoteHead(const Note& n, float x, float y) const {
    if (n.isRest()) return;
    float ls = layout.lineSpacing;

    // --- Semibreve ---
    if (n.duration() == NoteValue::WHOLE) {
        if (semibreve.id != 0) {
            // Semibreve: cabeca centralizada na imagem
            drawTextureAligned(semibreve, x, y, ls * 2.0f, 0.5f); 
            return;
        }
        // Fallback: elipse vazia
        DrawEllipse(static_cast<int>(x), static_cast<int>(y), 8.0f, 5.5f, BLACK);
        DrawEllipse(static_cast<int>(x), static_cast<int>(y), 4.5f, 2.8f, RAYWHITE);
        return;
    }

    // --- Minima (inclui minima pontuada) ---
    if (n.duration() == NoteValue::HALF || n.duration() == NoteValue::DOTTED_HALF) {
        if (minima.id != 0) {
            // Minima: cabeca a 35% do topo da imagem (a haste sobe)
            drawTextureAligned(minima, x, y, ls * 6.0f, 0.6f);
            return;
        }
        // Fallback: elipse vazia com haste
        DrawEllipse(static_cast<int>(x), static_cast<int>(y), 8.0f, 5.5f, BLACK);
        DrawEllipse(static_cast<int>(x), static_cast<int>(y), 4.5f, 2.8f, RAYWHITE);
        return;
    }

    // --- Seminima (inclui seminima pontuada) ---
    if (n.duration() == NoteValue::QUARTER || n.duration() == NoteValue::DOTTED_QUARTER) {
        if (seminima.id != 0) {
            // Seminima: cabeca a 35% do topo da imagem
            drawTextureAligned(seminima, x, y, ls * 4.5f, 0.75f);
            return;
        }
        // Fallback: elipse preenchida
        DrawEllipse(static_cast<int>(x), static_cast<int>(y), 8.0f, 5.5f, BLACK);
        return;
    }

    // eighth note = colcheia, dotted eighth = colcheia pontuada
    if (n.duration() == NoteValue::EIGHTH || n.duration() == NoteValue::DOTTED_EIGHTH) {
        if (colcheia.id != 0) {
            drawTextureAligned(colcheia, x, y, ls * 7.0f, 0.60f);
            return;
        }
        // Fallback: elipse preenchida
        DrawEllipse(static_cast<int>(x), static_cast<int>(y), 8.0f, 5.5f, BLACK);
        return;
    }

    // --- Semicolcheia e demais: apenas primitiva ---
    DrawEllipse(static_cast<int>(x), static_cast<int>(y), 8.0f, 5.5f, BLACK);
}

// Desenha o ponto de aumentacao ao lado da nota.
void ScoreRenderer::drawDot(float x, float y) const {
    DrawCircle(static_cast<int>(x + 14.0f), static_cast<int>(y - layout.lineSpacing * 0.25f), 2.5f, BLACK);
}

// Desenha o simbolo de pausa
void ScoreRenderer::drawRest(NoteValue dur, float x, float y) const {
    float ls = layout.lineSpacing;

    // --- Pausa de semibreve ---
    if (dur == NoteValue::WHOLE) {
        if (pausaSemibreve.id != 0) {
            drawTextureCentered(pausaSemibreve, x, y, ls * 1.2f);
            return;
        }
        // Fallback: retangulo pendurado na linha do meio
        DrawRectangle(static_cast<int>(x - 9.0f), static_cast<int>(y - ls),
                      18, static_cast<int>(ls * 0.6f), BLACK);
        return;
    }

    // --- Pausa de minima ---
    if (dur == NoteValue::HALF) {
        if (pausaMinima.id != 0) {
            drawTextureCentered(pausaMinima, x, y, ls * 1.2f);
            return;
        }
        DrawRectangle(static_cast<int>(x - 9.0f), static_cast<int>(y),
                      18, static_cast<int>(ls * 0.6f), BLACK);
        return;
    }

    // --- Pausa de seminima ---
    if (dur == NoteValue::QUARTER) {
        if (pausaSeminima.id != 0) {
            drawTextureCentered(pausaSeminima, x, y, ls * 3.0f);
            return;
        }
        // Fallback: zigue-zague
        DrawLineEx({x,      y - ls * 0.8f}, {x + 6.f, y - ls * 0.3f}, 2.0f, BLACK);
        DrawLineEx({x + 6.f,y - ls * 0.3f}, {x - 2.f, y + ls * 0.1f}, 2.0f, BLACK);
        DrawLineEx({x - 2.f,y + ls * 0.1f}, {x + 6.f, y + ls * 0.5f}, 2.0f, BLACK);
        DrawLineEx({x + 6.f,y + ls * 0.5f}, {x,       y + ls * 0.9f}, 2.0f, BLACK);
        return;
    }

    // --- Pausa de colcheia e colcheia pontuada ---
    if (dur == NoteValue::EIGHTH || dur == NoteValue::DOTTED_EIGHTH) {
        if (pausaSeminima.id != 0) {
            // Reutiliza a textura de pausa de seminima quando nao ha imagem especifica
            drawTextureCentered(pausaSeminima, x, y, ls * 3.0f);
            return;
        }
        DrawCircle(static_cast<int>(x), static_cast<int>(y + ls * 0.3f), ls * 0.28f, BLACK);
        DrawLineEx({x, y + ls * 0.3f}, {x + ls * 0.7f, y - ls * 0.5f}, 1.5f, BLACK);
        return;
    }

    // --- Semicolcheia ---
    if (dur == NoteValue::SIXTEENTH) {
        DrawCircle(static_cast<int>(x), static_cast<int>(y + ls * 0.3f), ls * 0.28f, BLACK);
        DrawCircle(static_cast<int>(x), static_cast<int>(y - ls * 0.3f), ls * 0.28f, BLACK);
        DrawLineEx({x, y + ls * 0.3f}, {x + ls * 0.7f, y - ls * 0.7f}, 1.5f, BLACK);
        return;
    }

    // Fallback generico
    DrawRectangle(static_cast<int>(x - 6.0f), static_cast<int>(y),
                  12, static_cast<int>(ls * 0.5f), GRAY);
}

// Desenha a haste da nota para cima ou para baixo.
void ScoreRenderer::drawStem(float x, float y, bool up) const {
    float stemLength = layout.lineSpacing * 3.5f;
    float endY  = up ? y - stemLength : y + stemLength;
    float stemX = up ? x + 7.0f : x - 7.0f;
    DrawLineEx({stemX, y}, {stemX, endY}, 1.5f, BLACK);
}

// Desenha a bandeirola para colcheias e semicolcheias.
void ScoreRenderer::drawFlag(NoteValue dur, float x, float y, bool up) const {
    if (dur != NoteValue::EIGHTH && dur != NoteValue::SIXTEENTH &&
        dur != NoteValue::DOTTED_EIGHTH) return;

    float stemLength = layout.lineSpacing * 3.5f;
    float stemX    = up ? x + 7.0f : x - 7.0f;
    float stemEndY = up ? y - stemLength : y + stemLength;
    float dir      = up ? 1.0f : -1.0f;

    Vector2 p0 = {stemX,         stemEndY};
    Vector2 p1 = {stemX + 12.0f, stemEndY + dir * 10.0f};
    Vector2 p2 = {stemX + 10.0f, stemEndY + dir * 20.0f};
    Vector2 p3 = {stemX + 14.0f, stemEndY + dir * 32.0f};
    DrawLineEx(p0, p1, 2.0f, BLACK);
    DrawLineEx(p1, p2, 2.0f, BLACK);
    DrawLineEx(p2, p3, 2.0f, BLACK);

    if (dur == NoteValue::SIXTEENTH || dur == NoteValue::DOTTED_EIGHTH) {
        float off = dir * 10.0f;
        DrawLineEx({p0.x, p0.y + off}, {p1.x, p1.y + off}, 2.0f, BLACK);
        DrawLineEx({p1.x, p1.y + off}, {p2.x, p2.y + off}, 2.0f, BLACK);
    }
}

// Desenha o acidente (sustenido, bemol, bequadro) antes da cabeca da nota.
void ScoreRenderer::drawAccidental(Accidental acc, float x, float y) const {
    const char* label = nullptr;
    switch (acc) {
        case Accidental::SHARP:   label = "#"; break;
        case Accidental::FLAT:    label = "b"; break;
        case Accidental::NATURAL: label = "n"; break;
        default: break;
    }
    if (!label) return;
    DrawText(label, static_cast<int>(x - 26.0f), static_cast<int>(y - 13.0f), 22, BLACK);
}

// Desenha o compasso; usa imagem para 4/4 e texto para outros casos.
void ScoreRenderer::drawTimeSignature(int num, int den, float x) const {
    if (num == 4 && den == 4 && formulaCompasso.id != 0) {
        float ls          = layout.lineSpacing;
        float targetHeight = ls * 4.7f;
        float targetWidth  = targetHeight * static_cast<float>(formulaCompasso.width) / static_cast<float>(formulaCompasso.height);
        Rectangle source{0.0f, 0.0f, static_cast<float>(formulaCompasso.width), static_cast<float>(formulaCompasso.height)};
        Rectangle dest{x - targetWidth * 0.15f,
                       layout.origin.y + 2.0f * ls - targetHeight * 0.50f,
                       targetWidth,
                       targetHeight};
        DrawTexturePro(formulaCompasso, source, dest, {0.0f, 0.0f}, 0.0f, WHITE);
        return;
    }
    DrawText(TextFormat("%d", num), static_cast<int>(x), static_cast<int>(layout.origin.y - 2), 18, BLACK);
    DrawText(TextFormat("%d", den), static_cast<int>(x),  static_cast<int>(layout.origin.y + 22), 18, BLACK);
}

// Reservado para armaduras de clave (nao implementado).
void ScoreRenderer::drawKeySignature(int, const Clef&, float) const {}

// Desenha uma partitura completa: pauta, clave, compasso, notas e barras de compasso.
void ScoreRenderer::drawExercise(const Exercise& ex, float xOffset) const {
    const float beatsPerMeasure = ex.timeSig.numerator * (4.0f / ex.timeSig.denominator);
    const float measureBeats    = beatsPerMeasure > 0.0f ? beatsPerMeasure : 4.0f;
    float totalBeats = 0.0f;
    int   totalNotes = 0;
    for (const auto& measure : ex.measures) {
        for (const auto& note : measure.notes) {
            totalBeats += note.durationInBeats();
            ++totalNotes;
        }
    }

    float x = layout.origin.x + xOffset;
    int   visualMeasureCount = std::max(1, static_cast<int>(std::ceil(totalBeats / measureBeats)));
    float noteAreaWidth = 124.0f + totalNotes * 42.0f +
                          visualMeasureCount * 20.0f + layout.margin;
    float width = std::max({layout.measureWidth * visualMeasureCount, noteAreaWidth, 600.0f});

    drawStaff(x, width);
    drawClef(ex.clef, x + 8.0f);
    drawTimeSignature(ex.timeSig.numerator, ex.timeSig.denominator, x + 54.0f);

    int   noteIndex       = 0;
    float noteX           = x + 124.0f;
    float accumulatedBeats = 0.0f;
    float nextBarBeat     = measureBeats;
    const float beatEpsilon = 0.001f;

    for (const auto& measure : ex.measures) {
        for (const auto& note : measure.notes) {
            float y = staffYFromBottomSlot(layout.origin.y, layout.lineSpacing,
                                           noteSlotForClef(note.pitch(), ex.clef));

            // Circulo de destaque (modo read-name)
            if (std::find(highlighted_.begin(), highlighted_.end(), noteIndex)
                != highlighted_.end()) {
                DrawCircle(static_cast<int>(noteX), static_cast<int>(y),
                           14.0f, Fade(highlightColor_, 0.35f));
            }

            drawLedgerLines(note, noteX, ex.clef);
            drawAccidental(note.accidental(), noteX, y);

            if (note.isRest()) {
                drawRest(note.duration(), noteX, y);
            } else {
                drawNoteHead(note, noteX, y);

                // Haste e bandeirola so sao desenhadas quando a nota NAO possui
                // imagem propria (que ja inclui esses elementos graficos).
                if (!noteHasTexture(note.duration())) {
                    if (note.duration() != NoteValue::WHOLE) {
                        bool up = stemUp(note.pitch());
                        drawStem(noteX, y, up);
                        drawFlag(note.duration(), noteX, y, up);
                    }
                }

                // Ponto de aumentacao (desenhado sempre que aplicavel)
                if (note.duration() == NoteValue::DOTTED_HALF    ||
                    note.duration() == NoteValue::DOTTED_QUARTER  ||
                    note.duration() == NoteValue::DOTTED_EIGHTH) {
                    drawDot(noteX, y);
                }
            }

            noteX += 42.0f;
            accumulatedBeats += note.durationInBeats();
            if (accumulatedBeats + beatEpsilon >= nextBarBeat) {
                DrawLineEx({noteX, layout.origin.y},
                           {noteX, layout.origin.y + 4.0f * layout.lineSpacing},
                           1.0f, BLACK);
                noteX      += 20.0f;
                nextBarBeat += measureBeats;
            }
            ++noteIndex;
        }
    }
}

// Desenha uma nota isolada usando a conversao vertical da clave recebida.
void ScoreRenderer::drawSingleNote(const Note& n, float x, const Clef& clef) const {
    float y = layout.origin.y + clef.noteToY(n.pitch(), layout.lineSpacing);
    drawAccidental(n.accidental(), x, y);
    if (n.isRest()) {
        drawRest(n.duration(), x, y);
    } else {
        drawNoteHead(n, x, y);
        if (!noteHasTexture(n.duration()) && n.duration() != NoteValue::WHOLE) {
            bool up = stemUp(n.pitch());
            drawStem(x, y, up);
            drawFlag(n.duration(), x, y, up);
        }
        if (n.duration() == NoteValue::DOTTED_HALF   ||
            n.duration() == NoteValue::DOTTED_QUARTER ||
            n.duration() == NoteValue::DOTTED_EIGHTH) {
            drawDot(x, y);
        }
    }
}

// Converte uma coordenada Y da tela em pitch usando uma instancia de Clef.
int ScoreRenderer::screenYToPitch(float y, const Clef& clef) const {
    float bottom = layout.origin.y + 4.0f * layout.lineSpacing;
    float slot   = (bottom - y) / (layout.lineSpacing / 2.0f);
    return clef.referenceNote() + static_cast<int>(std::round(slot)) * 2;
}

// Converte uma coordenada Y da tela em pitch usando apenas o tipo da clave.
int ScoreRenderer::screenYToPitch(float y, ClefType clef) const {
    float bottom = layout.origin.y + 4.0f * layout.lineSpacing;
    float slot   = (bottom - y) / (layout.lineSpacing / 2.0f);
    int steps    = static_cast<int>(std::round(slot - clefAnchorSlot(clef)));
    return midiFromDiatonicNumber(diatonicNumber(clefAnchorPitch(clef)) + steps);
}

// ============================================================
//  ReadAndName
// ============================================================

// Monta opcoes cromaticas de nomes de notas em solfejo.
void ReadAndName::buildChoices() {
    opcoes = {"Dó", "Dó#", "Réb", "Ré", "Ré#", "Mib",
                "Mi", "Fá", "Fá#", "Solb", "Sol", "Sol#",
                "Láb", "Lá", "Lá#", "Sib", "Si"};
}

// Calcula a area clicavel de cada botao de nome de nota.
Rectangle ReadAndName::getButtonRect(int i) const {
    const int   columns = 9;
    const float w = 72.0f;
    const float h = 34.0f;
    const float gap = 10.0f;
    return {40.0f + (i % columns) * (w + gap), 540.0f + (i / columns) * (h + gap), w, h};
}

// Calcula a area de botoes de clave deixados para extensao futura.
Rectangle ReadAndName::getClefButtonRect(int i) const {
    return {760.0f + i * 120.0f, 560.0f, 108.0f, 38.0f};
}

// Renderiza a partitura, os botoes de resposta, HUD e feedback.
void ReadAndName::render() const {
    DrawText("Nomeie a nota destacada", 40, 50, 22, DARKGRAY);
    renderer.drawExercise(exercicioAtual);
    for (int i = 0; i < static_cast<int>(opcoes.size()); ++i) {
        drawButton(opcoes[i].c_str(), getButtonRect(i), DARKBLUE);
    }
    drawHUD();
    drawFeedback();
}