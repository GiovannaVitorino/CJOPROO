/*função incrementar por valor*/
#include <iostream>

using namespace std;

void incrementarPorRef(int &num){
    num++;
    cout << "Dentro da funcao: " << num << endl;
}

int main(void) {
   int a = 5;

   incrementarPorRef(a);
   cout << "Fora da funcao: " << a << endl;

    cout << "\n\n";
    return 0;
}
