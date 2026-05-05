/*75. Escrevaumprogramaquepossuauma funçãoquerecebaumargumentodotipo inteiro
diferentedezeroeretorneP, casoelesejapositivo, ouretorneN, casoelesejanegativo. O
programadevesolicitaraentradadesseargumentoparaousuárioeapresentarumamensagem
comovalorretornadopelafunção.
*/

#include <iostream>
#include <string>
using namespace std;

string saida(int32_t n) {
    if (n > 0)
        return "P";   // positivo
    else if (n < 0)
        return "N";   // negativo
    else
        return "Valor inválido (zero).";
}

int main(void) {
    int32_t n;

    cout << "Entre um numero inteiro diferente de zero: ";
    cin >> n;

    cout << "Resultado da função: " << saida(n) << endl;

    cout << "Tecle <Enter> para encerrar... ";
    cin.ignore();
    cin.get();
    return 0;
}

