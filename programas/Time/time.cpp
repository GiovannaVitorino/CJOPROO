#include "time.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Construtor padrão
//asegura que todos os objetos Time iniciem em um esado consistente
Time::Time() : hour(0), minute(0), second(0) {}

void Time::setTime(int h, int m, int s) {
    if ((h >= 0 && h < 24) && (m >= 0 && m < 60) && (s >= 0 && s < 60)) {
        hour = h;
        minute = m;
        second = s;
    } else {
        throw invalid_argument("Hour, minute and/or second was out of range!");
    }
}

void Time::printUniversal() const {
    cout << setfill('0') << setw(2) << hour << ":"
         << setfill('0') << setw(2) << minute << ":"
         << setfill('0') << setw(2) << second;
}

void Time::printStandard() const {
    cout << ((hour == 0 || hour == 12) ? 12 : hour % 12) << ":"
         << setfill('0') << setw(2) << minute << ":"
         << setfill('0') << setw(2) << second
         << (hour < 12 ? " AM" : " PM");
}