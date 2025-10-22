#include <iostream>
#include <thread>//libreria de courdas
#include <vector>
#include <cmath>
#include <chrono>//libreria del tiempo

using namespace std;
using namespace chrono;
void trabajitohulk(int id){

    auto inicio = steady_clock::now();

    double resultado = 0;
    for (int i = 0; i < 500000000; ++i){
        resultado += sin(i)*cos(i);}

    auto fin = steady_clock::now();
    auto duracion = duration_cast<milliseconds>(fin - inicio).count();

    cout << "  cuerdas " << id << " termino en " << duracion << " MS"<<endl;
}
int main() {
    cout <<"*** simulador de cpu ***"<<endl;
    cout << "cargando..."<< endl;
    cout << "******X__X*******" << endl;
    //cout << "si 2 + 2 es 4 "<< " entonces cuanto es 3 mas 3 mas mita 3"<<endl;

    int numcuerdas = thread::hardware_concurrency();
    cout << "nucleos encontrados ene el cpu: " << numcuerdas << endl;

    vector<thread> cuerdas;
    auto inicioTotal = steady_clock::now();

    for (int i = 0; i < numcuerdas; ++i){
        cuerdas.emplace_back(trabajitohulk, i +1);}

    for (auto &h : cuerdas )
        h.join();
    auto finalTotal = steady_clock::now();
    auto tiempoTotal = duration_cast<milliseconds>(finalTotal - inicioTotal).count();
    cout <<""<<endl;
    cout << "Tiempo total : " << tiempoTotal <<  "ms\n";
    cout << " Fin gracias por usar nuestros servicios!!! ";
    
    return 0;

}
