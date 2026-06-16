#include "game_manager.hpp"
 
// Ponto de entrada do programa: prepara o gerenciador e inicia o jogo.
int main() {
    // GameManager centraliza estado, modos, audio, renderizacao e recursos.
    auto& game = GameManager::get();
    // Inicializa janela, texturas, audio, fabrica de exercicios e modos.
    game.init();
    // Executa o loop principal ate a janela ser fechada.
    game.run();
    // Retorno 0 indica encerramento normal.
    return 0;
}