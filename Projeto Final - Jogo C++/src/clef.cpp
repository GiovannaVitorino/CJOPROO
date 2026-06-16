#include "clef.hpp"
 
// Desenha o simbolo da clave na posicao configurada.
void Clef::render() const {
    DrawTextCodepoint(font_, glyphCodepoint(),
                      position_, lineSpacing_ * 4.0f, BLACK);
}
 
// Converte a altura MIDI em coordenada Y relativa ao topo da pauta.
float Clef::noteToY(int midiPitch, float lineSpacing) const {
    // Cada grau diatônico = lineSpacing/2 pixels
    // Fórmula: step = 2 * (midiPitch - referenceNote()) / 2  (aprox. cromático)
    float halfSteps = static_cast<float>(midiPitch - referenceNote());
    // 8 = número de half-steps até a borda superior da pauta
    return (8.0f - halfSteps * 0.5f) * (lineSpacing / 2.0f);
}
