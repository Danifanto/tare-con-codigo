#include <iostream>
#include <iomanip>//manipulador de formatado (fixed,setprecision)para que den dos numero decimales
#include <vector>//para vectores(arrays)
#include <limits>//para limpiar la entrada cuando hay errores
#include <string>//lib para escirbir 
#include <fstream>//lib para leer archivos
#include <chrono>//libreria del tiempo
#include <ctime>//libreria del tiempo


using namespace std;
using namespace chrono;
string cliente; 
string correo;
//estructura del producto
struct Producto {
    string nombre;
    float precio;
    int cantidad = 0;
//metodo que devuelve precio * cantidad
    float total() const { //esta como constante por que modifica el objeto
        return precio * cantidad;
    }
};

void limpiesadePantalla() {// para limpieza de pantalla
    #ifdef _WIN32
        system("cls"); // para windows
    #else
        system("clear");// para unix
    #endif
}
//funcion para mostrar menú de productos
void mostrarMenu(const vector<Producto>& productos) {//vector del producto
    cout << "====================================="<< endl;
    cout << "========== tienda DANIELS ===========" << endl;
    cout << "====================================="<< endl;
    //bucle para que se muestren los valores del vector producto
    for (size_t i = 0; i < productos.size(); ++i) {
        cout << i + 1 << ". " << productos[i].nombre << " | $" << fixed << setprecision(2) << productos[i].precio <<" | cantidad: " << productos[i].cantidad << "\n";
    }
    cout <<endl<< "0. Ver total y pagar \n";
    cout << "99. salir\n";
    cout << "Elige sus productos : ";
}

//funcion que usamos para calcular el total del carrito 
float calcularTotal(const vector<Producto>& productos, float &subtotal, float &itbms) {//aqui usamos el & para que devuelva los valores al llamador ademas del return
    subtotal = 0.0f;
    //recorre los prodcutos y suma p.total, para obtener el subtotal.
    for (const auto& p : productos){
        subtotal += p.total();
    }
    itbms = subtotal * 0.07f;//calcula itbms como 7%(0.07f) y devuelve el  subtotal + ibtms
    return subtotal + itbms;
}

