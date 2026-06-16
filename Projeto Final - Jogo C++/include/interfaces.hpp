#pragma once
#include "raylib.h"

// Tudo que pode ser desenhado
// Contrato usado por telas, modos e componentes visuais.
class IRenderable {
public:
    virtual void render() const = 0;
    virtual ~IRenderable() {}
};

// Tudo que tem lógica de frame
// Contrato para objetos que atualizam estado a cada frame.
class IUpdatable {
public:
    virtual void update(float dt) = 0;
    virtual ~IUpdatable() {}
};

// Qualquer coisa que emite som
// Contrato minimo para motores ou fontes de audio do jogo.
class IAudioSource {
public:
    virtual void play()  = 0;
    virtual void stop()  = 0;
    virtual bool isPlaying() const = 0;
    virtual ~IAudioSource() {}
};