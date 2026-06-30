#include <iostream>
#include <cstring>

using namespace std;

struct Ponto{
    int x;
    int y;

    void defineCoordenadas(int px, int py){
        x = px;
        y = py;
    }

    void exibeCoordenadas(string P) const{
        cout << "Coordenadas do ponto " << P << ": (" << x << ", " << y << ")\n";
    }
};

int main(void) {

    cout << "\nDeclaracao de estrutura com atributos e funcoes\n\n";

    Ponto p1;

    p1.defineCoordenadas(10,20);
    p1.exibeCoordenadas("P1");

    cout << endl;

    return 0;
}
