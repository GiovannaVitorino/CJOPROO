#ifndef PLAAYER_HPP
#define PLAAYER_HPP
#include "raylib.h"

class Player{
public:
    Player();
    void draw() const;
    void update(float deltaTime);
    void CheckScreenLimits(); //verifica se player colidiu com os limites da tela
private:
    Texture2D texture;
    Vector2 position;
    float speed;
}

#endif // PLAAYER_HPP