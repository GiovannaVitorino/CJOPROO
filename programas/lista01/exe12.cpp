/*Utilizando como dados de entrada o peso, a altura e o sexo de uma pessoa, escreva
um programa que calcule seu peso ideal e informe se ela está dentro, acima
ou abaixo do peso. Considere as seguintes fórmulas:
a. Para homens: (72.7 × altura) − 58
b. Para mulheres: (62.1 × altura) − 44.7*/

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

int main(void){
    float peso, altura, pesoIdeal;
    char sexo;

    cout << "Qual e seu peso atual? ";
    cin >> peso;

    cout << "Qual e sua altura? ";
    cin >> altura;

    cout << "Qusl e seu sexo (F ou M)? ";
    cin >> sexo;
    sexo = toupper(sexo);

    if (sexo == 'M')
        pesoIdeal = (72.7 * altura) - 58;
    else
        pesoIdeal = (62.1 * altura) - 44.7;

    cout << fixed << setprecision(2);
    cout << "O seu peso ideal e: " << pesoIdeal << "Kg. Voce esta ";
    if (peso == pesoIdeal)
        cout << "dentro do peso.";
    else if (peso > pesoIdeal)
        cout << peso - pesoIdeal << "Kg acima do peso.";
    else
        cout << pesoIdeal - peso << "kg abaixo do peso.";

    cout << endl;
    cout << "Tecle <Enter> para encerrar... ";
    cin.get();
    return 0;
}
