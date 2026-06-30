// ----------------------------------------------------------------------------
// Demonstra como ordenar um array de strings utilizando o Quick Sort
// ----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Total de nomes
const int TAM = 3;

// ----------------------------------------------------------------------------
// Prot�tipos de fun��o
// ----------------------------------------------------------------------------
void trocar(string& a, string& b);
int particao(string dados[], int menor, int maior);
void quickSort(string dados[], int menor, int maior);

// ----------------------------------------------------------------------------
// Fun��o principal
// ----------------------------------------------------------------------------
int main() {
    cout << "\nExemplo: Quick Sort\n\n";

    // Vari�veis
       string nomes [TAM];

    // Loop que realiza a entrada dos nomes
    for (int i = 0; i < TAM; i++)
    {
        cout << "Informe o nome " << i+1 << ": ";
        getline(cin, nomes[i]);
        cout << endl;
    }

    cout << "\n";

    // Imprimindo os nomes antes da ordenacao
    cout << "Nomes antes da ordenacao:\n\n";

    for (int i = 0; i < TAM; i++)
    {
        cout << "Nome " << i+1 << ": " << nomes[i] << endl;
    }

    // Ordena os nomes utilizando o Quick Sort
    quickSort (nomes, 0, TAM-1);
    cout << "\n";

    // Imprimindo os nomes depois da ordenacao
    cout << "Nomes depois da ordenacao:\n\n";

    for (int i = 0; i < TAM; i++)
    {
        cout << "Nome " << i+1 << ": " << nomes[i] << endl;
    }

    cout << "\n";

    // Fim do programa
    return 0;

}

// ----------------------------------------------------------------------------
// Fun��es
// ----------------------------------------------------------------------------

// Fun��o para trocar o valor de duas strings
void trocar(string& a, string& b) {
    string temp = a;
    a = b;
    b = temp;
}

// ----------------------------------------------------------------------------

// Fun��o de parti��o, que coloca o piv� no lugar correto e organiza os
// elementos menores que o piv� � esquerda e os maiores � direita
int particao(string dados[], int menor, int maior) {
    string pivo = dados[maior];
    int i = menor - 1;

    for (int j = menor; j < maior; j++)
    {
        if (dados[j] <= pivo)
        {
            i++;
            trocar(dados[i], dados[j]);
        }
    }

    trocar(dados[i + 1], dados[maior]);
    return i + 1;
}

// ----------------------------------------------------------------------------

// Fun��o Quick Sort
void quickSort(string dados[], int menor, int maior) {
     if (menor < maior)
    {
        int pivo = particao(dados, menor, maior);

        quickSort(dados, menor, pivo - 1);
        quickSort(dados, pivo + 1, maior);
    }
}
