#include "aluno.hpp"

Aluno::Aluno(string nomeAluno, string sexoAluno, int idadeAluno) {
    nome = nomeAluno;
    sexo = sexoAluno;
    idade = idadeAluno;
}

string Aluno::getNome() const {
        return nome;
    }

    void Aluno::setNome(string nomeAluno){
        nome = nomeAluno;
    }

    string Aluno::getSexo() const {
        return sexo;
    }

        void Aluno::setSexo(string sexoAluno){
            sexo = sexoAluno;
        }

    int Aluno::getIdade() const {
        return idade;
    }

    void Aluno::setIdade(int idadeAluno){
        idade = idadeAluno;
    }


void Aluno::exibirDados() {
    cout << "Nome: " << nome << endl;
    cout << "Sexo: " << sexo << endl;
    cout << "Idade: " << idade << endl;
}
