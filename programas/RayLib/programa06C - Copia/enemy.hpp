// ----------------------------------------------------------------------------
// Exemplo 03: Enemy.hpp
// ----------------------------------------------------------------------------
#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "raylib.h"
// Definição da classe Player
class Enemy {
public:
// Construtor: carrega a textura e define a posição inicial do player
Enemy();
// Destrutor: descarrega a textura do player
~Enemy();
// Método para desenhar o player na tela
void Draw() const;
// Método para atualizar o player
void Update(float deltaTime);
//Método estático, utilizado para obter o total de instancias do inimigo
static unsigned int getEnemyCount();
private:
Texture2D texture; // Textura do player
Vector2 position; // Posição do player na tela
float speed; // Velocidade de movimentação do player

//Atributo estático, utilizado para obter o total de instancias do inimigo
static unsigned int enemyCount;

};
#endif
