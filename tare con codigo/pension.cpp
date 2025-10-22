#include  <iostream>
#include  <fstream>
#include  <vector>
#include  <iomanip>

using namespace std;
double calcularPension(double salario, int hijos) {
    double porcentaje = 0.0;
    if (hijos == 1) {
        porcentaje = 0.20;
    } else if (hijos == 2) {
        porcentaje = 0.30;
    } else if (hijos >= 3) {
        porcentaje = 0.40;
    }
    return salario * porcentaje;}
int main() {
    vector<double> salarios = {636.80, 950.00, 1500.00, 1800.00, 2000.00};

    double datos[5][3];

    for (int i = 0; i < 5; i++) {
        int hijos;
        cout << "Ingrese el numero de hijos del hombre " << (i + 1) << " (salario: $" << salarios[i] << "): ";
        cin >> hijos;

        double pension = calcularPension(salarios[i], hijos);

        datos[i][0] = salarios[i];
        datos[i][1] = hijos;
        datos[i][2] = pension;
    }

    ofstream archivo("pensiones_alimenticias.doc");
    if (archivo.is_open()) {
        archivo << fixed << setprecision(2);
        archivo << "=== PENSIONES ALIMENTICIAS (Ley 42 - Panama) ===\n\n";
        for (int i = 0; i < 5; i++) {
            archivo << "Hombre " << (i + 1) << ":\n";
            archivo << "  Salario: $" << datos[i][0] << "\n";
            archivo << "  Hijos: " << (int)datos[i][1] << "\n";
            archivo << "  Pension: $" << datos[i][2] << "\n\n";
        }
        archivo.close();
        cout << "\nResultados guardados en 'pensiones_alimenticias.txt'\n";
    } else {
        cerr << "Error al abrir el archivo.\n";
    }
    return 0;}
