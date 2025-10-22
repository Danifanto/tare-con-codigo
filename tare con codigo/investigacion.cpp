#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>

using namespace std;

// Constantes físicas
const double CARGA_ELECTRON = 1.602e-19; // Coulombs por electrón
const double CONSTANTE_PLANCK = 6.626e-34; // J·s
const double RESISTIVIDAD_COBRE = 1.68e-8; // Ω·m

class TrazoPCB {
private:
    string nombre;
    double longitud; // en metros
    double ancho; // en metros
    double espesor; // en metros
    double corriente; // en amperes
    double resistividad; // en Ω·m

public:
    TrazoPCB(string n, double l, double a, double e, double i, double r = RESISTIVIDAD_COBRE)
    : nombre(n), longitud(l), ancho(a), espesor(e), corriente(i), resistividad(r) {}

    string getNombre() const {return nombre;}
    double getLongitud() const { return longitud;}
    double getEspesor() const { return espesor;}
    double getAncho() const { return ancho;}


    // Calcular resistencia del trazo
    double calcularResistencia() const {
    double area_seccion = ancho * espesor;
    if (area_seccion > 0) {
    return resistividad * (longitud / area_seccion);
    }
    return 0;
    }

    // Calcular densidad de corriente (A/m²)
    double calcularDensidadCorriente() const {
    double area = ancho * espesor;
    if (area > 0) {
    return corriente / area;
    }
    return 0;
    }

    // Calcular número de electrones por segundo
    double calcularElectronesPorSegundo() const {
    if (CARGA_ELECTRON > 0) {
    return corriente / CARGA_ELECTRON;
    }
    return 0;
    }

    // Calcular velocidad de deriva de electrones (m/s)
    double calcularVelocidadDeriva() const {
    double densidad_electronica = 8.5e28; // electrones/m³ para cobre
    double area = ancho * espesor;
    if (area > 0 && densidad_electronica > 0 && CARGA_ELECTRON > 0) {
    return corriente / (densidad_electronica * area * CARGA_ELECTRON);
    }
    return 0;
    }

    // Calcular caída de voltaje en el trazo
    double calcularCaidaVoltaje() const {
        return corriente * calcularResistencia();
    }

