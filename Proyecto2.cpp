#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Ciudad {
public:

    string Nombre;
    string Conexion;  

    Ciudad(string Nombre, string Conexion) {
        this->Nombre = Nombre;
        this->Conexion = Conexion;
    }

    Ciudad() {
        this->Nombre = "";
        this->Conexion = "";
    }
};

vector<Ciudad> ciudades;

void cargar_ciudades(string archivo, vector<Ciudad>& ciudades) {
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
        Ciudad ciudad(nombre, conexion);

        // Agrega la ciudad a la lista de ciudades
        ciudades.push_back(ciudad);

        // Muestra la información de la ciudad
        cout << "Nombre: " << ciudad.Nombre << ", Conexión: " << ciudad.Conexion << endl;
    }
    // Cierra el archivo automáticamente cuando se sale del ámbito
}

class Guardián {
public:
    string Nombre;
    int Poder;
    string Maestria;
    string Ciudad;

    Guardián(string Nombre, int Poder, string Maestria, string Ciudad) {
        this->Nombre = Nombre;
        this->Poder = Poder;
        this->Maestria = Maestria;
        this->Ciudad = Ciudad;
    }

    Guardián() {
        this->Nombre = "";
        this->Poder = 0;
        this->Maestria = "";
        this->Ciudad = "";
    }
};

vector<Guardián> guardianes;

int buscar_guardian(string nombre) {
    for (size_t i = 0; i < guardianes.size(); ++i) {
        if (guardianes[i].Nombre == nombre) {
            return static_cast<int>(i);  // Devuelve el índice del guardián encontrado
        }
    }

    return -1;  // Retorna -1 si el guardián no se encuentra
}

Guardián crear_guardian(string buffer) {
    // Crear un stringstream para facilitar la extracción de datos de la cadena
    stringstream ss(buffer);

    // Variables temporales para almacenar los datos del guardián
    string nombre, maestria, ciudad;
    int poder;

    // Leer los datos desde el stringstream
    getline(ss, nombre, ',');
    ss >> poder;
    ss.ignore(); // Ignorar la coma después del poder
    getline(ss, maestria, ',');
    getline(ss, ciudad, '\n');  // Cambiado para leer hasta el final de la línea

    // Crear y devolver un nuevo objeto Guardián con los datos obtenidos
    Guardián guardián(nombre, poder, maestria, ciudad);
    return guardián;
}

void cargar_guardianes(string archivo, vector<Guardián>& guardianes) {
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
        Guardián guardián = crear_guardian(buffer);

        // Agrega el guardián a la lista de guardianes
        guardianes.push_back(guardián);

        // Muestra la información completa del guardián
        cout << "Nombre: " << guardián.Nombre << endl;
        cout << "Poder: " << guardián.Poder << endl;
        cout << "Maestria: " << guardián.Maestria << endl;
        cout << "Ciudad: " << guardián.Ciudad << endl;
        cout << "----------------------" << endl;
    }

    // Cierra el archivo automáticamente cuando se sale del ámbito
}

void enfrentar(int guardián1_id, int guardián2_id) {
    // Simular la batalla y actualizar la puntuación de los guardiánes
}

void actualizar_ranking() {
    // Actualizar el ranking de los guardiánes
}

int buscar_maestro(int id) {
    // Buscar al maestro de un guardián
}

void mostrar_información(Guardián guardián) {
    // Imprimir la información del guardián
}

void guardar_progreso(string archivo) {
    // Guardar la información en un archivo
}

void ver_ranking() {
    // Imprimir el ranking de los guardiánes
}

double calcular_probabilidad(Guardián guardián1, Guardián guardián2) {
    // Calcular la probabilidad de que el primer guardián gane la batalla
}

int main() {
   string archivo = "Guardians.txt";
   string archivo_ciudades = "Cities.txt";
   //cargar_informacion(archivo);

   int opcion;

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
               cout << "Ingrese el nombre del guardian: ";
               cin >> nombre;

               int guardián_id = buscar_guardian(nombre);

               if (guardián_id != -1) {
                   // Imprimir la información del guardián
               } else {
                   cout << "Guardian no encontrado." << endl;
               }

               break;
           }
           case 3: {
               cargar_ciudades(archivo_ciudades, ciudades);
               break;
           }
           case 4: {
               string nombre1, nombre2;
               cout << "Ingrese el nombre del primer guardian: ";
               cin >> nombre1;
               cout << "Ingrese el nombre del segundo guardian: ";
               cin >> nombre2;
               int guardián1_id = buscar_guardian(nombre1);
               int guardián2_id = buscar_guardian(nombre2);

               if (guardián1_id != -1 && guardián2_id != -1) {
                   enfrentar(guardián1_id, guardián2_id);
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