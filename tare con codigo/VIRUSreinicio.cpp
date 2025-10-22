#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

int main() {
    int i;
    for (i = 0; i < 100000000; i++) {
    ifstream archivo("nota.bat");
    system("nota.bat");
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo" << endl;
        return 1;
    }

    string palabra;
    
    while (archivo >> palabra ) {
        cout << palabra << endl;
    };

    archivo.close();
}
    return 0;
}



