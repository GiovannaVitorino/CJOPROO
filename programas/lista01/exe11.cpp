/*Escreva um programa que peça 2 números inteiros e um número real.
Calcule e mostre:
a. O produto do dobro do primeiro com metade do segundo;
b. A soma do triplo do primeiro com o terceiro;
c. O terceiro elevado ao cubo.*/

#include <iostream>
#include <cmath>

using namespace std;

int main(void){
    int i1, i2 ;
    float r, produto, soma, potencia;

    cout << "Digite o primeiro numero inteiro: ";
    cin >> i1;

    cout << "Digite o segundo numero inteiro: ";
    cin >> i2;

    cout << "Digite o numero real: ";
    cin >> r;

    produto = (i1 * 2) * ((float)i2 / 2); // ou produto = (i1 * 2) * (i2 / 2.0);
    soma = (3 * i1) + r;
    potencia = pow(r,3);

    cout << "O produto do dobro do primeiro com metade do segundo " << produto << endl;
    cout << "A soma do triplo do primeiro com o terceiro: " << soma << endl;
    cout << "O terceiro elevado ao cubo: " << potencia << endl;

    return 0;
}
