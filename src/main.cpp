#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {

    int opcion;

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

                cout << "\nContenido de config.txt:\n";

                while (getline(archivo, linea)) {
                    cout << linea << endl;
                }

                archivo.close();
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
