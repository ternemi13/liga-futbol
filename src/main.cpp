#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
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

            equipos.clear();

            ifstream config("data/config.txt");

            if (!config) {
                cout << "Error al abrir config.txt\n";
                break;
            }

            string linea;

            while (getline(config, linea)) {

                if (linea.empty()) continue;

                stringstream ss(linea);
                string clave, valor;

                getline(ss, clave, '=');
                getline(ss, valor);

                if (clave == "puntosGanar") puntosGanar = stoi(valor);
                else if (clave == "puntosEmpate") puntosEmpate = stoi(valor);
                else if (clave == "puntosPerder") puntosPerder = stoi(valor);

                else if (clave == "equipo") {
                    Equipo nuevo;
                    nuevo.nombre = valor;
                    nuevo.PJ = 0;
                    nuevo.PG = 0;
                    nuevo.PE = 0;
                    nuevo.PP = 0;
                    nuevo.GF = 0;
                    nuevo.GC = 0;
                    nuevo.puntos = 0;

                    equipos.push_back(nuevo);
                }
            }

            config.close();

            ifstream archivo("data/partidos.txt");

            if (!archivo) {
                cout << "Error al abrir partidos.txt\n";
                break;
            }

            while (getline(archivo, linea)) {

                if (linea.empty()) continue;

                stringstream ss(linea);
                string local, visitante;
                int golesLocal, golesVisitante;

                getline(ss, local, ',');
                getline(ss, visitante, ',');
                ss >> golesLocal;
                ss.ignore();
                ss >> golesVisitante;

                for (int i = 0; i < equipos.size(); i++) {

                    if (equipos[i].nombre == local) {
                        equipos[i].PJ++;
                        equipos[i].GF += golesLocal;
                        equipos[i].GC += golesVisitante;

                        if (golesLocal > golesVisitante) {
                            equipos[i].PG++;
                            equipos[i].puntos += puntosGanar;
                        } else if (golesLocal == golesVisitante) {
                            equipos[i].PE++;
                            equipos[i].puntos += puntosEmpate;
                        } else {
                            equipos[i].PP++;
                            equipos[i].puntos += puntosPerder;
                        }
                    }

                    if (equipos[i].nombre == visitante) {
                        equipos[i].PJ++;
                        equipos[i].GF += golesVisitante;
                        equipos[i].GC += golesLocal;

                        if (golesVisitante > golesLocal) {
                            equipos[i].PG++;
                            equipos[i].puntos += puntosGanar;
                        } else if (golesVisitante == golesLocal) {
                            equipos[i].PE++;
                            equipos[i].puntos += puntosEmpate;
                        } else {
                            equipos[i].PP++;
                            equipos[i].puntos += puntosPerder;
                        }
                    }
                }
            }

            archivo.close();

          
            sort(equipos.begin(), equipos.end(), [](Equipo a, Equipo b) {
                return a.puntos > b.puntos;
            });

            ofstream archivoTabla("data/tabla.txt");

if (!archivoTabla) {
    cout << "Error al crear tabla.txt\n";
}
archivoTabla << "# Equipo PJ PG PE PP GF GC DG PTS\n";

            cout << "\n=== TABLA DE POSICIONES ===\n";
cout << "\n# Equipo PJ PG PE PP GF GC DG PTS\n";

cout << "\n# Equipo PJ PG PE PP GF GC DG PTS\n";

for (int i = 0; i < equipos.size(); i++) {

    int DG = equipos[i].GF - equipos[i].GC;

    // Muestro en consola :D
    cout << i + 1 << " "
         << equipos[i].nombre << " "
         << equipos[i].PJ << " "
         << equipos[i].PG << " "
         << equipos[i].PE << " "
         << equipos[i].PP << " "
         << equipos[i].GF << " "
         << equipos[i].GC << " "
         << DG << " "
         << equipos[i].puntos
         << endl;

    //guardo en el archivo xdd
    archivoTabla << i + 1 << " "
                 << equipos[i].nombre << " "
                 << equipos[i].PJ << " "
                 << equipos[i].PG << " "
                 << equipos[i].PE << " "
                 << equipos[i].PP << " "
                 << equipos[i].GF << " "
                 << equipos[i].GC << " "
                 << DG << " "
                 << equipos[i].puntos
                 << endl;
}
archivoTabla.close();
            break;
        }

        case 2: {

            ifstream archivo("data/config.txt");

            if (!archivo) {
                cout << "Error al abrir config.txt\n";
                break;
            }

            equipos.clear();

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

     case 4: {

    ifstream archivo("data/partidos.txt");

    if (!archivo) {
        cout << "Error al abrir partidos.txt\n";
        break;
    }

    string linea;

    cout << "\n=== PARTIDOS JUGADOS ===\n";

    while (getline(archivo, linea)) {

        if (linea.empty()) continue;

        stringstream ss(linea);
        string local, visitante;
        int golesLocal, golesVisitante;

        getline(ss, local, ',');
        getline(ss, visitante, ',');
        ss >> golesLocal;
        ss.ignore();
        ss >> golesVisitante;

        cout << local << " " << golesLocal
             << " - " << golesVisitante << " "
             << visitante << endl;
    }

    archivo.close();

    break;
}
        case 5:
            cout << "Saliendo del programa...\n";
            break;

        default:
            cout << "Opcion invalida\n";
        }

    } while(opcion != 5);

    return 0;
}
