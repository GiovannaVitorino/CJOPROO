#include <iostream>
using namespace std;

int main(void) {
    cout << "\n";
    cout << "Exemplo de aritmetics de ponteiros\n\n";

    int numeros[] = {2, 5, 10, 1, 3, 21};

    int *ptr = numeros;

    cout << "1. Valor apontado por <ptr>: " << *ptr << endl;

    ptr++;
    cout << "2. Valor apontado por <ptr>: " << *ptr << endl;

    ptr+3;
    cout << "3. Valor apontado por <ptr>: " << *ptr << endl;

    ptr--;
    cout << "4. Valor apontado por <ptr>: " << *ptr << endl;

    int *ptr1 = &numeros[0];
    int *ptr2 = &numeros[4];

    cout << "5. Valor apontado por <ptr1>: " << *ptr1 << endl;
    cout << "6. Valor apontado por <ptr2>: " << *ptr2 << endl;

    int total = *ptr1 + *ptr2;

    cout << "7. Total de elementos entre <ptr1> e <ptr2>: " << total << endl;

    if (ptr1 > ptr2)
        cout << "8. <ptr1> aponta para um elemento mais a frente no array." << endl;
    else
        cout << "8. <ptr2> aponta para um elemento mais a frente no array." << endl;

    int *ptr3 = numeros;
    int segundoElemento = *(ptr3+1);

    cout << "9. Segundo elemento no array: " << segundoElemento << endl;


    return 0;
}
