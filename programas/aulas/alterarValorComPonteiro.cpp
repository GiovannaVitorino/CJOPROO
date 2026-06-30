#include <iostream>

using namespace std;

int main(){
    int idade = 25;
    int *idadePtr = &idade;
    int *nomePtr = nullptr;

    cout << "1. Valor de <idade>: " << idade << "\n";
    cout << "1. Endereco de <idade>: " << &idade << "\n\n";

    *idadePtr = 30;

    cout << "2. Valor de <idade>: " << idade << "\n";
    cout << "2. Endereco de <idade>: " << &idade << "\n\n";

    return 0;
}
