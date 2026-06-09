// ----------------------------------------------------------------------------
// Exemplo 03: programa06.cpp
// ----------------------------------------------------------------------------
#include "raylib.h"
#include "player.hpp"
#include "enemy.hpp"
#include <iostream>
#include <vector>
#include <memory> //unique_ptr


using namespace std;
// ----------------------------------------------------------------------------
// Variáveis globais
// ----------------------------------------------------------------------------
// Diretório da aplicação
const char *appDir = GetApplicationDirectory();
// ----------------------------------------------------------------------------
// Função principal
// ----------------------------------------------------------------------------
int main() {
// Define a janela da aplicação
InitWindow(800, 600, "Programa 06 - B");
// Delta time
float deltaTime;
// Framerate
SetTargetFPS(60);
// Instanciamento do player
Player player;
// ------------------------------------------------------------------------

cout << "\n >> Enemy count: " << Enemy::getEnemyCount() << "\n\n";

// Instancia de inimigo
Enemy enemy;


//Inform    Untoa inimigos foram criados
cout << "\n >> Enemy count: " << Enemy::getEnemyCount() << "\n\n";

vector<unique_ptr<Enemy>> enemies;


for (int i = 0; i < 5; i++)
{
    enemies.emplace_back(unique_ptr<Enemy>(new Enemy()));
}

cout << "\n >> Enemy count: " << Enemy::getEnemyCount() << "\n\n";



//-------------------------------------------------------------------------
// Game loop
while (!WindowShouldClose()) {
// Retorna o tempo em segundos que o último frame levou para ser processado
deltaTime = GetFrameTime();

// Atualiza o player
player.Update(deltaTime);

for (auto& enemy : enemies)
{
    enemy->Update(deltaTime);
}



// Início da renderização dos objetos do jogo
BeginDrawing();
// Define a cor de fundo
ClearBackground(BLACK);
// Renderiza o player
player.Draw();

for (auto& enemy : enemies)
{
    enemy->Draw();
}


DrawText(
    TextFormat("Enemies: %d", Enemy::getEnemyCount()),
    GetScreenWidth() - 130.f,
    20.0f,
    22,
    WHITE
);
// Fim da renderização dos objetos do jogo
EndDrawing();
}
// ------------------------------------------------------------------------
// Fecha a janela e limpa recursos do Raylib
CloseWindow();
return 0;
}
