#include <iostream>
#include <cstring>

using namespace std;

int main(void) {
    cout << "\nExemplo de uso de strcmp()" << endl;

    const char *nomes[] = {
    "Paulo",
    "Ana Cristina",
    "Renata",
    "Joao",
    "Miranda"
    };

    size_t total = sizeof (nomes) / sizeof(nomes[0]);

    const char *temp;

    int i, j;

    cout << "-> Total de nomes: " << total << endl << endl;

    cout << "Antes da ordenacao: " << "\n\n";

    for (i = 0; i < total; i++){
        cout << i+1 << ". " << nomes[i] << endl;
    }

    for (i = 0; i < total; i++){
        for (j = i+1; j < total; j++){
            if(strcmp(nomes[i], nomes[j]) > 0){
                temp = nomes [i];
                nomes[i] = nomes [j];
                nomes[j] = temp;
            }
        }
    }

    cout << "\n";

    cout << "* Depois da ordenacao: " << endl << endl;

    for (i=0; i<total; i++){
        cout << i+1 << ". " << nomes[i] << endl;
    }

    cout << endl;

    return 0;
}
