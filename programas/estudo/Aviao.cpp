#include "Aviao.hpp"

Aviao::Aviao(int tp) {
    if (tp == 1) {
        tipo = "Jato";
        velMax = 800;
    } else if (tp == 2) {
        tipo = "Monomotor";
        velMax = 400;
    } else if (tp == 3) {
        tipo = "Planador";
        velMax = 100;
    }
}

void Aviao::imprimir() {
    std::cout << "Tipo: " << tipo << std::endl;
    std::cout << "Velocidade: " << vel << std::endl;
    std::cout << "Velocidade máxima: " << velMax << std::endl;
}
