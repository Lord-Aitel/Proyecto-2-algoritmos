#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm> 

using namespace std;

// Estructura del Guardian
struct Guardian {
    int id;
    string nombre;
    int puntos;
    // Agregar otros atributos relevantes

    // Constructor predeterminado
    Guardian() : id(0), puntos(0) {}

    // Constructor con parámetros
    Guardian(int _id, string _nombre, int _puntos) : id(_id), nombre(_nombre), puntos(_puntos) {}

    // Getters y setters...
};

class RankingGuardianes {
private:
    vector<Guardian> listaCandidatos;

public:
    // Funciones del ranking
    void agregarGuardian(Guardian guardian);
    void mostrarRanking();
};

// Función para agregar un guardian al ranking
void RankingGuardianes::agregarGuardian(Guardian guardian) {
    listaCandidatos.push_back(guardian);

    // Ordenar el vector en función de los puntos de los guardianes
    sort(listaCandidatos.begin(), listaCandidatos.end(), [](const Guardian& a, const Guardian& b) {
        return a.puntos > b.puntos;
    });
}

// Función para mostrar el ranking
void RankingGuardianes::mostrarRanking() {
    cout << "Ranking de Guardianes:" << endl;
    for (size_t i = 0; i < listaCandidatos.size(); ++i) {
        cout << "Posición " << i + 1 << ": ID: " << listaCandidatos[i].id
             << ", Nombre: " << listaCandidatos[i].nombre
             << ", Puntos: " << listaCandidatos[i].puntos << endl;
    }
}

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
        cout << "   ----The guardians battles----" << endl;
        cout << "/[1]  Ver la lista de candidatos \\" << endl;
        cout << "/[2]       Ver al guardián       \\" << endl;
        cout << "/[3]      Conocer el reino       \\" << endl;
        cout << "/[4]    Presenciar una Batalla   \\" << endl;
        cout << "/[5]          Para Salir         \\" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: {

                RankingGuardianes ranking;
                
                Guardian guardian1(1, "Guardian Uno", 50);
                Guardian guardian2(2, "Guardian Dos", 60);
                Guardian guardian3(3, "Guardian Tres", 55);

                ranking.agregarGuardian(guardian1);
                ranking.agregarGuardian(guardian2);
                ranking.agregarGuardian(guardian3);

                ranking.mostrarRanking();
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