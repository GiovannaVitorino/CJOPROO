/*Escreva um programa para uma loja de tintas. O programa deverá pedir o tamanho
em metros quadrados da área a ser pintada. Considere que a cobertura da tinta é
de 1 litro para cada 3 metros quadrados e que a tinta é vendida em latas de 18L,
que custam R$ 80,00. Informe ao usuário a quantidade de latas de tinta que deve
ser comprada e o preço total que deverá ser pago. Para apresentar o resultado,
considere a utilização de duas casas decimais*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(void){
    float area, litros, qtdeLatas, preco;

    cout << "Qual a area a ser pintada (metros quadrados)? ";
    cin >> area;

    litros = area / 3.00;
    qtdeLatas = ceil(litros / 18.00); // ceil arrendonda pra cima
    preco = qtdeLatas * 80.00;

    cout << fixed << setprecision(2);
    cout << "Quantidade de latas: " << qtdeLatas << endl;
    cout << "Preco: R$" << preco << endl;

    cout << endl;
    cout << "Tecle <Enter> para encerrar... ";
    cin.get();
    return 0;
}
