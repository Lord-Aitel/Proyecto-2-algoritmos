#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
#include <cmath>

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
    }

    Guardian() {
        this->Nombre = "";
        this->Poder = 0;
        this->Maestria = "";
        this->Ciudad = "";
    }
};

unordered_map<string, Ciudad> mapaCiudades;

void cargar_ciudades(string archivo, unordered_map<string, Ciudad>& mapaCiudades, vector<Guardian>& guardianes) {
    ifstream in(archivo);

    if (!in.is_open()) {
        cout << "No se pudo abrir el archivo: " << archivo << endl;
        return;
    }

    string buffer;

    while (getline(in, buffer)) {
        stringstream ss(buffer);
        string nombre, conexion;

        getline(ss, nombre, ',');
        getline(ss, conexion, ',');

        // Verificar si la ciudad ya existe en el mapa
        if (mapaCiudades.find(nombre) == mapaCiudades.end()) {
            Ciudad ciudad(nombre);
            ciudad.Conexion.push_back(conexion);

            // Agregar guardianes locales a la ciudad
            for (const Guardian& guardian : guardianes) {
                if (guardian.Ciudad == nombre) {
                    ciudad.guardianesLocales.push_back(guardian);
                }
            }

            mapaCiudades[nombre] = ciudad;
        } else {
            // La ciudad ya existe, solo agregar la conexión
            mapaCiudades[nombre].Conexion.push_back(conexion);

        }
    }
    in.close();
}



void imprimir_ciudades(const unordered_map<string, Ciudad>& mapaCiudades) {
    for (const auto& par : mapaCiudades) {
        const Ciudad& ciudad = par.second;
        cout << "Nombre: " << ciudad.Nombre << endl;
        cout << "Conexiones:" << endl;
        for (const string& conexion : ciudad.Conexion) {
            cout << "- " << conexion << endl;
        }
        cout << "------------" << endl;
    }
}





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
    int poder;  // Cambiado de tipo de string a int

    // Leer los datos desde el stringstream
    getline(ss, nombre, ',');
    ss >> poder;
    ss.ignore();  // Ignorar la coma después del poder
    getline(ss, maestria, ',');
    getline(ss, ciudad, '\n');  // Cambiado para leer hasta el final de la línea

    // Crear y devolver un nuevo objeto Guardian con los datos obtenidos
    Guardian guardian(nombre, poder, maestria, ciudad);
    return guardian;
}

