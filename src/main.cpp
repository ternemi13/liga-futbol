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
                if (a.puntos != b.puntos)
                    return a.puntos > b.puntos;

                int dgA = a.GF - a.GC;
                int dgB = b.GF - b.GC;

                return dgA > dgB;
            });

            ofstream archivoTabla("data/tabla.txt");

            archivoTabla << "# Equipo PJ PG PE PP GF GC DG PTS\n";

            cout << "\n# Equipo PJ PG PE PP GF GC DG PTS\n";

            for (int i = 0; i < equipos.size(); i++) {

                int DG = equipos[i].GF - equipos[i].GC;

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

            cin >> local;
            cin >> visitante;

            if (local == visitante) {
                cout << "No pueden ser el mismo equipo\n";
                break;
            }

            cin >> golesLocal;
            cin >> golesVisitante;

            ofstream archivoSalida("data/partidos.txt", ios::app);

            archivoSalida << equipos[local - 1].nombre << ","
                          << equipos[visitante - 1].nombre << ","
                          << golesLocal << ","
                          << golesVisitante << endl;

            archivoSalida.close();

            
            ofstream archivoFechas("data/fechas.txt", ios::app);

            archivoFechas << "JORNADA\n";
            archivoFechas << equipos[local - 1].nombre << ","
                          << equipos[visitante - 1].nombre << ","
                          << golesLocal << ","
                          << golesVisitante << endl;
            archivoFechas << "FIN_JORNADA\n";

            archivoFechas.close();

            cout << "Partido guardado correctamente\n";

            break;
        }

        case 3: {

            ifstream archivo("data/fechas.txt");

            if (!archivo) {
                cout << "Error al abrir fechas.txt\n";
                break;
            }

            string linea;

            cout << "\n=== HISTORIAL DE JORNADAS ===\n";

            while (getline(archivo, linea)) {

                if (linea == "JORNADA") {
                    cout << "\n--- Nueva Jornada ---\n";
                }
                else if (linea == "FIN_JORNADA") {
                    cout << "----------------------\n";
                }
                else if (!linea.empty()) {

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
            }

            archivo.close();

            break;
        }

        case 4: {

            ifstream archivo("data/partidos.txt");

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
