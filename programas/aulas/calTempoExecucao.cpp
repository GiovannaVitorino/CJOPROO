#include <iostream>
using namespace std;

int main() {
    int n = 10;       // tamanho de exemplo
    int contador = 0; // inicializa contador

    for (int i = n / 2; i < n; i++) {
        int j = 1; // c1
        while ((j + n / 2) <= n) {
            int k = 1;
            while (k <= n) {
                contador++;
                k++; // incrementa k para evitar loop infinito
            }
            j++; // incrementa j para evitar loop infinito
        }
    }

    cout << "Contador final: " << contador << endl;
    return 0;
}
