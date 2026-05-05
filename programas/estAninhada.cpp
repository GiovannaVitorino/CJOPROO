#include <iostream>
#include <vector>
//exemplo 05: estruturas aninhadas


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

struct Treinador{
    string nome;
    string cidade;
    vector<Pokemon> pokemons;
};

int main(void) {
    cout << endl;
    cout << "*Exemplo de aninhamento de estruturas\n\n";

    //cria o treinador
    Treinador treinador;
    treinador.nome = "Ash Ketchun";
    treinador.cidade = "Pallet Town";

    //cria o pokemon
    Pokemon pikachu;
    pikachu.nome = "Pikachu";
    pikachu.tipo = "Eletrico";
    pikachu.nivel = 40;
    pikachu.hp = 85;

    //cria o greninja
    Pokemon greninja;
    greninja.nome = "Greninja";
    greninja.tipo = "Agua / Sombrio";
    greninja.nivel = 35;
    greninja.hp = 60;

    Pokemon hawlucha;
    hawlucha.nome = "Hawlucha";
    hawlucha.tipo = "Lutador / Voador";
    hawlucha.nivel = 32;
    hawlucha.hp = 55;

    //adiciona pokemons ao treinador
    treinador.pokemons.push_back(pikachu);
    treinador.pokemons.push_back(greninja);
    treinador.pokemons.push_back(hawlucha);

    //exibe dados
    cout << ">>Dados do treinador" << endl;
    cout << "Nome: " << treinador.nome << endl;
    cout << "Cidade: " << treinador.cidade << endl;

    cout << "Pokemons do treindador\n" << endl;

    for (int i =0; i < treinador.pokemons.size(); i++){
        cout << "Nome: " << treinador.pokemons[i].nome << endl;
        cout << "Tipo: " << treinador.pokemons[i].tipo << endl;
        cout << "Nivel: " << treinador.pokemons[i].nivel << endl;
        cout << "HP: " << treinador.pokemons[i].hp << endl;
        cout << endl;
    }

    return 0;
}
