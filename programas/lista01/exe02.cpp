/*Escreva um programa que peça para o usuário informar um número inteiro
e então mostre a mensagem: “O número informado foi <número>.*/
#include <iostream>

using namespace std;

int main(void){
    int n;

    cout << "Informe um numero inteiro: ";
    cin >> n;

    cout << "\nO numero informado foi: " << n;

    return 0;
}
