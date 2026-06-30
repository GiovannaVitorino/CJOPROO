#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    cout << "Exemplo de argumentos de uma funcao principal\n\n";
    cout << "Numero de argumentos: " << argc << "\n\n";

    for (int i = 0; i < argc; i++) {
        cout << "Argumento " << i << ": " << argv[i] << "\n";
    }

    return 0;
}
