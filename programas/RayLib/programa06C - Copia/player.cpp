// ----------------------------------------------------------------------------
// Exemplo 03: player.cpp
// ----------------------------------------------------------------------------
#include "player.hpp"
// Diretório da aplicação
extern char *appDir;
// ----------------------------------------------------------------------------
// Construtor: carrega a textura e define a posição inicial do player
Player::Player() {
// Carrega a textura do player
texture = LoadTexture(TextFormat("%s/assets/images/player.png", appDir));
// Posição inicial do jogador
position.x = (GetScreenWidth() - texture.width) / 2.0f;
position.y = GetScreenHeight() - texture.height - 10.0f;
// Define a velocidade de movimentação do player
speed = 150.0f;
}
// ----------------------------------------------------------------------------
// Destrutor: descarrega a textura do player
Player::~Player() {
// Libera os recursos utilizados pela textura do player
UnloadTexture(texture);
}
// ----------------------------------------------------------------------------
// Método para desenhar o player na tela
void Player::Draw() const {
// Renderiza a imagem da player na posição correta
DrawTexture(texture, position.x, position.y, RAYWHITE);
}
// ----------------------------------------------------------------------------
// Método para atualizar o player
void Player::Update(float deltaTime) {
// Movimenta o player para a direita
if (IsKeyDown(KEY_RIGHT)) {
position.x += speed * deltaTime;
}
// Movimenta o player para a esquerda
if (IsKeyDown(KEY_LEFT)) {
position.x -= speed * deltaTime;
}
// Movimenta o player para cima
if (IsKeyDown(KEY_UP)) {
position.y -= speed * deltaTime;
}

// Movimenta o player para baixo
if (IsKeyDown(KEY_DOWN)) {
position.y += speed * deltaTime;
}
// Verifica se o player atingiu os limites da tela
CheckScreenLimits();
}
// ----------------------------------------------------------------------------
// Método que verifica se o player colidiu com as bordas da tela
void Player::CheckScreenLimits() {
// Verifica se o player colidiu com o lado esquerdo
if (position.x <= 0) {
position.x = 0;
}
// Verifica se o player colidiu com o lado direito
if (position.x + texture.width >= GetScreenWidth()) {
position.x = GetScreenWidth() - texture.width;
}
// Verifica se o player colidiu com o topo
if (position.y <= 0) {
position.y = 0;
}
// Verifica se o player colidiu com a base
if (position.y + texture.height >= GetScreenHeight()) {
position.y = GetScreenHeight() - texture.height;
}
}
