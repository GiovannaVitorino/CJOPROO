#pragma once
#include "note.hpp"
#include "exercise.hpp"
#include "clef.hpp"
#include "interfaces.hpp"
#include <vector>
#include <memory>

// Define medidas e posicao base de uma pauta.
struct StaffLayout {
    Vector2 origin;
    float   lineSpacing   = 14.0f;
    float   measureWidth  = 200.0f;
    float   margin        = 24.0f;
};

// Responsavel por transformar exercicios musicais em desenho na tela.
class ScoreRenderer : public IRenderable {
    // Layout, fonte, texturas e estado de destaque usados no desenho.
    StaffLayout          layout;
    Font&                font_;

    // --- Texturas de claves e compasso ---
    Texture2D            claveSol{};
    Texture2D            claveFa{};
    Texture2D            formulaCompasso{};

    // --- Texturas de figuras ritmicas (notas) ---
    Texture2D            semibreve{};        // semibreve.png
    Texture2D            minima{};          // minima.png
    Texture2D            seminima{};       // seminima.png
    Texture2D            colcheia{};        // colcheia.png

    // --- Texturas de pausas ---
    Texture2D            pausaSemibreve{};        // pausaSemibreve.png
    Texture2D            pausaMinima{};          // pausaSeminim.png
    Texture2D            pausaSeminima{};       // pausaColcheia.png

    std::vector<int>     highlighted_; // indices de notas destacadas
    Color                highlightColor_ = YELLOW;

    // --- Metodos privados de desenho ---
    void drawStaff(float x, float width) const;
    void drawClef(ClefType clef, float x) const;
    void drawLedgerLines(const Note& n, float x, ClefType clef) const;
    void drawNoteHead(const Note& n, float x, float y) const;
    void drawRest(NoteValue dur, float x, float y) const;
    void drawDot(float x, float y) const;
    void drawStem(float x, float y, bool up) const;
    void drawFlag(NoteValue dur, float x, float y, bool up) const;
    void drawAccidental(Accidental acc, float x, float y) const;
    void drawTimeSignature(int num, int den, float x) const;
    void drawKeySignature(int key, const Clef& clef, float x) const;

    // Retorna true se a duracao possui imagem propria carregada,
    // evitando que drawStem/drawFlag sejam chamados desnecessariamente.
    bool noteHasTexture(NoteValue dur) const {
        switch (dur) {
            case NoteValue::WHOLE:
                return semibreve.id != 0;
            case NoteValue::HALF:
            case NoteValue::DOTTED_HALF:
                return minima.id != 0;
            case NoteValue::QUARTER:
            case NoteValue::DOTTED_QUARTER:
                return seminima.id != 0;
            case NoteValue::EIGHTH:
            case NoteValue::DOTTED_EIGHTH:
                return colcheia.id != 0;
            default:
                return false;
        }
    }

    // Calcula se a haste vai para cima ou para baixo.
    bool stemUp(int midiPitch) const {
        return midiPitch < 71; // B4 — notas abaixo tem haste para cima
    }

public:
    // Fonte padrao reaproveitada quando um renderizador temporario e criado.
    static Font& defaultFont() {
        static Font font = GetFontDefault();
        return font;
    }

    // Textura padrao da clave de Sol.
    static Texture2D defaultTrebleClefTexture() {
        static Texture2D texture = LoadTexture("assets/images/ClaveSol.png");
        return texture;
    }

    // Textura padrao da clave de Fa.
    static Texture2D defaultbassClefTexture() {
        static Texture2D texture = LoadTexture("assets/images/ClaveFa.png");
        return texture;
    }

    // Textura padrao do simbolo de compasso 4/4.
    static Texture2D defaultCommonTimeTexture() {
        static Texture2D texture = LoadTexture("assets/images/CompassoQuaternario.png");
        return texture;
    }

    // Construtor principal usado pelo GameManager com todos os recursos ja carregados.
    ScoreRenderer(Font& font,
                  StaffLayout layout,
                  Texture2D trebleClefTexture,
                  Texture2D bassClefTexture,
                  Texture2D commonTimeTexture,
                  Texture2D wholeNoteTexture,
                  Texture2D halfNoteTexture,
                  Texture2D quarterNoteTexture,
                  Texture2D eighthNoteTexture,
                  Texture2D pauseWholeTexture,
                  Texture2D pauseHalfTexture,
                  Texture2D pauseQuarterTexture)
        : layout(layout),
          font_(font),
          claveSol(trebleClefTexture),
          claveFa(bassClefTexture),
          formulaCompasso(commonTimeTexture),
          semibreve(wholeNoteTexture),
          minima(halfNoteTexture),
          seminima(quarterNoteTexture),
          colcheia(eighthNoteTexture),
          pausaSemibreve(pauseWholeTexture),
          pausaMinima(pauseHalfTexture),
          pausaSeminima(pauseQuarterTexture) {}

    // Construtor simplificado: carrega apenas claves e compasso (figuras ficam como primitivas).
    explicit ScoreRenderer(StaffLayout layout)
        : layout(layout),
          font_(defaultFont()),
          claveSol(defaultTrebleClefTexture()),
          claveFa(defaultbassClefTexture()),
          formulaCompasso(defaultCommonTimeTexture()) {}

    // --- Interface publica ---
    void render() const override {} // render geral (nao usado diretamente)

    // Desenha um exercicio completo na pauta.
    void drawExercise(const class Exercise& ex, float xOffset = 0.0f) const;
    // Desenha uma unica nota em uma clave especifica.
    void drawSingleNote(const Note& n, float x, const Clef& clef) const;

    // Marca uma nota para receber destaque visual.
    void highlight(int noteIndex, Color color = YELLOW) {
        highlighted_.push_back(noteIndex);
        highlightColor_ = color;
    }
    // Remove todos os destaques antes de recalcular o destaque atual.
    void clearHighlights() { highlighted_.clear(); }

    // Converte posicao de mouse -> pitch MIDI
    int screenYToPitch(float y, const Clef& clef) const;
    int screenYToPitch(float y, ClefType clef) const;

    // Setters fluentes
    ScoreRenderer& setLineSpacing(float s) { layout.lineSpacing = s; return *this; }
    ScoreRenderer& setOrigin(Vector2 o)    { layout.origin = o;      return *this; }
};