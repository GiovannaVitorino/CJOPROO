#include <iostream>
#include <vector>
//exemplo 07: enum com escopo


using namespace std;

enum class EstadoJogo{
    MenuPrincipal,
    Jogando,
    Pausado,
    GameOver
};

void mostrarEstado(EstadoJogo estado);

int main(void) {
    cout << endl;
    cout << "*Exemplo de enumeracoes\n\n";

    EstadoJogo estadoAtual = EstadoJogo::MenuPrincipal;
    mostrarEstado(estadoAtual);

    estadoAtual = EstadoJogo::Jogando;
    mostrarEstado(estadoAtual);

    estadoAtual = EstadoJogo::Pausado;
    mostrarEstado(estadoAtual);

    estadoAtual = EstadoJogo::GameOver;
    mostrarEstado(estadoAtual);

    cout << endl;

    return 0;
}

void mostrarEstado(EstadoJogo estado){
    switch (estado){
        case EstadoJogo::MenuPrincipal:
            cout << "Voce esta no Menu principal." << endl;
            break;
        case EstadoJogo::Jogando:
            cout << "O jogo esta em andamento..." << endl;
            break;
        case EstadoJogo::Pausado:
            cout << "O jogo está pausado." << endl;
            break;
        case EstadoJogo::GameOver:
            cout << "Game Over!" << endl;
            break;
        default:
            cout << "Estado desconhecido." << endl;
    }
}
