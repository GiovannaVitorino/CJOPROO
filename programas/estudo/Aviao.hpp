#pragma once
#include <iostream>
#include <string>

class Aviao {
public:
    int vel = 0;
    int velMax;
    std::string tipo;

    Aviao(int tp);      // apenas declaração
    void imprimir();    // apenas declaração
};
