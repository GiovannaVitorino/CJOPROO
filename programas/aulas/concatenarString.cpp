#include <iostream>
#include <cstring>

using namespace std;


int main(void) {
    cout << "\nExemplo de uso de strcat() e strncat()\n\n";

    char parte1[50] = "Instituto";
    char parte2[] = "Federal";
    char texto[20] = "";

    strcat(parte1, parte2);
    strncat(texto, parte1, 5);


    cout << "->Parte 1: " << parte1 << endl;
    cout << "->Psrte 2: " << parte2 << endl;
    cout << "->Texto..: " << texto << endl;

    cout << endl;

    return 0;
}
