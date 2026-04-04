#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main() {

    int opcion;
    string nombreLiga;
int puntosGanar, puntosEmpate, puntosPerder;

    do {
        cout << "\n=== SISTEMA DE LIGA ===\n";
        cout << "1. Ver tabla de posiciones\n";
        cout << "2. Registrar partido\n";
        cout << "3. Ver jornadas\n";
        cout << "4. Ver partidos\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
           case 1: {
    ifstream archivo("data/config.txt");

    if (!archivo) {
        cout << "Error al abrir config.txt\n";
        break;
    }

    string linea;

    while (getline(archivo, linea)) {

        if (linea.empty()) continue;

        stringstream ss(linea);
        string clave, valor;

        getline(ss, clave, '=');
        getline(ss, valor);

        if (clave == "nombreLiga") {
            nombreLiga = valor;
        }
        else if (clave == "puntosGanar") {
            puntosGanar = stoi(valor);
        }
        else if (clave == "puntosEmpate") {
            puntosEmpate = stoi(valor);
        }
        else if (clave == "puntosPerder") {
            puntosPerder = stoi(valor);
        }
    }

    archivo.close();

    cout << "\nLiga: " << nombreLiga << endl;
    cout << "Puntos por ganar: " << puntosGanar << endl;
    cout << "Puntos por empate: " << puntosEmpate << endl;
    cout << "Puntos por perder: " << puntosPerder << endl;

    break;
}

            case 2:
                cout << "Registrando partido...\n";
                break;

            case 3:
                cout << "Mostrando jornadas...\n";
                break;

            case 4:
                cout << "Mostrando partidos...\n";
                break;

            case 5:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while(opcion != 5);

    return 0;
}
