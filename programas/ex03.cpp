#include <iostream>

using namespace std;

int elevaCubo(int n);

int main(){
    cout << "\n";
    cout << "Exemplo de passagem por Valor\n\n";

    int numero = 5;

    cout << "*V0alorvoriginal: numero" << numero << "\n";

    numero = elevaCubo(numero);

    cout << "Valor modificado: " << numero << "\n\n";

    return 0;
}

int elevaCubo(int n){
    return n*n*n;

    }
