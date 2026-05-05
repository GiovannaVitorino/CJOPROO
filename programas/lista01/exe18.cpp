/*Escreva um programa que peça a entrada de um valor inteiro e mostre na
tela se esse valor é positivo ou negativo.*/

#include <iostream>

using namespace std;

int main(void){
    int32_t n;

    cout << "Entr um valor inteiro: ";
    cin >> n;

    if (n >= 0)
        cout << "Valor positivo.";
    else
        cout << "Valor negativo.";

    cout << endl;
    cout << "Tecle <Enter> para encerrar... ";
    cin.ignore();
    cin.get();
    return 0;
}
