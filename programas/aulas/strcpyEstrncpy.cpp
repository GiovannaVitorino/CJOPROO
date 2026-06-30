#include <iostream>
#include <cstring>

using namespace std;


int main(void) {
    cout << "\nExemplo de uso de strcopy() e strncpy()\n\n";

    char nome[] = "Instituto Federal";

    char texto1[20];
    char texto2[11];

    strcpy(texto1, nome);
    strncpy(texto2, nome, 9);

    texto2[10] = '\0';

    cout << "->Nome...: " << nome << endl;
    cout << "->Texto 1: " << texto1 << endl;
    cout << "->Texto 2: " << texto2 << endl;

    cout << endl;

    return 0;
}
