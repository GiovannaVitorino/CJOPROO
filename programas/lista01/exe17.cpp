/*Escreva um programa que peça a entrada de dois números inteiros e imprima
o maior deles*/

#include <iostream>

using namespace std;

int main(void){
    int16_t a, b;

    cout << "Valor da variavel <A>: ";
    cin >> a;

    cout << "Valor da variavel <B>: ";
    cin >> b;

    if (a > b)
        cout << "Maior valor: " << a;
    else
        cout << "Maior valor: " << b;

    cout << endl;
    cout << "Tecle <Enter> para encerrar... ";
    cin.ignore();
    cin.get();
    return 0;
}
