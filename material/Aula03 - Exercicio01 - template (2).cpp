// ----------------------------------------------------------------------------
// Demonstra como ordenar um array de strings utilizando o Quick Sort
// ----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Total de nomes
// TODO

// ----------------------------------------------------------------------------
// Protótipos de função
// ----------------------------------------------------------------------------
void trocar(string& a, string& b);
int particao(string dados[], int menor, int maior);
void quickSort(string dados[], int menor, int maior);

// ----------------------------------------------------------------------------
// Função principal
// ----------------------------------------------------------------------------
int main() {

    cout << "\nExemplo: Quick Sort\n\n";

    // Variáveis
    // TODO

    // Loop que realiza a entrada dos nomes
    // TODO
    
    cout << "\n";

    // Imprimindo os nomes antes da ordenação
    cout << "Nomes antes da ordenação:\n\n";

    // TODO
    
    // Ordena os nomes utilizando o Quick Sort
    // TODO

    cout << "\n";

    // Imprimindo os nomes depois da ordenação
    cout << "Nomes depois da ordenação:\n\n";
    
    // TODO
    cout << "\n";

    // Fim do programa
    return 0;

}

// ----------------------------------------------------------------------------
// Funções
// ----------------------------------------------------------------------------

// Função para trocar o valor de duas strings
void trocar(string& a, string& b) {
    // TODO
}

// ----------------------------------------------------------------------------

// Função de partição, que coloca o pivô no lugar correto e organiza os 
// elementos menores que o pivô à esquerda e os maiores à direita
int particao(string dados[], int menor, int maior) {
    // TODO
}

// ----------------------------------------------------------------------------

// Função Quick Sort
void quickSort(string dados[], int menor, int maior) {
    // TODO
}
