#include <iostream>
using namespace std;

void cantar(int);
void dancar(int);
void enrolar(int);

int main(void) {
    cout << "\nArray de ponteiros para funcoes\n\n";

    void (*funcoes[3])(int) = {
        cantar,
        dancar,
        enrolar
    };

    int opcao;
    cout << "Informe a opcao desejada (0, 1 ou 2): ";
    cin >> opcao;
    cout << endl;

    while ((opcao >= 0) && (opcao < 3)) {
        (*funcoes[opcao])(opcao);

        cout << "Informe a opcao desejada (0, 1 ou 2): ";
        cin >> opcao;
        cout << endl;
    }

    return 0;
}

void cantar(int opcao) {
    cout << "* Voce escolheu a opcao " << opcao << ". Vamos cantar!\n\n";
}

void dancar(int opcao) {
    cout << "* Voce escolheu a opcao " << opcao << ". Vamos dancar!\n\n";
}

void enrolar(int opcao) {
    cout << "* Voce escolheu a opcao " << opcao << ". Vamos enrolar!\n\n";
}
