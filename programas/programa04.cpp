#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
//


using namespace std;

struct Pokemon {
    string nome;
    string tipo;
    int nivel;
    int hp;

    void aumentaHP(int pontos) {
        hp += pontos;
    }
};

int main(void) {
    cout << endl;
    cout << "* Exemplo Pokemon\n\n";

    Pokemon *ptrPokemon = new Pokemon;

    ptrPokemon->nome = "Pikachu";
    ptrPokemon->tipo = "Elétrico";
    ptrPokemon->nivel = 1;
    ptrPokemon->hp = 1;

    cout << ">> Dados do pokemon\n" << endl;
    cout << "Nome: " << ptrPokemon->nome << endl;
    cout << "Tipo: " << ptrPokemon->tipo << endl;
    cout << "Nivel: " << ptrPokemon->nivel << endl;
    cout << "HP: " << ptrPokemon->hp << endl;
    cout << endl;

    cout << ">> Um Pokemon selvagem apareceu...Vamos batalhar!\n\n";
    cout << "Seu Pikachu venceu uma luta muito dificil... ";
    cout << "Ele ganhou 50 pontos\n";

    ptrPokemon->aumentaHP(50);

    cout << "Olhe, o que está acontecendo? Seu Pokemon está brilhando!\n";
    ptrPokemon->nivel++;

    cout << "O Pikachu subiu de nivel!\n\n";

    cout << ">> Dados do pokemon\n" << endl;
    cout << "Nome: " << ptrPokemon->nome << endl;
    cout << "Tipo: " << ptrPokemon->tipo << endl;
    cout << "Nivel: " << ptrPokemon->nivel << endl;
    cout << "HP: " << ptrPokemon->hp << endl;
    cout << endl;

    delete ptrPokemon;

    return 0;
}
