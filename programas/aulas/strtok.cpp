#include <iostream>
#include <cstring>

using namespace std;

int main(void) {
    cout << "\nExemplo de uso de strtok() e de alocacao dinamica" << endl << endl;

    char texto[] = "Minha-frase-de-token-teste-teste";
    char separador[] = "-";
    int capacidade = 2;
    char **tokens = nullptr;

    tokens = new char*[capacidade];

    char *tokenPtr;
    int i, total;

    cout << "*Texto inicial: " << texto << endl;

    tokenPtr = strtok(texto, separador);

    total = 0;

    while(tokenPtr != NULL){
        if(total >= capacidade){
            capacidade *=2;

            char **temp = new char*[capacidade];

            for (i = 0; i < total; i++){
                temp[i] = tokens[i];
            }

            delete[] tokens;
            tokens = temp;
        }
        tokens[total] = tokenPtr;
        total++;
        tokenPtr = strtok(NULL, separador);
    }

    cout << "* Foram gerados " << total << " tokens: " << endl;
    cout << endl;

    return 0;
}
