#include <iostream>

using namespace std;

int main(void) {
    float A, B, C;

    cout << "\n";
    cout << "Desvio condicional aninhado\n\n";
    cout << "*Informe o valor do lado <A>: "; cin >> A;
    cout << "*Informe o valor do lado <B>: "; cin >> B;
    cout << "*Informe o valor do lado <C>: "; cin >> C;

    if (A < (B + C) && B < (A + C) && C < (A + B)) {
        cout << "\nOs valores fornecidos formam um triangulo ";

        if (A == B && B == C) {
            cout << "equilatero";
        }
        else if (A == B || A == C || B == C) {
            cout << "isosceles";
        }
        else {
            cout << "escaleno";
        }
    }
    else {
        cout << "\nOs valores fornecidos não formam um triangulo.";
    }

    cout << "\n\n";
    return 0;
}
