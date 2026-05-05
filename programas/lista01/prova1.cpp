#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int16_t total, nota, maiorNota = 0;
vector<int> matriz;

//----FUNÇÃO PARA VALIDAR ENTRADA DE DADOS----
void entrada() {
    cout << "* Informe o total de avaliacoes: ";
    cin >> total;

    cout << "Informe os valores separados por espaco: ";
    for (int i = 0; i < total; i++) {
        cin >> nota;
        //grava o valor digitado na matriz
        matriz.push_back(nota);
        // encontra a maior nota para definir a altura do grafico
        if (nota > maiorNota) {
            maiorNota = nota;
        }
    }
}

//----FUNÇÃO PARA EXIBIR O GRÁFICO----
void saida() {
    cout << "\nGrafico de Barras:" << endl;
    for (int linha = maiorNota; linha >= 1; --linha) {
        cout << setw(2) << linha << "|";  // formata a saida
        for (int i = 0; i < total; ++i) {
            if (matriz[i] >= linha)
                cout << "*  ";
            else
                cout << "   ";
        }
        cout << endl;
    }

    //exibir divisoria
    cout << "  +";
    for (int i = 0; i < total; ++i) {
        cout << " - ";
    }

    // Exibir base com os valores
    cout << endl;
    cout << "  ";
    for (int i = 0; i < total; ++i) {
        cout << setw(2) << matriz[i] << "|";
    }
    cout << endl;
}

//funcao principal
int main() {
    cout << "Inicio: Prova P1" << endl;
    entrada();
    saida();

    // --ENCERRAMENTO--
    cout << "\nTecle <Enter> para encerrar... ";
    cin.ignore();
    cin.get();

    return 0;
}
