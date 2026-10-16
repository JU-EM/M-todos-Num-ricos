#include <iostream>
#include <string>
#include <cmath>
using namespace std;


double aDecimal(const string& num, int base) {
    double resultado = 0;
    bool esFraccion = false;   
    double factor = 1.0;      

    for (char c : num) {
        if (c == '.') {
            esFraccion = true;
            factor = 1.0 / base;
            continue; 
        }

       
        int digito = (c >= '0' && c <= '9') ? c - '0' : toupper(c) - 'A' + 10;

        if (!esFraccion) {
            
            resultado = resultado * base + digito;
        } else {
            
            resultado += digito * factor;
            factor /= base;
        }
    }
    return resultado;
}


string deDecimal(double num, int base) {
    const string digitos = "0123456789ABCDEF";
    const int PRECISION_DECIMALES = 8; 

    bool negativo = num < 0;
    if (negativo) num = -num;

    long long parteEntera = (long long)num;
    double parteFraccionaria = num - parteEntera;

    string textoEntero;
    if (parteEntera == 0) {
        textoEntero = "0";
    } else {
        while (parteEntera > 0) {
            textoEntero = digitos[parteEntera % base] + textoEntero;
            parteEntera /= base;
        }
    }

    string textoFraccion;
    if (parteFraccionaria > 0.0000001) { 
        textoFraccion = ".";
        for (int i = 0; i < PRECISION_DECIMALES && parteFraccionaria > 0.0000001; i++) {
            parteFraccionaria *= base;
            int digito = (int)parteFraccionaria;
            textoFraccion += digitos[digito];
            parteFraccionaria -= digito;
        }
    }

    return (negativo ? "-" : "") + textoEntero + textoFraccion;
}

bool esValidoEnBase(const string& num, int base) {
    if (num.empty()) return false;

    int cantidadPuntos = 0;

    for (char c : num) {
        if (c == '.') {
            cantidadPuntos++;
            if (cantidadPuntos > 1) return false; 
            continue;
        }

        int valorDigito;
        if (c >= '0' && c <= '9') {
            valorDigito = c - '0';
        } else if (isalpha((unsigned char)c)) {
            valorDigito = toupper(c) - 'A' + 10;
        } else {
            return false; 
        }

        if (valorDigito >= base) {
            return false;
        }
    }

    if (num == ".") return false;

    return true;
}

string pedirValorValido(int base) {
    string valor;
    bool valido = false;

    do {
        cout << "Ingresa el valor en base " << base
             << " (puedes usar punto decimal, ej: 101.11): ";
        cin >> valor;

        valido = esValidoEnBase(valor, base);

        if (!valido) {
            cout << "Valor invalido para base " << base
                 << ". Verifica que no uses digitos fuera de rango o mas de un punto decimal.\n";
        }
    } while (!valido);

    return valor;
}


void mostrarConversion(double decimal, int baseOrigen) {
    if (baseOrigen != 10) cout << "Decimal:     " << decimal << endl;
    if (baseOrigen != 2)  cout << "Binario:     " << deDecimal(decimal, 2) << endl;
    if (baseOrigen != 8)  cout << "Octal:       " << deDecimal(decimal, 8) << endl;
    if (baseOrigen != 16) cout << "Hexadecimal: " << deDecimal(decimal, 16) << endl;
}

int main() {
    char respuesta;
    do {

        int opcion;
        cout << "\n--- CONVERSOR DE BASES ---\n";
        cout << "1. Decimal\n2. Binario\n3. Octal\n4. Hexadecimal\n";
        cout << "Elige la base del valor que vas a convertir: ";
        cin >> opcion;

        int base = (opcion == 1) ? 10 : (opcion == 2) ? 2 : (opcion == 3) ? 8 : 16;

   
        string valor = pedirValorValido(base);

        double decimal = aDecimal(valor, base);

  
        cout << "\nResultado:\n";
        mostrarConversion(decimal, base);

        cout << "\nDeseas seguir convirtiendo? (s/n): ";
        cin >> respuesta;

    } while (tolower(respuesta) == 's');

    cout << "\nFin del programa.\n";
    return 0;
}