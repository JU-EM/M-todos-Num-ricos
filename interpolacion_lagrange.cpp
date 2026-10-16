#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

const int MAX = 100; 


double leer(const char* mensaje) {
    double v;
    cout << mensaje;
    if (!(cin >> v)) {
        cout << "\nEntrada invalida. Programa terminado.\n";
        exit(1);
    }
    return v;
}




double pesoL(double x[], int n, int i, double xq) {
    double L = 1;
    for (int j = 0; j < n; j++) {
        if (j != i) L = L * (xq - x[j]) / (x[i] - x[j]);
    }
    return L;
}


double lagrange(double x[], double fx[], int n, double xq) {
    double suma = 0;
    for (int i = 0; i < n; i++) {
        suma = suma + fx[i] * pesoL(x, n, i, xq);
    }
    return suma;
}


double pixelX(double x, double xmin, double xmax) {
    return 60 + (x - xmin) / (xmax - xmin) * 700;
}
double pixelY(double y, double ymin, double ymax) {
    return 440 - (y - ymin) / (ymax - ymin) * 380;
}

void graficar(double x[], double fx[], int n, double xq, double gq) {

    double xmin = x[0], xmax = x[n - 1];
    if (xq < xmin) xmin = xq;
    if (xq > xmax) xmax = xq;


    double ymin = gq, ymax = gq;
    for (int k = 0; k <= 200; k++) {
        double xs = xmin + (xmax - xmin) * k / 200;
        double ys = lagrange(x, fx, n, xs);
        if (ys < ymin) ymin = ys;
        if (ys > ymax) ymax = ys;
    }
    for (int i = 0; i < n; i++) {
        if (fx[i] < ymin) ymin = fx[i];
        if (fx[i] > ymax) ymax = fx[i];
    }
    double margenX = (xmax - xmin) * 0.05;
    double margenY = (ymax - ymin) * 0.10;
    if (margenY == 0) margenY = 1;  
    xmin -= margenX;  xmax += margenX;
    ymin -= margenY;  ymax += margenY;

    ofstream f("grafica_lagrange_simple.svg");
    f << "<svg xmlns='http://www.w3.org/2000/svg' width='800' height='500' "
         "font-family='sans-serif' font-size='13'>\n";
    f << "<rect width='800' height='500' fill='white'/>\n";
    f << "<text x='400' y='30' text-anchor='middle' font-size='18'>"
         "Interpolacion de Lagrange</text>\n";

   
    f << "<rect x='60' y='60' width='700' height='380' fill='none' "
         "stroke='black'/>\n";
    f << "<text x='60' y='460'>" << xmin << "</text>\n";
    f << "<text x='760' y='460' text-anchor='end'>" << xmax << "</text>\n";
    f << "<text x='55' y='440' text-anchor='end'>" << ymin << "</text>\n";
    f << "<text x='55' y='70' text-anchor='end'>" << ymax << "</text>\n";
    f << "<text x='410' y='485' text-anchor='middle'>x</text>\n";

    
    f << "<polyline fill='none' stroke='red' stroke-width='2' points='";
    for (int k = 0; k <= 200; k++) {
        double xs = xmin + (xmax - xmin) * k / 200;
        double ys = lagrange(x, fx, n, xs);
        f << pixelX(xs, xmin, xmax) << "," << pixelY(ys, ymin, ymax) << " ";
    }
    f << "'/>\n";

   
    for (int i = 0; i < n; i++) {
        double px = pixelX(x[i], xmin, xmax);
        double py = pixelY(fx[i], ymin, ymax);
        f << "<circle cx='" << px << "' cy='" << py << "' r='5' fill='blue'/>\n";
        f << "<text x='" << px + 8 << "' y='" << py - 8 << "' fill='blue'>("
          << x[i] << ", " << fx[i] << ")</text>\n";
    }

   
    double qx = pixelX(xq, xmin, xmax);
    double qy = pixelY(gq, ymin, ymax);
    f << "<circle cx='" << qx << "' cy='" << qy << "' r='7' fill='green'/>\n";
    f << "<text x='" << qx + 10 << "' y='" << qy + 22 << "' fill='green'>g("
      << xq << ") = " << gq << "</text>\n";

    f << "</svg>\n";
}

int main() {
    double x[MAX], fx[MAX];  


    int n = (int)leer("Ingrese la cantidad de Datos 'i' (2 a 100): ");
    while (n < 2 || n > MAX)
        n = (int)leer("  Debe estar entre 2 y 100. Intente de nuevo: ");


    for (int i = 0; i < n; i++) {
        cout << "Posicion " << i << " :\n";
        x[i] = leer("Datos en X: ");
        while (i > 0 && x[i] <= x[i - 1])
            x[i] = leer("  X debe ser mayor que el anterior. Intente de nuevo: ");
        fx[i] = leer("Datos en f(x): ");
        cout << "\n";
    }


    double xq = leer("Ingrese el valor de X para  g(x): ");
    if (xq < x[0] || xq > x[n - 1])
        cout << "Aviso: X esta fuera del rango, se hara EXTRAPOLACION.\n";


    double gq = lagrange(x, fx, n, xq);


    cout << "\n------------------------------------------------\n";
    cout << "i\tDato X\tDato f(x)\tL_i(X)\n";
    cout << "------------------------------------------------\n";
    double sumaL = 0;
    for (int i = 0; i < n; i++) {
        double L = pesoL(x, n, i, xq);
        sumaL = sumaL + L;
        cout << i << "\t" << x[i] << "\t" << fx[i] << "\t\t" << L << "\n";
    }
    cout << "------------------------------------------------\n";
    cout << "Suma de los L_i(X) = " << sumaL << "  (debe ser 1)\n";
    cout << "La Respuesta en g(" << xq << ") es: " << gq << "\n";


    graficar(x, fx, n, xq, gq);
    cout << "\nGrafica guardada en 'grafica_lagrange_simple.svg' (abrela en el navegador).\n";

    return 0;
}