/* Escreva um programa que peça para o usuário informar quanto ele ganha por
hora, o nome do mês e o número de horas que ele trabalhou nesse mês. Em seguida,
o programa deve calcular e exibir o salário que ele deve receber no final mês.
Para apresentar o resultado, considere a utilização de duas casas decimais.*/
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main(void){
    float vh, salario;
    int ht;
    string mes;
    //char mes[10];

    cout << "Valor da hora: ";
    cin >> vh;

    cout << "Mes: ";
    cin >> mes;
    //getline(cin, mes)

    cout << "Horas trabalhadas: ";
    cin >> ht;

    salario = vh*ht;

    cout << fixed << setprecision(2);
    cout << "\nSalario do mes de " << mes << ": R$" << salario << endl;

    return 0;
}
