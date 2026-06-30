#include <iostream>
#include <iomanip>

using namespace std;

int main(void) {
    int16_t n;
    int16_t r;

    cout << "\n";
    cout << "Programa tabuaada";
    cout << "\n\nInforme um numero: "; cin >> n;

    for (int16_t i {1}; i <= 10; ++i){

        r = n * i;
        cout << setw(2) << right << n << "X" << i << " = " << r << "\n";
    }

    cout << "\n\n";
    return 0;
}
