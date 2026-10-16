#include <iostream>
#include <iomanip>

using namespace std;

int main() {

    const int n = 100001;

    float numeros[n];

    numeros[0] = 1.0f;

    for (int i = 1; i < n; i++) {
        numeros[i] = 0.000001f;
    }

    float suma_sin_agrupar = 0.0f;

    for (int i = 0; i < n; i++) {
        suma_sin_agrupar += numeros[i];
    }

    float pequeños = 0.0f;

    for (int i = 1; i < n; i++) {
        pequeños += numeros[i];
    }

    float suma_agrupada = 1.0f + pequeños;

   

    cout << "Sin agrupar: " << suma_sin_agrupar << endl;

     cout << fixed << setprecision(2);
     
    cout << "Agrupada:    " << suma_agrupada << endl;

    cout << "Ideal:       1.1000000000" << endl;

    return 0;
}