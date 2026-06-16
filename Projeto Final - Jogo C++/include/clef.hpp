#pragma once
#include "raylib.h"
#include "interfaces.hpp"
#include <string>

class Note; // forward declaration

// Base abstrata para claves: sabe desenhar o simbolo e converter notas em Y.
class Clef : public IRenderable {
public:
    // Converte pitch MIDI → posição Y na pauta (em pixels, relativo ao topo da pauta)
    virtual float   noteToY(int midiPitch, float lineSpacing) const;
    // Pitch da nota na 1ª linha da pauta (mais baixa)
    virtual int     referenceNote() const = 0;
    virtual std::string name() const = 0;
    // Codepoint Unicode SMuFL do símbolo
    virtual int     glyphCodepoint() const = 0;

    void render() const override; // desenha o símbolo na pauta

protected:
    // Dados visuais usados por render() para posicionar o simbolo da clave.
    Vector2 position_; // onde será desenhado
    Font&   font_;
    float   lineSpacing_;

public:
    // Recebe posicao, fonte e espacamento da pauta usados pela renderizacao.
    Clef(Vector2 pos, Font& font, float lineSpacing) : position_(pos), font_(font), lineSpacing_(lineSpacing) {}
};