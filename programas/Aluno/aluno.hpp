#ifndef ALUNO_H
#define ALUNO_H

#include <iostream>
using namespace std;

class Aluno {
private:
    string nome;
    string sexo;
    int idade;

public:
    // Construtor
    Aluno(string nomeAluno, string sexoAluno, int idadeAluno);

    // Getters
    string getNome() const;
    string getSexo() const;
    int getIdade() const;

    // Setters
    void setNome(string nomeAluno);
    void setSexo(string sexoAluno);
    void setIdade(int idadeAluno);

    // Método para exibir dados
    void exibirDados();
};

#endif