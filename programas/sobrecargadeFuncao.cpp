/*função incrementar por valor*/
#include <iostream>

using namespace std;

void imprime(){
    cout << "Funcao sem argumentos." << endl;
}

void imprime(int valor){
    cout << "Funcao com argumento inteiro: " << valor <<  endl;
}

void imprime(float valor){
    cout << "Funcao com argumento real: " << valor <<  endl;
}

void imprime(int n1, float n2){
    cout << "Primeiro valor: " << n1 <<  endl;
    cout << "Segundo valor " << n2 <<  endl;
}

int main(void) {
   cout << "\n";
   imprime();
   imprime(10);
   imprime(10.99f);
   imprime(1, 0.99f);

    cout << "\n\n";
    return 0;
}
