//---------------------------------------------------------------------------
// Exemplo 03: player.hpp
//---------------------------------------------------------------------------
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "raylib.h"
// Definição da classe Player
class Player {
public:
// Construtor: carrega a textura e define a posição inicial do player
Player();
// Destrutor: descarrega a textura do player
~Player();
// Método para desenhar o player na tela
void Draw() const;
// Método para atualizar o player
void Update(float deltaTime);
// Método que verifica se o player colidiu com as bordas da tela
void CheckScreenLimits();
private:
Texture2D texture; // Textura do player
Vector2 position; // Posição do player na tela
float speed;
// Velocidade de movimentação do player
};
#endif // PLAYER_HPP