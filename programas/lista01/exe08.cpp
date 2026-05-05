/*Escreva um programa para calcular e apresentar o valor do volume de uma
lata de óleo. O valor do volume pode ser obtido pela fórmula
V = 3.141516×R×R×A, onde V corresponde ao valor do volume, R corresponde
ao valor do raio e A correpsonde ao valor da altura. O usuário deverá
fornecer os valores do raio e da altura. Para apresentar o resultado,
considere a utilização de duas casas decimais*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(void){
    float v, r, a;
    const float pi = 3.141516;

    cout << "Valor do raio: ";
    cin >> r;

    cout << "Valor da altura: ";
    cin >> a;

    v = pi * pow(r,2) * a;

    cout << fixed << setprecision(2);
    cout << "Volume da lata de oleo: " << v << "L" << endl;

    return 0;
}
