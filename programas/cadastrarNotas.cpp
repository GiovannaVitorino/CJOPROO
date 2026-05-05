#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

struct Cadastro {
    string nome;
    vector<float> notas;
    float media;
};

float calcularMedia(const vector<float> &notas);
bool compararNomes(const Cadastro &a, const Cadastro &b);

int main(void) {
    cout << "\nCadastro de notas escolares\n\n";

    vector<Cadastro> alunos;

    int totalAlunos;
    int totalNotas;
    float mediaGlobal = 0.0f;

    cout << "Informe o total de alunos: ";
    cin >> totalAlunos;

    cout << "Informe o total de notas: ";
    cin >> totalNotas;

    cout << endl;

    for (int i = 0; i < totalAlunos; i++) {
        Cadastro aluno;

        cout << "Informe o nome do aluno " << i+1 << ": ";
        getline(cin >> ws, aluno.nome);

        cout << "Informe a linha com as " << totalNotas << " notas: ";
        string linhaNotas;
        getline(cin, linhaNotas);
        istringstream stream(linhaNotas);

        float notaTemp;
        while (stream >> notaTemp) {
            aluno.notas.push_back(notaTemp);
        }

        aluno.media = calcularMedia(aluno.notas);
        alunos.push_back(aluno);

        mediaGlobal += aluno.media;
        cout << endl;
    }

    mediaGlobal /= totalAlunos;

    sort(alunos.begin(), alunos.end(), compararNomes);

    cout << setprecision(2) << fixed;
    cout << "Resultado final\n\n";

    for (const auto& aluno : alunos) {
        cout << "Aluno: " << aluno.nome << endl;
        cout << "Notas: ";
        for (float nota : aluno.notas) {
            cout << nota << " ";
        }
        cout << "\nMedia: " << aluno.media << endl;
        cout << endl;
    }

    cout << "Media Global da turma: " << mediaGlobal << "\n\n";

    return 0;
}

float calcularMedia(const vector<float> &notas) {
    float soma = 0.0f;
    for (float nota : notas) {
        soma += nota;
    }
    return notas.empty() ? 0.0f : soma / notas.size();
}

bool compararNomes(const Cadastro &a, const Cadastro &b) {
    return a.nome < b.nome;
}
