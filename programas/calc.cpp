#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

float resultado, n1, n2;

void entrada();
void saida(string operacao);
void pausa();
void adicao();
void subtracao();
void multiplicacao();
void divisao();

int main(void) {
    int opcao = 0;

    while (opcao != 5) {
        cout << setprecision(2) << fixed << showpoint;

        cout << "\nPrograma calculadora - Menu principal\n";
        cout << "[1] - Adicao" << endl;
        cout << "[2] - Subtracao" << endl;
        cout << "[3] - Multiplicacao" << endl;
        cout << "[4] - Divisao" << endl;
        cout << "[5] - Encerrar programa" << endl;
        cout << "\n=> Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: adicao(); break;
            case 2: subtracao(); break;
            case 3: multiplicacao(); break;
            case 4: divisao(); break;
            case 5: cout << "\nPrograma encerrado.\n\n"; break;
            default: cout << "\nOpcao invalida!\n"; break;
        }
    }

    return 0;
}

void entrada() {
    cout << "Informe o primeiro numero: "; cin >> n1;
    cout << "Informe o segundo numero: "; cin >> n2;
}

void saida(string operacao) {
    cout << "\nResultado da " << operacao;
    cout << " entre " << n1 << " e " << n2 << " = " << resultado << endl;
    pausa();
}

void pausa() {
    char letra;
    cout << "\nTecle <C> + <Enter> para voltar ao menu: ";
    do {
        letra = cin.get();
        letra = toupper(letra);
    } while (letra != 'C');
}

void adicao() {
    cout << "\nRotina de adicao" << endl;
    entrada();
    resultado = n1 + n2;
    saida("adicao");
}

void subtracao() {
    cout << "\nRotina de subtracao" << endl;
    entrada();
    resultado = n1 - n2;
    saida("subtracao");
}

void multiplicacao() {
    cout << "\nRotina de multiplicacao" << endl;
    entrada();
    resultado = n1 * n2;
    saida("multiplicacao");
}

void divisao() {
    cout << "\nRotina de divisao" << endl;
    entrada();
    if (n2 == 0) {
        cout << "\nErro: divisao por zero!\n";
        pausa();
    } else {
        resultado = n1 / n2;
        saida("divisao");
    }
}
