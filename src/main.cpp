#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Equipo {
    string nombre;
    int PJ = 0;
    int PG = 0;
    int PE = 0;
    int PP = 0;
    int GF = 0;
    int GC = 0;
    int puntos = 0;
};

struct Partido {
    string local;
    string visitante;
    int golesLocal;
    int golesVisitante;
};

int main() {

    int opcion;
    string nombreLiga;
    int puntosGanar, puntosEmpate, puntosPerder;

   vector<Equipo> equipos;

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
        else if (clave == "equipo") {
    Equipo nuevo;
    nuevo.nombre = valor;
    equipos.push_back(nuevo);
}
    }

    archivo.close();

    cout << "\nLiga: " << nombreLiga << endl;
    cout << "Puntos por ganar: " << puntosGanar << endl;
    cout << "Puntos por empate: " << puntosEmpate << endl;
    cout << "Puntos por perder: " << puntosPerder << endl;

    cout << "\nEquipos:\n";
    for (int i = 0; i < equipos.size(); i++) {
        cout << "- " << equipos[i].nombre << endl;
    }

    break;
}

            case 2: {
    ifstream archivo("data/config.txt");

    if (!archivo) {
        cout << "Error al abrir config.txt\n";
        break;
    }

    equipos.clear(); // evitar duplicados

    string linea;

    while (getline(archivo, linea)) {

        if (linea.empty()) continue;

        stringstream ss(linea);
        string clave, valor;

        getline(ss, clave, '=');
        getline(ss, valor);

        if (clave == "equipo") {
            Equipo nuevo;
            nuevo.nombre = valor;
            equipos.push_back(nuevo);
        }
    }

    archivo.close();

    cout << "\nEquipos disponibles:\n";
    for (int i = 0; i < equipos.size(); i++) {
        cout << i + 1 << ". " << equipos[i].nombre << endl;
    }

    int local, visitante;
    int golesLocal, golesVisitante;

    cout << "Seleccione equipo local (numero): ";
    cin >> local;

    cout << "Seleccione equipo visitante (numero): ";
    cin >> visitante;

    if (local == visitante) {
        cout << "No pueden ser el mismo equipo\n";
        break;
    }

    cout << "Goles del equipo local: ";
    cin >> golesLocal;

    cout << "Goles del equipo visitante: ";
    cin >> golesVisitante;

    ofstream archivoSalida("data/partidos.txt", ios::app);

    if (!archivoSalida) {
        cout << "Error al guardar partido\n";
        break;
    }

    archivoSalida << equipos[local - 1].nombre << ","
                  << equipos[visitante - 1].nombre << ","
                  << golesLocal << ","
                  << golesVisitante << endl;

    archivoSalida.close();

    cout << "Partido guardado correctamente\n";

    break;
}

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
