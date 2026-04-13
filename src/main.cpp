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


bool partidoExisteEnJornada(string eq1, string eq2) {

    ifstream archivo("data/fechas.txt");
    string linea;

    vector<string> ultimaJornada;

    
    while (getline(archivo, linea)) {

        if (linea.find("JORNADA=") != string::npos) {
            ultimaJornada.clear(); 
        }
        else if (linea == "FIN_JORNADA") {
            ultimaJornada.clear(); 
        }
        else if (!linea.empty()) {
            ultimaJornada.push_back(linea);
        }
    }

    archivo.close();

    // revisaa la última jornada 
    for (string linea : ultimaJornada) {

        stringstream ss(linea);
        string local, visitante;

        getline(ss, local, ',');
        getline(ss, visitante, ',');

        if ((local == eq1 && visitante == eq2) ||
            (local == eq2 && visitante == eq1)) {

            return true;
        }
    }

    return false;
}

void actualizarEquipo(Equipo* eq, int gf, int gc, int puntosGanar, int puntosEmpate, int puntosPerder) {

    eq->PJ++;
    eq->GF += gf;
    eq->GC += gc;

    if (gf > gc) {
        eq->PG++;
        eq->puntos += puntosGanar;
    }
    else if (gf == gc) {
        eq->PE++;
        eq->puntos += puntosEmpate;
    }
    else {
        eq->PP++;
        eq->puntos += puntosPerder;
    }
}


void leerConfig(vector<Equipo>& equipos, int& puntosGanar, int& puntosEmpate, int& puntosPerder) {

    equipos.clear();
    ifstream config("data/config.txt");

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
}


void ordenarEquipos(vector<Equipo>& equipos) {
    sort(equipos.begin(), equipos.end(), [](Equipo a, Equipo b) {

    // 1. Puntos
    if (a.puntos != b.puntos)
        return a.puntos > b.puntos;

    // 2. Diferencia de goles
    int dgA = a.GF - a.GC;
    int dgB = b.GF - b.GC;

    if (dgA != dgB)
        return dgA > dgB;

    // 3. Goles a favor
    return a.GF > b.GF;
});
}
int numeroJornada = 1;

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

            
            leerConfig(equipos, puntosGanar, puntosEmpate, puntosPerder);

            ifstream archivo("data/partidos.txt");
            string linea;

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
                        actualizarEquipo(&equipos[i], golesLocal, golesVisitante,
                                         puntosGanar, puntosEmpate, puntosPerder);
                    }

                    if (equipos[i].nombre == visitante) {
                        actualizarEquipo(&equipos[i], golesVisitante, golesLocal,
                                         puntosGanar, puntosEmpate, puntosPerder);
                    }
                }
            }

            archivo.close();

        
            ordenarEquipos(equipos);

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

            cout << "Seleccione equipo local: ";
cin >> local;

cout << "Seleccione equipo visitante: ";
cin >> visitante;

if (local < 1 || local > equipos.size() ||
    visitante < 1 || visitante > equipos.size()) {

    cout << "Equipo invalido\n";

    cin.clear();  
cin.ignore(1000, '\n');  
    break;
}
string equipoLocal = equipos[local - 1].nombre;
string equipoVisitante = equipos[visitante - 1].nombre;

if (partidoExisteEnJornada(equipoLocal, equipoVisitante)) {
    cout << "Este partido ya existe en la jornada actual\n";
    break;
}



            if (local == visitante) {
                cout << "No pueden ser el mismo equipo\n";
                break;
            }

            cout << "Goles del equipo local: ";
            cin >> golesLocal;
            cout << "Goles del equipo visitante: ";
            cin >> golesVisitante;

            ofstream archivoSalida("data/partidos.txt", ios::app);

            archivoSalida << equipos[local - 1].nombre << ","
                          << equipos[visitante - 1].nombre << ","
                          << golesLocal << ","
                          << golesVisitante << endl;

            archivoSalida.close();

            
            ofstream archivoFechas("data/fechas.txt", ios::app);

static bool nuevaJornada = true;

if (nuevaJornada) {
    archivoFechas << "JORNADA=" << numeroJornada << "\n";
    nuevaJornada = false;
}
            archivoFechas << equipos[local - 1].nombre << ","
                          << equipos[visitante - 1].nombre << ","
                          << golesLocal << ","
                          << golesVisitante << endl;
           

            archivoFechas.close();

            cout << "Partido guardado correctamente\n";
char opcionJornada;
cout << "Desea iniciar nueva jornada? (s/n): ";
cin >> opcionJornada;

if (opcionJornada == 's') {
    archivoFechas << "FIN_JORNADA\n";
    numeroJornada++;
    nuevaJornada = true;
}
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

        if (linea.find("JORNADA=") != string::npos) {
            cout << "\n" << linea << endl;
        }
        else if (linea.find("FECHA=") != string::npos) {
            cout << linea << endl;
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
