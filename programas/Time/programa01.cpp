#include <iostream>
#include <stdexcept>
#include "time.hpp"

using namespace std;

int main(){
    cout << "\nTime\n\n";

    //instancia objeto da classe time
    Time t;
    t.printUniversal(); //00:00:00

    cout <<"\nThe initial standard time is: ";
    t.printStandard(); //12:00:00 AM
    cout << endl;

    t.setTime(13, 27, 6);

    cout << "\nUniversal time after setTime is: ";
    t.printUniversal(); //13:27:06 

    cout << "\nStandard time after setTime is: ";
    t.printStandard(); //1:27:06 PM
    cout << endl;

    //tentativa de definir um horário inválido
    try {
        t.setTime(99, 99, 99); //definir um horário inválido
    } catch (invalid_argument &e) {
        cout << "\nException: " << e.what() << endl;
    }

    cout << "\nAfter attempting invalid settings:\n";
    cout << "Universal time: ";
    t.printUniversal(); //13:27:06

    cout << "\nStandard time: ";
    t.printStandard(); //1:27:06 PM'
    cout << endl;

    return 0;
}