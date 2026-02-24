/*função incrementar por valor*/
#include <iostream>

using namespace std;

void incrementarPorPont(int *num){
    (*num)++;
    cout << "Dentro da funcao: " << *num << endl;
}

int main(void) {
   int a = 5;

   incrementarPorPont(&a);
   cout << "Fora da funcao: " << a << endl;

    cout << "\n\n";
    return 0;
}
