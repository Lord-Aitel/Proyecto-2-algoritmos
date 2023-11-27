#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Ciudad;  // Declaración anticipada para resolver la dependencia circular
class Guardian;  // Declaración anticipada para resolver la dependencia circular

class Ciudad {
public:
    string Nombre;
    vector<string> Conexion;
    vector<Guardian> guardianesLocales;
    string Maestro;

    Ciudad(string Nombre) {
        this->Nombre = Nombre;
    }

    Ciudad() {
        this->Nombre = "";
    }
};

unordered_map<string, Ciudad> mapaCiudades;

void cargar_ciudades(string archivo, unordered_map<string, Ciudad>& mapaCiudades, vector<Ciudad>& vectorCiudades) {
    // Abre el archivo en modo lectura usando ifstream
    ifstream in(archivo);

    // Comprueba si el archivo se pudo abrir correctamente
    if (!in.is_open()) {
        cout << "No se pudo abrir el archivo: " << archivo << endl;
        return;
    }

    // Crea un buffer para guardar los datos de cada ciudad
    string buffer;

    // Lee las ciudades una por una del archivo
    while (getline(in, buffer)) {
        // Crear un stringstream para facilitar la extracción de datos de la cadena
        stringstream ss(buffer);

        // Variables temporales para almacenar los datos de la ciudad
        string nombre, conexion;

        // Leer los datos desde el stringstream
        getline(ss, nombre, ',');
        getline(ss, conexion, ',');

        // Crea un objeto Ciudad con los detalles de la ciudad
        Ciudad ciudad(nombre);
        ciudad.Conexion.push_back(conexion);

        // Agrega la ciudad al unordered_map
        mapaCiudades[nombre] = ciudad;

        // Agrega la ciudad al vector de ciudades
        vectorCiudades.push_back(ciudad);

        // Muestra la información de la ciudad
        cout << "Nombre: " << ciudad.Nombre << endl;
        cout << "Conexiones: " << endl;
        for (const string& conexiones : ciudad.Conexion) {
            cout << "- " << conexiones << endl;
        }
    }
    // Cierra el archivo automáticamente cuando se sale del ámbito
}

class Guardian {
public:
    string Nombre;
    int Poder;
    string Maestria;
    string Ciudad;
    int powerLevel;  // Nuevo miembro powerLevel

    Guardian(string Nombre, int Poder, string Maestria, string Ciudad) {
        this->Nombre = Nombre;
        this->Poder = Poder;
        this->Maestria = Maestria;
        this->Ciudad = Ciudad;
        this->powerLevel = Poder;  // Inicializar powerLevel con el mismo valor que Poder
    }

    Guardian() {
        this->Nombre = "";
        this->Poder = 0;
        this->Maestria = "";
        this->Ciudad = "";
        this->powerLevel = 0;
    }
};

vector<Guardian> guardianes;

int buscar_guardian(string nombre) {
    for (size_t i = 0; i < guardianes.size(); ++i) {
        if (guardianes[i].Nombre == nombre) {
            return i;  // Devuelve el índice del guardián encontrado
        }
    }

    return -1;  // Retorna -1 si el guardián no se encuentra
}

Guardian crear_guardian(string buffer) {
    // Crear un stringstream para facilitar la extracción de datos de la cadena
    stringstream ss(buffer);

    // Variables temporales para almacenar los datos del Guardian
    string nombre, maestria, ciudad;
    int poder;

    // Leer los datos desde el stringstream
    getline(ss, nombre, ',');
    ss >> poder;
    ss.ignore(); // Ignorar la coma después del poder
    getline(ss, maestria, ',');
    getline(ss, ciudad, '\n');  // Cambiado para leer hasta el final de la línea

    // Crear y devolver un nuevo objeto Guardian con los datos obtenidos
    Guardian guardian(nombre, poder, maestria, ciudad);
    return guardian;
}

bool compararPowerLevel(const Guardian& a, const Guardian& b) {
    return a.powerLevel > b.powerLevel;
}

int guardianIndex(const vector<Guardian>& guardianes, const string& nombre) {
    for (size_t i = 0; i < guardianes.size(); ++i) {
        if (guardianes[i].Nombre == nombre) {
            return i;  // Devuelve el índice del guardián encontrado
        }
    }

    return -1;  // Retorna -1 si el guardián no se encuentra
}

