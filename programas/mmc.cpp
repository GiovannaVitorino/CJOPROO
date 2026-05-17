/*jogo com x pe�as quadradas e y pecas triangulares. qual o maximo de participantes que pode ter para que ambos tenhama a mesma qtde de pe�as quadradas e trangulare?*/
#include <iostream>

using namespace std;

int main(void) {
   int quadradas, triangulares, a, b, r;

   cout << "\n";
   cout << "Calculo maximo de participantes do jogo.\n\n";
   cout << "Informe o total de pecas quadradas: ";
   cin >> quadradas;
   cout << "\nInforme o total de pecas triangulares: ";
   cin >> triangulares;

   a = quadradas;
   b = triangulares;

   //algoritmo de euclides para calcular mdc
   do{
    r =  a % b;
    a = b;
    b = r;
   } while (b != 0);

   cout << "\nConsiderando " << quadradas << " pecas quadradas e " << triangulares << " pecas triangulares, devemos ter no maximo " << a << " participantes.";

    cout << "\n\n";
    return 0;
}
