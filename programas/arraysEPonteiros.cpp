#include <iostream>
#include <string>
using namespace std;

void imprime1(int numeros[], size_t tamanho, string nome);
void imprime2(int *numeros, size_t tamanho, string nome);

int main(void) {
    cout << "Relacionamento entre Arrays e Ponteiros" << endl;

    int numeros1[] = {1, 2, 3, 4, 5};
    int numeros2[] = {6, 7, 8, 9, 10};
    int numeros3[] = {11, 12, 13, 14, 15};

    size_t tamanho1 = sizeof(numeros1) / sizeof(numeros1[0]);
    size_t tamanho2 = sizeof(numeros2) / sizeof(numeros2[0]);
    size_t tamanho3 = sizeof(numeros3) / sizeof(numeros3[0]);

    imprime1(numeros1, tamanho1, "<numeros1>");
    imprime2(numeros2, tamanho2, "<numeros2>");

    int *ptr3 = numeros3;

    cout << "3. <*ptr3>...: [";
    for (int i = 0; i <tamanho3; i++){
        if (i < tamanho3 - 1)
            cout << ptr3[i] << ", ";
        else
            cout << ptr3[i] << "]" << endl;
    }

    cout << "\n";

    return 0;
}

void imprime1(int numeros[], size_t tamanho, string nome){
    cout << "1. " << nome << ": [";

    for (int i = 0; i < tamanho; i++){
        if (i < tamanho - 1)
            cout << numeros[i] << ", ";
        else
            cout << numeros[i] << "]" << endl;
    }
}

void imprime2(int *numeros, size_t tamanho, string nome){
    cout << "2. " << nome << ": [";

    for (int i = 0; i < tamanho; i++){
        if (i < tamanho - 1)
            cout << *(numeros + i) << ", ";
        else
            cout << *(numeros + i) << "]" << endl;
    }
}
