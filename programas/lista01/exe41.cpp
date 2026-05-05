/*Supondo que a população de um país A seja da ordem de 80000 habitantes com uma taxa
anual de crescimento de 3% e que a população de B seja 200000 habitantes com uma taxa de
crescimento de 1.5%. Escreva um programa que calcule e informe o número de anos necessários
para que a população do país A ultrapasse ou iguale a população do país B, mantidas as taxas
de crescimento*/

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
