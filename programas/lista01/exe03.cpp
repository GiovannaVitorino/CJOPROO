/*Escreva um programa que peça para o usuário informar 4 notas bimestrais
de um aluno. Em seguida, o programa deve calcular e exibir a média final
que o aluno obteve. Para apresentar o resultado, considere a utilização
de duas casas decimais.*/
#include <iostream>
#include <iomanip>

using namespace std;

int main(void){
    float n, soma, media;

    for (int i = 0; i < 4; i++){
        cout << "Informe a " << i+1 << "a. nota: ";
        cin >> n;

        soma += n;
    }

    media = soma/4;

    cout << fixed << setprecision(2);
    cout << "\nMedia final do estudante: " << media;

    return 0;
}