void cargar_guardianes(string archivo, vector<Guardian>& guardianes) {
    // Abre el archivo en modo lectura usando ifstream
    ifstream in(archivo);

    // Comprueba si el archivo se pudo abrir correctamente
    if (!in.is_open()) {
        cout << "No se pudo abrir el archivo: " << archivo << endl;
        return;
    }

    // Crea un buffer para guardar los datos de cada guardián
    string buffer;

    // Lee los guardianes uno por uno del archivo
    while (getline(in, buffer)) {
        // Crea un objeto Guardián con los detalles del guardián
        Guardian guardian = crear_guardian(buffer);

        // Agrega el guardián a la lista de guardianes
        guardianes.push_back(guardian);

        if(mapaCiudades.find(guardian.Ciudad) != mapaCiudades.end())
        {
            Ciudad& ciudad = mapaCiudades[guardian.Ciudad];
            if (ciudad.Maestro.empty() || guardian.Poder > guardianes[guardianIndex(guardianes, ciudad.Maestro)].Poder) 
            {
                ciudad.Maestro = guardian.Nombre;
            }

        ciudad.guardianesLocales.push_back(guardian);
        // Ordenar a los aprendices según su Poder
        sort(ciudad.guardianesLocales.begin(), ciudad.guardianesLocales.end(), compararPowerLevel);

        }

        // Muestra la información completa del guardián
        cout << "Nombre: " << guardian.Nombre << endl;
        cout << "Poder: " << guardian.Poder << endl;
        cout << "Maestria: " << guardian.Maestria << endl;
        cout << "Ciudad: " << guardian.Ciudad << endl;
        cout << "----------------------" << endl;
    }

    // Cierra el archivo automáticamente cuando se sale del ámbito
}

void enfrentar(int guardian1_id, int guardian2_id) {
    // Simular la batalla y actualizar la puntuación de los guardiánes
}

void actualizar_ranking() {
    // Actualizar el ranking de los guardiánes
}

int buscar_maestro(int id) {
    // Buscar al maestro de un guardián
    return 0;
}

void mostrar_información(Guardian guardian) {
    // Imprimir la información del guardián
}

void guardar_progreso(string archivo) {
    // Guardar la información en un archivo
}

void ver_ranking() {
    // Imprimir el ranking de los guardiánes
}

double calcular_probabilidad(Guardian guardian1, Guardian guardian2) {
    return 0;
    // Calcular la probabilidad de que el primer guardián gane la batalla
}

int main() {
   string archivo = "Guardians.txt";
   string archivo_ciudades = "Cities.txt";
   //cargar_informacion(archivo);

   int opcion;

   vector<Ciudad> ciudadesVector; 
   unordered_map<string, Ciudad> ciudadesMap;
   do {
        cout << "   ----The guardians battles----" << endl;
        cout << "/[1]  Ver la lista de candidatos \\" << endl;
        cout << "/[2]       Ver al guardian       \\" << endl;
        cout << "/[3]      Conocer el reino       \\" << endl;
        cout << "/[4]    Presenciar una Batalla   \\" << endl;
        cout << "/[5]          Para Salir         \\" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

       switch (opcion) {
           case 1: {
               cargar_guardianes(archivo, guardianes);
               break;
           }
           case 2: {
                string nombre;
                cout << "Ingrese el nombre del guardián: ";
                cin >> nombre;

                int guardian_id = buscar_guardian(nombre);
                if (guardian_id != -1) {
                    // Mostrar la información del guardián
                    cout << "Nombre: " << guardianes[guardian_id].Nombre << endl;
                    cout << "Poder: " << guardianes[guardian_id].Poder << endl;
                    cout << "Maestría: " << guardianes[guardian_id].Maestria << endl;
                    cout << "Ciudad: " << guardianes[guardian_id].Ciudad << endl;
                } else {
                    cout << "Guardián no encontrado." << endl;
                }

                break;
            }
           case 3: {
               cargar_ciudades(archivo_ciudades, mapaCiudades, ciudadesVector);
               break;
           }
           case 4: {
               string nombre1, nombre2;
               cout << "Ingrese el nombre del primer guardian: ";
               cin >> nombre1;
               cout << "Ingrese el nombre del segundo guardian: ";
               cin >> nombre2;
               int guardian1_id = buscar_guardian(nombre1);
               int guardian2_id = buscar_guardian(nombre2);

               if (guardian1_id != -1 && guardian2_id != -1 && guardian1_id != guardian2_id) {
                   enfrentar(guardian1_id, guardian2_id);
               } else {
                   cout << "Guardian no encontrado." << endl;
               }
               break;
           }
           case 5: {
               // Salir del programa
               break;
           }
           default: {
               cout << "Opción no válida." << endl;
               break;
           }
       }
   } while (opcion != 5);

   return 0;
}