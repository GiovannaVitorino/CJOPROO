#include <iostream>
using namespace std;
 class Retangulo {
    // Atributos
    private:
        int altura;
        int largura;

    public:
    // Construtor
    Retangulo(int altura, int largura) : altura(altura), largura(largura) {}

    // Getters
    int getAltura() const {
        return altura;
    }

    int getLargura() const {
        return largura;
    }

    // Métodos
    int calcularArea() const {
        return altura * largura;
    }

    int calcularPerimetro() const {
        return 2 * (altura + largura);
    }
 };
 
 int main() {
    Retangulo retangulo(10, 20);
    cout << "Altura: " << retangulo.getAltura() << endl;
    cout << "Largura: " << retangulo.getLargura() << endl;
    cout << "Área: " << retangulo.calcularArea() << endl;
    cout << "Perímetro: " << retangulo.calcularPerimetro() << endl;

    cin.get();
    return 0;
 }
 