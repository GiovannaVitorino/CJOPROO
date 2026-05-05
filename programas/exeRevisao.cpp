#include <iostream>
#include <vector>
/*escreva um programa que receba um conjunto de valores inteiros.
Em seguida, exiba uma grafico de barras horizontal simulando o
histograma referente aos valores que foram informados. O programa
deve exibir o resultado conforme o exemplo abaixo*/
//entrada: x dados (laço para contar os dados) gravar dados em matriz
//processamento:
//saida: grafico (-
//encontrar maior valor da matriz para saber qtde de colunas

using namespace std;

    vector<int> matriz;
    int dado, contador;

 void entrada(){
    cout << "Entre os dados de cada linha (0 para parar):" << endl;

    while (true) {
        cout << "Dado: ";
        cin >> dado;
        if (dado == 0) {
            break;
        }
        matriz.push_back(dado);
        contador++;
    }
 }

 void saida(){
     cout << endl;
    for (int i = contador - 1; i >= 0; i--){
            cout << i+1 << "|";
        for (int j = 0; j < matriz[i]; j++){
            if (matriz[i]==0)
                break;
            cout << "* ";
        }
        cout << endl;
    }
    /*cout << " +";
    for (int i = 0; i < contador+1; i++){
     cout << "- ";
    }
    cout << endl;*/

    for (int i = 0; i < contador+1; i++){
     cout << i << "|";
    }
    cout << endl;
 }


int main(){
    cout << "Programa grafico horizontal";
    entrada();
    saida();
}