// funcion de la factura 
void imprimirFactura(const vector<Producto>& productos, float subtotal, float itbms, float total, float pago, float cambio) {
    limpiesadePantalla();//limpia y imprimir el encabesado
    /*cout <<"========== FACTURA =========="<< endl;
    cout << "Cliente: Daniels\n";
    for (const auto& p : productos) {//for para imprimir los productos
        if (p.cantidad > 0) {//con la condicion  mayor a 0
            cout << p.nombre << " x" << p.cantidad << " =$" << p.total() << "\n";
        }
    }
    cout << "-----------------------------\n";
    cout << "Substotal: $" <<fixed << setprecision(2) << subtotal << "\n";
    //itbms = subtotal * 0.07f;
    cout << "ITBMS (7%): $" <<fixed << setprecision(2)<< itbms << "\n";
    cout << "total: $" <<fixed << setprecision(2)<< total << "\n";
    cout << "Pago: $" <<fixed << setprecision(2)<< pago << "\n";
    cout << "cambio: $ " <<fixed << setprecision(2)<< cambio << "\n";
    cout << "=============================\n";*/
    cout << " ingrese el nombre del Cliente:"<<endl;
    cin >> cliente;
    cout << "ingrese su correo electronico"<<endl;
    cin >> correo;
    ofstream escribir("estudiantes.txt");
if (escribir.is_open()) {
    escribir << "============================== DGI ===============================" << endl;
    escribir << "========== COMPROVANTE AUXILIAR DE FACTURA ELECTRONICA ===========" << endl;
    escribir << "RUC: 11.111.111-1" << "D.V.61" << endl;
    escribir << "C.Comercial Albrook mall" << endl;
    escribir << "" << endl;
    escribir << "========================== TIENDAS DANIELS =========================" << endl;
    escribir << "======================== Tus mejores amigos ========================" << endl;
    escribir << "" << endl;
    escribir << "======================== sucursal Albrook mall =====================" << endl;
    escribir << "======================== Tel: +507 6530-5913 =======================" << endl;
    escribir << "____________________________________________________________________" << endl;
    escribir << "" << endl;
    escribir << "Tipo: Factura electrónica                      Numero: 2021-2022-001" << endl;
    auto ahora = system_clock::now();
    time_t tiempoActual = system_clock::to_time_t(ahora);
    escribir << "fecha y hora: "<< ctime(&tiempoActual) <<"                          "<< endl;
    escribir << "Surcursal: 06-surcursal ala  caja /Pto Fact:  06-1" << endl;
    escribir << "Tipo de receptor: consumidor final" << endl;
    escribir << "Cliente: " << cliente<< endl;
    escribir << "RUC/ID: 8 1003 719 DV:"<<endl;
    escribir << "Direccion:  PANAMA,ciudad de Panama."<<endl;
    escribir << "____________________________________________________________________"<<endl;
    escribir << ""<<endl;
    escribir << "DESCRIOCION                                                   PRECIO"<< endl;
    for (const auto& p : productos) {//for para imprimir los productos
        if (p.cantidad > 0) {//con la condicion  mayor a 0
    escribir << p.nombre << " x" << p.cantidad << ":                                                     $ " <<fixed << setprecision(2) << p.total() << endl;
        }
    }
    escribir << "____________________________________________________________________"<<endl;
    escribir << "Substotal:                                                    $ " <<fixed << setprecision(2) << subtotal << "\n";
    //itbms = subtotal * 0.07f;
    escribir << "ITBMS (7%):                                                   $ " <<fixed << setprecision(2)<< itbms << "\n";
    escribir << "total:                                                        $ " <<fixed << setprecision(2)<< total << "\n";
    escribir << "Pago:                                                         $ " <<fixed << setprecision(2)<< pago << "\n";
    escribir << "cambio:                                                       $ " <<fixed << setprecision(2)<< cambio << "\n";
    escribir << "____________________________________________________________________\n";
    escribir << "               gracias por comprar en nuestras tiendas              " <<endl;

    escribir.close();
}

// Leer y procesar datos
ifstream leer("estudiantes.txt");
string linea;

if (leer.is_open()) {
cout << "Lista de estudiantes:" << endl;
while (getline(leer, linea)) {
cout << "Datos: " << linea << endl;
}
leer.close();
}
}