bool compararPoder(const Guardian& a, const Guardian& b) {
    return a.Poder > b.Poder;
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
        sort(ciudad.guardianesLocales.begin(), ciudad.guardianesLocales.end(), compararPoder);

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

void imprimir_candidatos(const vector<Guardian>& guardianes) {
    cout << "Lista de candidatos:" << endl;
    bool hay_candidatos = false;

    for (const Guardian& guardian : guardianes) {
        if (guardian.Poder >= 90 && guardian.Poder <= 99) {
            hay_candidatos = true;
            cout << "Nombre: " << guardian.Nombre << endl;
            cout << "Poder: " << guardian.Poder << endl;
            cout << "Maestría: " << guardian.Maestria << endl;
            cout << "Ciudad: " << guardian.Ciudad << endl;
            cout << "----------------------" << endl;
        }
    }

    if (!hay_candidatos) {
        cout << "No hay guardianes candidatos en este momento." << endl;
    }
}


int actualizar_ranking(Guardian& miGuardian) {
    int poderGuardian = miGuardian.Poder;
    int nuevaPosicion = -1; // Variable para almacenar la nueva posición del guardián

    // Ordenar la lista de guardianes según su poder
    sort(guardianes.begin(), guardianes.end(), compararPoder);

    // Buscar la nueva posición del guardián en el vector ordenado
    for (size_t i = 0; i < guardianes.size(); ++i) {
        if (guardianes[i].Nombre == miGuardian.Nombre && guardianes[i].Poder == poderGuardian) {
            // Almacenar la nueva posición del guardián
            nuevaPosicion = i;
            break;
        }
    }

    return nuevaPosicion; // Devolver la nueva posición del guardián
}




double calcular_probabilidad(const Guardian& guardian1, const Guardian& guardian2) {
    // Calcular la probabilidad basada en la diferencia de poder entre los guardianes
    // y otros factores específicos del juego.
    // Esta es solo una lógica de ejemplo, ajusta según tus necesidades.

    const double factorPoder = 0.1; // Ajusta este factor según sea necesario

    double diferenciaPoder = guardian1.Poder - guardian2.Poder;

    // Asegurarse de que la diferencia de poder no sea negativa
    diferenciaPoder = max(0.0, diferenciaPoder);

    // Calcular la probabilidad
    double probabilidad = 1 / (1 + exp(-factorPoder * diferenciaPoder));

    return probabilidad;
}

void mostrar_informacion(const Guardian& guardian) {
    // Imprimir la información del guardián
    cout << "Información del Guardián:" << endl;
    cout << "Nombre: " << guardian.Nombre << endl;
    cout << "Poder: " << guardian.Poder << endl;
    cout << "Maestría: " << guardian.Maestria << endl;
    cout << "Ciudad: " << guardian.Ciudad << endl;
    cout << "---------------------------------" << endl;
}

void mostrar_ciudades_conexion(const string& ciudad_actual, const unordered_map<string, Ciudad>& mapaCiudades) {
    if (mapaCiudades.find(ciudad_actual) == mapaCiudades.end()) {
        cout << "La ciudad actual no se encuentra en el mapa." << endl;
        return;
    }

    const Ciudad& ciudad_actual_obj = mapaCiudades.at(ciudad_actual);

    if (ciudad_actual_obj.Conexion.empty()) {
        cout << "No hay ciudades conectadas desde " << ciudad_actual << "." << endl;
        return;
    }

    cout << "Ciudades a las que puedes viajar desde " << ciudad_actual << ":" << endl;
    for (const string& conexion : ciudad_actual_obj.Conexion) {
        cout << "- " << conexion << endl;
    }
}


void enfrentar(int guardian1_id) {
    // Verificar que el ID del guardián sea válido
    if (guardian1_id < 0 || guardian1_id >= guardianes.size()) {
        cout << "ID de guardián no válido." << endl;
        return;
    }

    Guardian& guardian1 = guardianes[guardian1_id];
    Ciudad ciudad;
    ciudad.Nombre =  guardian1.Ciudad;
    if(mapaCiudades.find(ciudad.Nombre) == mapaCiudades.end())
    {
        ciudad = mapaCiudades[guardian1.Ciudad];
    }

    // Verificar que el guardián no sea el gran maestro o un guardián del reino
    if (guardian1.Nombre == "Freya" || guardian1.Nombre == ciudad.Maestro) {
        cout << "No puedes seleccionar al Gran Maestro o a los guardianes del reino." << endl;
        return;
    }

    do
    {
        mostrar_ciudades_conexion(ciudad.Nombre, mapaCiudades);

        cout << guardian1.Nombre << endl;

        string ciudad_destino;
        getline(cin, ciudad_destino);

        // Viajar a la ciudad de destino
        if (mapaCiudades.find(ciudad_destino) == mapaCiudades.end()) {
            cout << "Ciudad de destino no válida." << endl;
            return;
        }

        Ciudad& ciudad_destino_obj = mapaCiudades[ciudad_destino];

        // Obtener la lista de guardianes locales en la ciudad de destino
        vector<Guardian>& guardianes_locales = ciudad_destino_obj.guardianesLocales;

        for(const Guardian guardian : guardianes_locales)
        {
            mostrar_informacion(guardian);
        }

        cout << "Seleccione Rival." << endl;
        string guardianRival;
        Guardian guardian2;

        getline(cin, guardianRival);

        for(const Guardian guardian : guardianes_locales)
        {
            if(guardian.Nombre == guardianRival)
            {
                guardian2 = guardian;
                break;
            }
        }

        // Calcular la probabilidad de que el primer guardián gane la batalla
        double probabilidad = calcular_probabilidad(guardian1, guardian2);

        // Generar un número aleatorio entre 0 y 1
        double random = ((double)rand() / RAND_MAX);

        // Determinar el resultado de la batalla
        if (random < probabilidad) {
            cout << guardian1.Nombre << " ha ganado la batalla contra " << guardian2.Nombre << " en " << ciudad_destino << "!" << endl;
            // Actualizar el puntaje según el tipo de guardián derrotado
            if (guardian2.Nombre == ciudad_destino_obj.Maestro) {
                guardian1.Poder += 5;
            } else {
                guardian1.Poder += 3;
            }

            // Mostrar información actualizada del ganador
            mostrar_informacion(guardian1);

            // Bajar el puntaje al guardián derrotado
            guardian2.Poder -= 1;


            // Verificar si el guardián retador supera al maestro
            if (guardian1.Poder > guardianes[guardianIndex(guardianes, ciudad_destino_obj.Maestro)].Poder) {
                ciudad_destino_obj.Maestro = guardian1.Nombre;
            }
        } else {
            cout << guardian2.Nombre << " ha ganado la batalla contra " << guardian1.Nombre << " en " << ciudad_destino << "!" << endl;
            // Bajar el puntaje al guardián retador
            guardian1.Poder -= 1;

            // Bajar el puntaje al guardián derrotado
            guardian2.Poder += 1;

            // Mostrar información actualizada del perdedor
            mostrar_informacion(guardian1);

            // Mostrar información actualizada del ganador
            mostrar_informacion(guardian2);

            
        }
        guardian1_id = actualizar_ranking(guardian1);
        guardian1 = guardianes[guardian1_id];
        ciudad = ciudad_destino_obj;
    } while (guardian1.Poder < 90);
}

int buscar_maestro(const string& nombre) {
    // Buscar al maestro de un guardián
    for (size_t i = 0; i < guardianes.size(); ++i) {
        if (guardianes[i].Nombre == nombre) {
            // Se encontró al guardián, devolver el índice del maestro
            return guardianIndex(guardianes, mapaCiudades[guardianes[i].Ciudad].Maestro);
        }
    }

    // Si no se encuentra el guardián, devolver -1
    return -1;
}

void guardar_progreso(const string& archivo, const vector<Guardian>& guardianes, const unordered_map<string, Ciudad>& ciudades) {
    // Abre el archivo en modo escritura usando ofstream
    ofstream out(archivo);

    // Comprueba si el archivo se pudo abrir correctamente
    if (!out.is_open()) {
        cout << "No se pudo abrir el archivo: " << archivo << endl;
        return;
    }

    // Guarda la información de los guardianes en el archivo
    for (const Guardian& guardian : guardianes) {
        out << guardian.Nombre << "," << guardian.Poder << "," << guardian.Maestria << "," << guardian.Ciudad << endl;
    }

    // Guarda la información de las ciudades en el archivo
    for (const auto& par : ciudades) {
        const Ciudad& ciudad = par.second;
        out << ciudad.Nombre;
        for (const string& conexion : ciudad.Conexion) {
            out << "," << conexion;
        }
        out << endl;
    }

    // Cierra el archivo automáticamente al salir del ámbito
}   

void ver_ranking(const vector<Guardian>& guardianes) {
    // Crear una copia del vector de guardianes para no modificar el original
    vector<Guardian> guardianesOrdenados = guardianes;

    // Ordenar el vector de guardianes por nivel de poder
    sort(guardianesOrdenados.begin(), guardianesOrdenados.end(), compararPoder);

    // Imprimir el encabezado del ranking
    cout << "   ---- Ranking de Guardianes ----" << endl;
    cout << "-----------------------------------" << endl;
    cout << "|   Nombre   |  Poder  | Maestría |" << endl;
    cout << "-----------------------------------" << endl;

    // Imprimir la información de cada guardián en el ranking
    for (const Guardian& guardian : guardianesOrdenados) {
        cout << "| " << setw(11) << guardian.Nombre << " | " << setw(7) << guardian.Poder << " | " << setw(9) << guardian.Maestria << " |" << endl;
    }

    // Imprimir el final del ranking
    cout << "-----------------------------------" << endl;
}

int main() {
   string archivo = "Guardians.txt";
   string archivo_ciudades = "Cities.txt";
   vector<Ciudad> ciudadesVector; 

   //cargar_informacion(archivo);
   // Cargar al inicio para evitar errores
    cargar_guardianes(archivo, guardianes);
    cargar_ciudades(archivo_ciudades, mapaCiudades, guardianes);

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
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

       switch (opcion) {
           case 1: {
               imprimir_candidatos(guardianes);
               break;
           }
           case 2: {
                string nombre;
                cout << "Ingrese el nombre del guardián: ";
                getline(cin, nombre);

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
                imprimir_ciudades(mapaCiudades);
                break;
           }
           case 4: {
                string nombre1;
                cout << "Seleccione a un guardian: ";
                getline(cin, nombre1);
                int guardian1_id = buscar_guardian(nombre1);

                enfrentar(guardian1_id);

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