#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {

    int opcion;
    string Arch1;
    string Arch2;

    ifstream archivo1("Cities.txt");
    ifstream archivo2("Guardians.txt");

    while(getline(archivo1,Arch1)){
    cout <<Arch1<<endl;
    }
    
    cout<<"\n"<<endl;

    while(getline(archivo2,Arch2)){
    cout <<Arch2<<endl;
    }

do {
        cout << "     ----Menu de ejercicios---" << endl;
        cout << "/[1]   para Calcular factoriales \\" << endl;
        cout << "/[2]    para Calcular Fibonacci  \\" << endl;
        cout << "/[3] para Verificar un palindromo\\" << endl;
        cout << "/[4] para Operaciones matematicas\\" << endl;
        cout << "/[5]            para Salir       \\" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 5:
                cout << "Fin del Juego" << endl;
                break;
            default:
                cout << "Opcion no valida, ingresa una opcion valida." << endl;
                break;
        }
    } while (opcion != 5);
    return 0;
}