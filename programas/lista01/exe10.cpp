/*Escreva um programa para realizar a leitura de dois valores inteiros e
armazená-los nas variáveis A e B. Em seguida, efetuar a troca dos valores,
de forma que a variável A passe a possuir o valor da variável B e a
variável B passe a possuir o valor da variável A. Apresentar os valores
antes e depois da troca*/

#include <iostream>

using namespace std;

int main(void){
    int a, b, x;

    cout << "Valor para a variavel <A>: ";
    cin >> a;

    cout << "Valor para a variavel <B>: ";
    cin >> b;

    cout << "Valores antes da troca" << endl;
    cout << "<A>: " << a << endl;
    cout << "<B>: " << b << endl;

    x = a;
    a = b;
    b = x;

    //comando swap ou função

    cout << "Valores depois da troca" << endl;
    cout << "<A>: " << a << endl;
    cout << "<B>: " << b << endl;

    return 0;
}
