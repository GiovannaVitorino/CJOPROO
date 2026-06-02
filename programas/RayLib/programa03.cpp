//---------------------------------------------------------------------------
// Exemplo 03: programa03.cpp
//---------------------------------------------------------------------------
#include "raylib.h"
#include "player.hpp"
//---------------------------------------------------------------------------
// Variáveis globais
//---------------------------------------------------------------------------
// Diretório da aplicação
const char *appDir = GetApplicationDirectory();
//---------------------------------------------------------------------------
// Função principal
//---------------------------------------------------------------------------
int main() {
// Define a janela da aplicação
InitWindow(800, 600, "Programa 03");
// Delta time
float deltaTime;
// Framerate
SetTargetFPS(60);
// Instanciamento do player
Player player;
//-----------------------------------------------------------------------
// Game loop
while (!WindowShouldClose()) {
// Retorna o tempo em segundos que o último frame levou para ser processado
deltaTime = GetFrameTime();
// Atualiza o player
player.Update(deltaTime);
// Início da renderização dos objetos do jogo
BeginDrawing();
// Define a cor de fundo
ClearBackground(BLACK);
// Renderiza o player
player.Draw();
// Fim da renderização dos objetos do jogo
EndDrawing();
}
//-----------------------------------------------------------------------
// Fecha a janela e limpa recursos do Raylib
CloseWindow();
return 0;
}