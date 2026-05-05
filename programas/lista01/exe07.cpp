/* Escreva um programa para ler os valores de uma temperatura em graus
Fahrenheit e apresentá-la convertida para graus Kelvin. A fórmula de
conversão de graus Fahrenheit para graus Kelvin é dada por
K = (F − 32) × 5/9 + 273,15. Nessa fórmula, F corresponde à temperatura
em graus Fahrenheit e K corresponde à temperatura em graus Kelvin. Para
apresentar o resultado, considere a utilização de duas casas decimais*/

#include <iostream>
#include <iomanip>

using namespace std;

int main(void){
    float f, k;

    cout << "Entre a temperatura em fahrenheit: ";
    cin >> f;

    k = (f - 32) * 5/9 + 273.15;

    cout << fixed << setprecision(2);
    cout << "Temperatura convertida em kelvin: " << k << endl;

    return 0;
}
