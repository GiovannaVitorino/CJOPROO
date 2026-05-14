#ifndef TIME_HPP
#define TIME_HPP
#include <iostream>
using namespace std;

class Time {
    public:
    Time();//construtor padrão
    void setTime(int h, int m, int s);//definir a hora, minuto e segundo
    void printUniversal()const;//imprimir a hora no formato universal
    void printStandard()const;//imprimir a hora no formato padrão

    private:
    unsigned int hour;//0-23
    unsigned int minute;//0-59
    unsigned int second;//0-59
};
#endif