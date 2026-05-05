/*Escreva um programa para efetuar o cálculo da quantidade total de litros de combustível
gasta em uma viagem. O usuário deverá fornecer os valores do tempo gasto na viagem, da
velocidade média que foi utilizada e da quantidade de quilômetros que o automóvel faz com
um litro de combústivel. Para obter a distância percorrida, utilize a fórmula
DISTANCIA = TEMPO × VELOCIDADE. A quantidade de litros de combustível gasta na viagem
pode ser obtida pela fórmula DISTANCIA/QUANTIDADE_KILOMETROS_LITRO. O programa deve
apresentar os valores da velocidade média, do tempo gasto na viagem, da distância total
que foi percorrida e da quantidade de litros de combustível que foi utilizada na viagem.
Para apresentar o resultado, considere a utilização de duas casas decimais.*/

#include <iostream>
#include <iomanip>

using namespace std;

int main(void){
    float tempo, vm, kml, distancia, litros;

    cout << "Entre o tempo gasto na viagem: ";
    cin >> tempo;

    cout << "Entre a velocidade media: ";
    cin >> vm;

    cout << "Entre a qtde. de km por litro: ";
    cin >> kml;

    distancia = tempo * vm;
    litros = distancia/kml;

    cout << fixed << setprecision(2);
    cout << "Velocidade media: " << vm << "KM/h" << endl;
    cout << "Tempo gasto na viagem: " << tempo << "h" << endl;
    cout << "Distancia percorrida: " << distancia << "KM" << endl;
    cout << "Qtde. de litros gastos: " << litros << "L" << endl;

    return 0;
}
