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


double pixelX(double x, double xmin, double xmax) {
    return 60 + (x - xmin) / (xmax - xmin) * 700;
}
double pixelY(double y, double ymin, double ymax) {
    return 440 - (y - ymin) / (ymax - ymin) * 380;
}


void graficar(double x[], double y[], int n, double xq, double yq) {
  
    double xmin = x[0], xmax = x[n - 1];
    double ymin = yq, ymax = yq;
    if (xq < xmin) xmin = xq;
    if (xq > xmax) xmax = xq;
    for (int i = 0; i < n; i++) {
        if (y[i] < ymin) ymin = y[i];
        if (y[i] > ymax) ymax = y[i];
    }
    double margenX = (xmax - xmin) * 0.05;
    double margenY = (ymax - ymin) * 0.10;
    if (margenY == 0) margenY = 1;  
    xmin -= margenX;  xmax += margenX;
    ymin -= margenY;  ymax += margenY;

    ofstream f("grafica_lineal_simple.svg");
    f << "<svg xmlns='http://www.w3.org/2000/svg' width='800' height='500' "
         "font-family='sans-serif' font-size='13'>\n";
    f << "<rect width='800' height='500' fill='white'/>\n";
    f << "<text x='400' y='30' text-anchor='middle' font-size='18'>"
         "Interpolacion lineal</text>\n";

 
    f << "<rect x='60' y='60' width='700' height='380' fill='none' "
         "stroke='black'/>\n";
    f << "<text x='60' y='460'>" << xmin << "</text>\n";
    f << "<text x='760' y='460' text-anchor='end'>" << xmax << "</text>\n";
    f << "<text x='55' y='440' text-anchor='end'>" << ymin << "</text>\n";
    f << "<text x='55' y='70' text-anchor='end'>" << ymax << "</text>\n";
    f << "<text x='410' y='485' text-anchor='middle'>x</text>\n";


    f << "<polyline fill='none' stroke='red' stroke-width='2' points='";
    for (int i = 0; i < n; i++)
        f << pixelX(x[i], xmin, xmax) << "," << pixelY(y[i], ymin, ymax) << " ";
    f << "'/>\n";


    for (int i = 0; i < n; i++) {
        double px = pixelX(x[i], xmin, xmax);
        double py = pixelY(y[i], ymin, ymax);
        f << "<circle cx='" << px << "' cy='" << py << "' r='5' fill='blue'/>\n";
        f << "<text x='" << px + 8 << "' y='" << py - 8 << "' fill='blue'>("
          << x[i] << ", " << y[i] << ")</text>\n";
    }


    double qx = pixelX(xq, xmin, xmax);
    double qy = pixelY(yq, ymin, ymax);
    f << "<circle cx='" << qx << "' cy='" << qy << "' r='7' fill='green'/>\n";
    f << "<text x='" << qx + 10 << "' y='" << qy + 22 << "' fill='green'>("
      << xq << ", " << yq << ")</text>\n";

    f << "</svg>\n";
}

int main() {
    double x[MAX], y[MAX];  


    int n = (int)leer("Ingrese la cantidad de Datos 'i' (2 a 100): ");
    while (n < 2 || n > MAX)
        n = (int)leer("  Debe estar entre 2 y 100. Intente de nuevo: ");


    for (int i = 0; i < n; i++) {
        cout << "Posicion " << i << " :\n";
        x[i] = leer("Datos en X: ");
        while (i > 0 && x[i] <= x[i - 1])
            x[i] = leer("  X debe ser mayor que el anterior. Intente de nuevo: ");
        y[i] = leer("Datos en Y: ");
        cout << "\n";
    }


    double xq = leer("Ingrese el valor de X a interpolar: ");
    if (xq < x[0] || xq > x[n - 1])
        cout << "Aviso: X esta fuera del rango, se hara EXTRAPOLACION.\n";

    int i = 0;
    while (i < n - 2 && xq > x[i + 1]) i++;


    double x0 = x[i],     y0 = y[i];
    double x1 = x[i + 1], y1 = y[i + 1];


    double m = (y1 - y0) / (x1 - x0);


    double yq = y0 + m * (xq - x0);


    cout << "\n--------------------------------------\n";
    cout << "i\tDato X\tDato Y\n";
    cout << "--------------------------------------\n";
    for (int k = 0; k < n; k++) cout << k << "\t" << x[k] << "\t" << y[k] << "\n";
    cout << "--------------------------------------\n";
    cout << "Puntos usados: (x0, y0) = (" << x0 << ", " << y0 << ")  y  (x1, y1) = ("
         << x1 << ", " << y1 << ")\n";
    cout << "Pendiente m = " << m << "\n";
    cout << "La Respuesta para X = " << xq << " es: Y = " << yq << "\n";

    graficar(x, y, n, xq, yq);
    cout << "\nGrafica guardada en 'grafica_lineal_simple.svg' (abrela en el navegador).\n";

    return 0;
}