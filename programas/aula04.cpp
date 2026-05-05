#include <iostream>

using namespace std;

int main(){
    int idade = 25;
    int *idadePtr = &idade;
    int6 *nomePtr = nullptr;

    cout << "1. Valor de <idade>: " << idade << "\n";
    cout << "1. Endereco de <idade>: " << &idade << "\n";
    cout << "2. Valor de <idadePtr>: " << idadePtr << "\n";
    cout << "2. Valor apontado por <*idadePtr>: " << *idadePtr << "\n\n";

    return 0;
}
