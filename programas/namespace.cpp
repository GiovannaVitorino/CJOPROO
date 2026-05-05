#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

namespace estatistico{
    double PI = 3.141516;
    double media (const vector <double>& dados);
    double soma =0;
    for (auto valor : dados);
    return soma / dados.size
}

    double mediana (vector <double> dados){
        sort (dados.begin(), dados.end());

        size_t size = dados dados.size();

        if (size % 2 == 0){
            return (dados[size / 2 - 1] + dados[size / 2]) /2;

        }

        else{return dados[size / 2 ];

        }
    double variancia (const vector <double>& dados){
        double m = media(dados);
        double soma = 0;
    }
    for (auto valor : dados){
        soma += (valor -m) * (valor - m);
    }
    return soma / dados.size();
    }

    double desvioPadrao (const vector <double>& dados){
    return sqrt(variancia)
    }
}


int main(void) {
    vector<double> dados = {2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "\nExemplo de utilização de namespaces\n\n";

    cout << setprecision(2);
    cout << setiosflags(ios::fixed);

    cout << "Valor de PI...: " << estatistici::PI << endl;
    cout << "Media...: " << estatistici::media(dados) << endl;
    cout << "mediana...: " << estatistici::mediana(dados) << endl;
    cout << "Variancia...: " << estatistici::variancia(dados) << endl;
    cout << "Desvio padrao...: " << estatistici::desvioPadrao(dados) << endl;

    cout << "\n";

 return 0;
}

