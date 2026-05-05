/* Escreva um programa que pergunte quanto você ganha por hora e o número de horas
trabalhadas no mês. Calcule e mostre o total do seu salário no referido mês,
sabendo-se que são descontados 11% para o Imposto de Renda, 8% para o INSS e 5%
para o sindicato. O valor do salário líquido é obtido após realizar os descontos
do salário bruto. O programa deve apresentar o seguinte resultado, utilizando
duas casas decimais:
1 => Cálculo Salarial
3 + Salário Bruto..: R$ <valor do salário bruto>
4- IR (11%).......: R$ <valor do imposto de renda>
5- INSS (8%)......: R$ <valor do INSS>
6- Sindicato (5%).: R$ <valor do sindicato>
7 = Salário Líquido: R$ <valor do salário líquido>*/

#include <iostream>
#include <iomanip>

using namespace std;

int main(void){
    float vh, ht, sb, sl, descIR, descINSS, descSind;
    const float ir = 11.0;
    const float inss = 8.0;
    const float sind = 5.0;

    cout << "Valor da hora: ";
    cin >> vh;

    cout << "Horas trabalhadas: ";
    cin >> ht;

    sb = vh * ht;

    descIR = sb * ir / 100.00;
    descINSS = sb * inss / 100.00;
    descSind = sb * sind / 100.00;

    sl = sb - descIR - descINSS - descSind;

    cout << fixed << setprecision(2);
    cout << "\n=> Calculo Salarial" << endl;
    cout << "+ Salario Bruto..: R$ " << sb << endl;
    cout << "- IR (11%).......: R$ " << descIR << endl;
    cout << "- INSS (8%)......: R$ " << descINSS << endl;
    cout << "- Sindicato (5%).: R$ " << descSind << endl;
    cout << "= Salario Liquido: R$ " << sl << endl;

    cout << endl;
    cout << "Tecle <Enter> para encerrar... ";
    cin.ignore();
    cin.get();
    return 0;
}
