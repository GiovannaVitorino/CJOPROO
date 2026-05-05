/* Escreva um programa para calcular e apresentar o valor do peso de uma
esfera. O valor do peso pode ser obtido pela fórmula
P = D × 4 × 3.141516 × R × R ×R/3, onde P representa o valor do peso, D
representa o valor da densidade e R representa o valor do raio. O usuário
deverá fornecer os valores da densidade e do raio. Para apresentar o
resultado, considere a utilização de duas casas decimais.*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(void){
    float p, d, r;
    const float pi = 3.141516;

    cout << "Valor do raio: ";
    cin >> r;

    cout << "Valor da densidade: ";
    cin >> d;

    p = d * 4 * pi * pow(r,3)/3;

    cout << fixed << setprecision(2);
    cout << "Peso da esfera: " << p << "Kg" << endl;

    return 0;
}
