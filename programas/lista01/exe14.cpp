/*João Papo-de-Pescador, homem de bem, comprou um microcomputador para controlar
o rendimento diário de seu trabalho. Toda vez que ele traz um peso de peixes maior
que o estabelecido pelo regulamento de pesca do estado de São Paulo (50 quilos)
deve pagar uma multa de R$ 4,00 por quilo excedente. João precisa que você faça
um programa que leia a variável peso (peso de peixes) e calcule o excesso. Gravar
na variável excesso a quantidade de quilos além do limite e na variável multa o
valor da multa que João deverá pagar. Imprima os dados do programa com as
mensagens adequadas.*/

#include <iostream>
#include <iomanip>

using namespace std;

int main(void){
    float peso, excesso, multa;

    cout << "Quantos Kg voce pescou hoje? ";
    cin >> peso;

    excesso = peso - 50.00;
    multa = excesso * 4.00;

    cout << fixed << setprecision(2);
    cout << "Voce pescou " << excesso << "Kg alem do limite estabelecido." << endl;
    cout << "Devera pagar uma multa de R$" << multa << endl;

    cout << endl;
    cout << "Tecle <Enter> para encerrar... ";
    cin.get();
    return 0;
}
