/*Escrevaumprogramaque soliciteaentradadeuminteiro N e utilize uma
função para exibir o seguinte padrão:
1 1
2 22
3 333
4 ...
5 NNNNNN...N
*/

#include <iostream>

using namespace std;

void saida(int32_t n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < i+1; j++){
            cout << i+1;
        }
        cout << endl;
    }
}

int main(void){

    int32_t n;

    cout << "Entre um numero inteiro: ";
    cin >> n;

    saida(n);

    cout << endl;
    cout << "Tecle <Enter> para encerrar... ";
    cin.ignore();
    cin.get();
    return 0;
}
