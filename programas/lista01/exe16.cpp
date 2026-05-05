/* Escreva um programa que peça o tamanho de um arquivo para download (em MB)
e a velocidade de um link de Internet (em Mbps). Em seguida, o programa deve
calcular e informar o tempo aproximado de download do arquivo utilizando este
link (em minutos)*/

#include <iostream>

using namespace std;

int main(void){
    int16_t tam, vel, tempo;

    cout << "Tamanho do arquivo (MB): ";
    cin >> tam;

    cout << "Velocidade do link (Mbps): ";
    cin >> vel;

    tempo = ((tam * 8) / vel) / 60.0;

    cout << "\nTempo aproximado de download: " << tempo << "min" << endl;

    cout << endl;
    cout << "Tecle <Enter> para encerrar... ";
    cin.ignore();
    cin.get();
    return 0;
}