int main() {
    int tomarOtroCliente = 1;
    int areas,tipodearea;
    while (tomarOtroCliente == 1){//while nos permite tomar multiples clientes
        
        cout << "====================================="<< endl;
        cout << "========== tienda DANIELS ===========" << endl;
        cout << "====================================="<< endl;
        cout << "========== area de la tienda ===========" << endl;
        cout << "====================================="<< endl;
        cout << "Seleccione un area:\n";
        cout << "1. Comida (1 - 100)\n";
        cout << "2. Carnes (1 - 50)\n";
        cout << "3. Embutidos (1 - 100)\n";
        cout << "4. Bebidas (1 - 100)\n";
        cout << "5. Aceo personal (1 - 100)\n";
        cout << "6. Maquillaje (1 - 100)\n";
        cout << "7. Limpieza (1 - 100)\n";
        cout << "8. Hogar (1 - 100)\n";
        cout << "9. Ropa (1 - 100)\n";
        cout << "10. Ferreteria (1 - 100)\n";
        cout << "Ingrese su opción: ";
        cin >> areas; 
        vector<Producto> productos;
        switch (areas) { //carga las listas de las areas 
                case 1://comida
                    {
                    cout<<"Comida"<<endl;
                    productos = {
                    {"pasta", 1.00f},
                    {"azucar", 1.50f},
                    {"porotos", 2.00f},
                    {"molde de pan", 2.00f},
                    {"corn flakes", 2.50f},
                    {"chocolate", 2.00f},
                    {"galletas", 2.00f},
                    {"sal", 2.00f},
                    {"aceite", 3.00f},
                    {"sopa china", 3.00f}
                    };
                    }
                    break;
                case 2://carnes
                    {
                    cout<<"Carnes"<<endl;
                    productos = {
                    {"carne de res ", 1.00f},
                    {"pollo lb", 1.50f},
                    {"carne de cerdo", 2.00f},
                    {"pechuga de pollo", 2.00f},
                    {"mollejas", 2.50f},
                    {"carne molida", 2.00f},
                    {"jarrate", 2.00f},
                    {"mondongo", 2.00f},
                    {"pezcado", 3.00f},
                    {"higado de res", 3.00f}
                    };
                    }
                    break;
                case 3: //embutidos
                    {
                    cout<<"embutidos"<<endl;
                    productos = {
                    {"queso amarillo ", 1.00f},
                    {"queso cabra", 1.50f},
                    {"tocino", 2.00f},
                    {"bacon", 2.00f},
                    {"peperoni", 2.50f},
                    {"mortadela", 2.00f},
                    {"salchicha", 2.00f},
                    {"chorizo de cerdo", 2.00f},
                    {"chorizo de pollo", 3.00f},
                    {"jamon", 3.00f}
                    };
                    }
                    break;
                case 4: //bebidas
                    {
                    cout<<"bedidas"<<endl;
                    productos = {
                    {"coca cola", 1.00f},
                    {"balboa roja", 1.50f},
                    {"jugo de limon", 2.00f},
                    {"leche", 2.00f},
                    {"agua", 2.50f},
                    {"jugo de naranja", 2.00f},
                    {"chocolate", 2.00f},
                    {"agua de piapa", 2.00f},
                    {"vino", 3.00f},
                    {"vodka", 3.00f}
                    };
                    }
                    break;
                case 5://aceo personal
                    {
                    cout<<"aceo personal"<<endl;
                    productos = {
                    {"jabon de bañarse ", 1.00f},
                    {"shampoo", 1.50f},
                    {"talco", 2.00f},
                    {"pasta de dientes", 2.00f},
                    {"cepillo de dientes", 2.50f},
                    {"toalla sanitaria", 2.00f},
                    {"rasuradora", 2.00f},
                    {"desodorante", 2.00f},
                    {"tuallitas humedas", 3.00f},
                    {"crema de peinar", 3.00f}
                    };
                    }
                    break;
                case 6://maquillaje
                    {
                    cout<<"maquillaje"<<endl;
                    productos = {
                    {"rubor ", 1.00f},
                    {"labial", 1.50f},
                    {"sombras de ojos", 2.00f},
                    {"brochas", 2.00f},
                    {"base liquida", 2.50f},
                    {"desmaquillaje", 2.00f},
                    {"lapiz de ceja", 2.00f},
                    {"deliniador", 2.00f},
                    {"polvo facial", 3.00f},
                    {"crema facial", 3.00f}
                    };
                    }
                    break;
                case 7://limpieza
                    {
                    cout<<" limpieza"<<endl;
                    productos = {
                    {"bajon xedes ", 1.00f},
                    {"cloro", 1.50f},
                    {"desinfectante lavanda", 2.00f},
                    {"escoba", 2.00f},
                    {"trapeador", 2.50f},
                    {"bicarbonato de cocina", 2.00f},
                    {"jabon de fregar", 2.00f},
                    {"papel higiénico", 2.00f},
                    {"pastilla de olor", 3.00f},
                    {"suabitel", 3.00f}
                    };
                    }
                    break;
                case 8://Hogar
                    {
                    cout<<"hogar"<<endl;
                    productos = {
                    {"estufa ", 1.00f},
                    {"refri", 1.50f},
                    {"haspiradora ", 2.00f},
                    {"parrilla", 2.00f},
                    {"sillon", 2.50f},
                    {"abanico", 2.00f},
                    {"tollas de bañarse", 2.00f},
                    {"escritorio", 2.00f},
                    {"silla escritorio", 3.00f},
                    {"cortinas", 3.00f}
                    };
                    }
                    break;
                case 9: //ropa
                    {
                    cout<<"ropa"<<endl;
                    productos = {
                    {"sueters ", 1.00f},
                    {"pamtalon jeans", 1.50f},
                    {"camisa", 2.00f},
                    {"pantalon de tela", 2.00f},
                    {"boxers", 2.50f},
                    {"faldas", 2.00f},
                    {"blusa", 2.00f},
                    {"vestido de mujer", 2.00f},
                    {"pantis", 3.00f},
                    {"bresiel", 3.00f},
                    {"sandalias de mujer", 2.00f},
                    {"gorras", 3.00f},
                    {"corbata", 3.00f},
                    };
                    }
                    break;
                case 10://ferreteria
                    {
                    cout<<"ferreteria"<<endl;
                    productos = {
                    {"martillos ", 1.00f},
                    {"pala", 1.50f},
                    {"clavos", 2.00f},
                    {"semento", 2.00f},
                    {"arena", 2.50f},
                    {"piedra", 2.00f},
                    {"puerta", 2.00f},
                    {"ventanas", 2.00f},
                    {"destornilladora", 3.00f},
                    {"zinc", 3.00f}
                    };
                    }
                    break;    
                default:
                    cout <<("la opcion no es valida.\n");
                    break;
            }
            int opcion;
            float subtotal, itbms, total, pago, cambio;


        while (true) {
            limpiesadePantalla();
            mostrarMenu(productos);
            std::cin >> opcion;

            if (cin.fail()) {//detecta si escribiste mal,detecta entradas no numericas se limpia con cin clear y  se descarta la linea restante con cin ignore
                std::cin.clear();//recetea el error para cin vuelva a funcionar, por que si no puede seguir leyendo datos asta que se limpie cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n');//limpia la basura en el buffer o descarta lo que el usuario escribio mal para que no moleste en la siguiente lectura
                cout << "Opcion no valida. Presione enter para continuar...";
                cin.get();// espera que el usuario presione enter y para pausar el programa
                continue;
            }
            if (opcion == 99) {
                cout << "gracias por tu compra. hasta luego!!!\n";
                break;
            }

            if (opcion == 0) {
                total = calcularTotal(productos, subtotal, itbms); // aqui se llama la funcion  calculartotal para sacar el total y pagar 
                cout << "\nSubtotal : $ "<< subtotal << endl;
                cout << "ITBMS : $ " << itbms << endl;
                cout << "TOTAL A PAGAR: $" << total <<  "\n";
                cout << "Ingresa el total con el monto que pagas: $";
                cin >> pago;
                // si el dinero es menor al total se enviara un mensaje 
                if (pago < total) {
                    cout << "Dinero suficiente . presiona Enter para volver...";
                    cin.ignore();
                    cin.get();
                    continue;
                }
                cambio = pago - total;
                imprimirFactura(productos, subtotal, itbms, total, pago, cambio);
                cout << "Presiona Eneter para salir...";
                cin.ignore();
                cin.get();
                break;
            }
            if (opcion >= 1 && opcion <= (int)productos.size()) {
                productos [opcion - 1].cantidad++;
                cout << "Agregaste : " <<productos[opcion - 1].nombre <<"\n";
                cout <<"Presiona Enter para continuar...";
                cin.ignore();
                cin.get();
            }else{
                cout <<"Opncion no valida . Presione Enter...";
                cin.ignore();
                cin.get();
            }
        }
        cout << "Quieres tomar otro cliente?(1 = si y 0 = no) ";
        cin >> tomarOtroCliente;
    }
    return 0;}
