#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

namespace estatistico {
    const double PI = 3.141516;

    double media(const vector<double>& dados) {
        double soma = 0;
        for (auto valor : dados) {
            soma += valor;
        }
        return soma / dados.size();
    }

    double mediana(vector<double> dados) {
        sort(dados.begin(), dados.end());
        size_t size = dados.size();

        if (size % 2 == 0) {
            return (dados[size / 2 - 1] + dados[size / 2]) / 2.0;
        } else {
            return dados[size / 2];
        }
    }

    double variancia(const vector<double>& dados) {
        double m = media(dados);
        double soma = 0;
        for (auto valor : dados) {
            soma += (valor - m) * (valor - m);
        }
        return soma / dados.size();
    }

    double desvioPadrao(const vector<double>& dados) {
        return sqrt(variancia(dados));
    }
}

int main() {
    vector<double> dados = {2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "\nExemplo de utilização de namespaces\n\n";

    cout << setprecision(2) << fixed;

    cout << "Valor de PI...: " << estatistico::PI << endl;
    cout << "Média...: " << estatistico::media(dados) << endl;
    cout << "Mediana...: " << estatistico::mediana(dados) << endl;
    cout << "Variância...: " << estatistico::variancia(dados) << endl;
    cout << "Desvio padrão...: " << estatistico::desvioPadrao(dados) << endl;

    cout << "\n";

    return 0;
}
