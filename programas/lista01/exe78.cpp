/*
78. Escrevaumprogramaqueutilizeumafunçãoparaexibiroseguintepadrão:
1 *****
2 ****
3 ***
4 **
5 *
*/

#include <iostream>
using namespace std;

void saida() {
    for (int i = 1; i <= 5; i++) {
        //cout << i << " ";
        for (int j = 0; j <= 5 - i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
}

int main() {
    cout << "Resultado da funcao: " << endl;
    saida();

    cout << endl;
    cout << "Tecle <Enter> para encerrar... ";
    cin.ignore();
    cin.get();
    return 0;
}


