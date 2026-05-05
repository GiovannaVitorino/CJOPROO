/* Escreva um programa para ler os valores de uma temperatura em graus Celsius e
apresentá-la convertida para graus Fahrenheit e graus Kelvin. A fórmula de conversão para
graus Fahrenheit é dada por F = (9 × C + 160)/5. A fórmula de conversão para graus
Kelvin é dada por K = C+273,15. Nessas fórmulas, F corresponde à temperatura em graus
Fahrenheit, K corresponde à temperatura em graus Kelvin e C corresponde à temperatura
em graus Celsius. Para apresentar o resultado, considere a utilização de duas casas decimais.*/

#include <iostream>
#include <iomanip>

using namespace std;

int main(void){
    float c, f, k;

    cout << "Entre a temperatura em celsius: ";
    cin >> c;

    f = (9 * c + 160)/5;
    k = c + 273.15;

    cout << fixed << setprecision(2);
    cout << "\nTemperatura convertida em fahrenheit: " << f << endl;
    cout << "Temperatura convertida em kelvin: " << k << endl;

    return 0;
}
