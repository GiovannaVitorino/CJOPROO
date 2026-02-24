/*jogo com x peças quadradas e y pecas triangulares. qual o maximo de participantes que pode ter para que ambos tenhama a mesma qtde de peças quadradas e trangulare?*/
#include <iostream>

using namespace std;

int main(void) {
   int quadradas, triangulares, a, b, r;

   cout << "\n";
   cout << "Calculo maximo de participantes do jogo.\n\n";
   cout << "Informe o total de peças quadradas: ";
   cin >> quadradas;
   cout << "\nInforme o total de peças triangulares: ";
   cin >> triangulares;

   a = quadradas;
   b = triangulares;

   //algoritmo de euclides para calcular mdc
   do{
    r =  a % b;
    a = b;
    b = r;
   } while (b != 0);

   cout << "\nConsiderando " << quadradas << " peças quadradas e " << triangulares << " peças triangulares, devemos ter no máximo " << a << " participantes.";

    cout << "\n\n";
    return 0;
}
