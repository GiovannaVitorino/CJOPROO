#include <iostream>
using namespace std;

class Teste {
    public:
    // Construtor
        Teste(std::string nome, int idade) {
            cout << "Teste" << endl;
        }

        // Destrutor
        // ~Teste() {
        //     cout << "Teste" << endl;
        // }

        //Getters
        std::string getNome(std::string nome) const {
            return nome;
        }

        int getIdade(int idade) const {
            return idade;
        }

        private:
        std::string nome;
        int idade;
};

int main() {
    Teste pessdoa("Joao", 20);
    cout << "Acessando membros do objeto diretamente" << endl;
    cout << pessdoa.getNome("Joao") << endl;
    cout << pessdoa.getIdade(20) << endl;

    cout << "Acessando membros do objeto através do ponteiro" << endl;
    Teste* pessoa = &pessdoa; // pessoa é um ponteiro para o objeto pessdoa

    cout << "Endereco de memoria do objeto pessoa: " << &pessoa << endl;
    cout << pessoa->getNome("Joao") << endl;
    cout << pessoa->getIdade(20) << endl;

    cin.get();
    return 0;
}
