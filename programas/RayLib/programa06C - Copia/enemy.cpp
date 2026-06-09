// ----------------------------------------------------------------------------
// Exemplo 03: player.cpp
// ----------------------------------------------------------------------------
#include "enemy.hpp"
// Diretório da aplicação
extern char *appDir;



//define e inciializa o atributo estático, dentro de um escopo global
//Neste caso, não utilizamos a palavra reservada 'static'
unsigned int Enemy::enemyCount = 0;

//Métoso estatico, que retorna o total de inimigos que forM INSTANCIADOS
//nESTE CASO, NÃO UTILIZAMOS A Papalvra reservada 'staic'
unsigned int Enemy::getEnemyCount(){
    return enemyCount;
}

Enemy::Enemy() {

    //incrementa o total de inimigos
    ++enemyCount;
// Carrega a textura do player
texture = LoadTexture(TextFormat("%s/assets/images/enemy.png", appDir));
// Posição inicial do jogador
position.x = GetRandomValue(0, GetScreenWidth() - texture.width);
position.y = GetRandomValue(- texture.height, - texture.height - 200);
// Define a velocidade de movimentação do player
speed = GetRandomValue(20, 140) * 1.0f;
}
// ----------------------------------------------------------------------------
// Destrutor: descarrega a textura do player
Enemy::~Enemy() {

--enemyCount;
// Libera os recursos utilizados pela textura do player
UnloadTexture(texture);
}
// ----------------------------------------------------------------------------
// Método para desenhar o player na tela
void Enemy::Draw() const {
// Renderiza a imagem da player na posição correta
DrawTexture(texture, position.x, position.y, RAYWHITE);
}
// ----------------------------------------------------------------------------
// Método para atualizar o player
void Enemy::Update(float deltaTime) {

    //movimenta o inimigo para baixo
    position.y += speed * deltaTime;

    //verifica se o inimigo atingiu o limite inferior da tela
    if (position.y > GetScreenHeight())
    {
        position.x = GetRandomValue(0, GetScreenWidth() - texture.width);
        position.y = GetRandomValue(- texture.height, - texture.height - 200);
    }
    

}
// ----------------------------------------------------------------------------

