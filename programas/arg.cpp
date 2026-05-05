#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *arg[]){
    cout << "Exemplo de argumentos de uma funcao principal\n\n";
    cout << "Numero s de argumentis:\n\n"; << argc << "\n\n";

    for (int I = 0; i < argc; i++){
        cout << "argumento " << i << ":"<< argv[i];
    }

return 0;
}