    // Mostrar información del trazo
    void mostrarInfo() const {
        cout << fixed << setprecision(6);
        cout << "|--- TRAZO: " << nombre << " " << string(nombre.length(), '---|')<< "---a" << endl;
        cout << "│ Dimensiones: " << setw(8) << (longitud * 1000) << " mm x "
        << setw(6) << (ancho * 1000) << " mm x "
        << setw(6) << (espesor * 1000) << " mm │" << endl;
        cout << "│ Corriente: " << setw(12) << corriente << " A │" << endl;
        cout << "│ Resistencia: " << setw(12) << calcularResistencia() << " Ω │" << endl;
        cout << "│ Caída voltaje:" << setw(12) << calcularCaidaVoltaje() << " V │" << endl;
        cout << "└────────────────────────────────────────────┘" << endl;
    }
};
class FlujoElectrones {
private:
vector<TrazoPCB> trazos;
double voltajeTotal;

public:
FlujoElectrones(double voltaje) : voltajeTotal(voltaje) {}

void agregarTrazo(const TrazoPCB& trazo) {
trazos.push_back(trazo);
}

void analizarFlujoElectrones() {
cout << "\n=== ANÁLISIS DE FLUJO DE ELECTRONES EN PCB ===" << endl;
cout << "Voltaje total del circuito: " << voltajeTotal << " V" << endl;
cout << "Carga del electrón: " << CARGA_ELECTRON << " C" << endl;
cout << "═══════════════════════════════════════════════" << endl;

double corrienteTotal = 0;
double resistenciaTotal = 0;

for (const auto& trazo : trazos) {
trazo.mostrarInfo();

cout << scientific << setprecision(3);
cout << " • Densidad corriente: " << setw(10) << trazo.calcularDensidadCorriente() << " A/m²" << endl;
cout << " • Electrones/segundo: " << setw(10) << trazo.calcularElectronesPorSegundo() << " e⁻/s" << endl;
cout << " • Velocidad deriva: " << setw(10) << trazo.calcularVelocidadDeriva() << " m/s" << endl;
cout << fixed;

corrienteTotal += trazo.calcularElectronesPorSegundo();
resistenciaTotal += trazo.calcularResistencia();

cout << endl;
}

mostrarResumen(corrienteTotal, resistenciaTotal);
mostrarAnalisisDetallado();
}

void mostrarResumen(double electronesTotal, double resistenciaTotal) const {
cout << "═══════════════════════════════════════════════" << endl;
cout << "RESUMEN DEL FLUJO DE ELECTRONES:" << endl;
cout << "• Total de electrones por segundo: " << scientific << setprecision(3)
<< electronesTotal << " e⁻/s" << endl;
cout << fixed << setprecision(6);
cout << "• Resistencia total del PCB: " << resistenciaTotal << " Ω" << endl;
cout << "• Corriente total: " << (electronesTotal * CARGA_ELECTRON) << " A" << endl;
}

void mostrarAnalisisDetallado() {
cout << "\n--ANÁLISIS DETALLADO POR TRAZO ---" << endl;

for (const auto& trazo : trazos) {
double electrones_por_segundo = trazo.calcularElectronesPorSegundo();
double velocidad_deriva = trazo.calcularVelocidadDeriva();
double tiempo_recorrido = trazo.getLongitud() / velocidad_deriva;

cout << "\nTrazo: " << trazo.getNombre() << endl;
cout << scientific << setprecision(3);
cout << " • Flujo electrónico: " << setw(10) << electrones_por_segundo << " e⁻/s" << endl;
cout << " • Velocidad deriva: " << setw(10) << velocidad_deriva << " m/s" << endl;
cout << fixed << setprecision(6);
cout << " • Tiempo recorrido: " << setw(10) << tiempo_recorrido << " s" << endl;
cout << " • Densidad corriente:" << scientific << setw(10)
<< trazo.calcularDensidadCorriente() << " A/m²" << endl;
}
}
void simularTiempoReal(double tiempoSegundos) {
cout << "\n--SIMULACIÓN POR " << tiempoSegundos << " SEGUNDOS ---" << endl;

for (const auto& trazo : trazos) {
double electrones_totales = trazo.calcularElectronesPorSegundo() * tiempoSegundos;
double distancia_recorrida = trazo.calcularVelocidadDeriva() * tiempoSegundos;

cout << "\nTrazo " << trazo.getNombre() << " después de " << tiempoSegundos << " s:" << endl;
cout << scientific << setprecision(3);
cout << " • Electrones que han pasado: " << setw(12) << electrones_totales << " e⁻" << endl;
cout << fixed << setprecision(6);
cout << " • Distancia recorrida: " << setw(12) << distancia_recorrida << " m" << endl;
cout << " • Porcentaje del trazo: " << setw(12)<< (distancia_recorrida / trazo.getLongitud()) * 100 << " %" << endl;
}
}
};
// Función para mostrar ejemplos de materiales
void mostrarTablaMateriales() {
cout << "\n--RESISTIVIDAD DE MATERIALES COMUNES EN PCB ---" << endl;
cout << "Material | Resistividad (Ω·m)" << endl;
cout << "------------|-------------------" << endl;
cout << "Cobre | 1.68e-8" << endl;
cout << "Oro | 2.44e-8" << endl;
cout << "Aluminio | 2.82e-8" << endl;
cout << "Plata | 1.59e-8" << endl;
cout << "Estaño | 1.09e-7" << endl;
}
// Función para calcular efectos térmicos
void calcularEfectosTermicos(const TrazoPCB& trazo) {
double resistencia = trazo.calcularResistencia();
double potencia = trazo.calcularCaidaVoltaje() * (trazo.calcularElectronesPorSegundo() * CARGA_ELECTRON);
double area_superficie = 2 * (trazo.getLongitud
    () * trazo.getAncho() + trazo.getLongitud() * trazo.getEspesor() + trazo.getAncho() * trazo.getEspesor());

cout << "\n--ANÁLISIS TÉRMICO ---" << endl;
cout << "Potencia disipada: " << scientific << setprecision(3) << potencia << " W" << endl;
cout << "Área superficial: " << fixed << setprecision(6) << area_superficie << " m²" << endl;
cout << "Densidad potencia: " << scientific << setprecision(3)
<< (potencia / area_superficie) << " W/m²" << endl;
}
int main() {
cout << "===============================================" << endl;
cout << " SIMULADOR DE FLUJO DE ELECTRONES EN PCB" << endl;
cout << "===============================================" << endl;

// Crear un circuito PCB de ejemplo
FlujoElectrones pcb(12.0); // 12V de alimentación

// Agregar trazos típicos de una PCB
pcb.agregarTrazo(TrazoPCB("Power_Bus", 0.1, 0.002, 0.000035, 2.0)); // 10cm, 2mm ancho, 35μm espesor, 2A
pcb.agregarTrazo(TrazoPCB("Señal_1", 0.05, 0.0005, 0.000035, 0.1)); // 5cm, 0.5mm ancho, 35μm, 100mA
pcb.agregarTrazo(TrazoPCB("Señal_2", 0.03, 0.0008, 0.000035, 0.05)); // 3cm, 0.8mm ancho, 35μm, 50mA
pcb.agregarTrazo(TrazoPCB("Ground", 0.08, 0.003, 0.000035, 2.0)); // 8cm, 3mm ancho, 35μm, 2A

// Mostrar tabla de materiales
mostrarTablaMateriales();

// Realizar análisis completo
pcb.analizarFlujoElectrones();

// Simular por diferentes intervalos de tiempo
pcb.simularTiempoReal(1.0); // 1 segundo
pcb.simularTiempoReal(60.0); // 1 minuto

// Análisis térmico para el trazo de potencia
calcularEfectosTermicos(TrazoPCB("Power_Bus", 0.1, 0.002, 0.000035, 2.0));

cout << "\n===============================================" << endl;
cout << " SIMULACIÓN COMPLETADA" << endl;
cout << "===============================================" << endl;

return 0;
}
