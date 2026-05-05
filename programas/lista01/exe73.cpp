/*73. Escrevaumprogramaque soliciteaentradadeuminteiroNeutilizeuma funçãopara
exibiroseguintepadrão:
1 1
2 12
3 123
4 ...
5 123...N
*/

#include <iostream>

using namespace std;

void saida(int32_t n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < i+1; j++){
            cout << j+1;
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
