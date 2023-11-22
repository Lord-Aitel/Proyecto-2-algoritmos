#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class UndirectedGraph {
private:
    int V; // Número de vértices
    vector<vector<int>> graph; // Matriz de adyacencia

public:
    // Constructor
    UndirectedGraph(int vertices) : V(vertices), graph(vertices, vector<int>(vertices, 0)) {}

    // Función para agregar una arista entre los vértices u y v
    void addEdge(int u, int v) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            graph[u][v] = 1;
            graph[v][u] = 1;
        } else {
            cerr << "Vértices no válidos: " << u << ", " << v << endl;
        }
    }

    // Función para imprimir la matriz de adyacencia
    void printGraph() const {
        cout << "Matriz de Adyacencia:\n";
        for (const auto& row : graph) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << '\n';
        }
    }

    // Función para obtener la matriz de adyacencia
    const vector<vector<int>>& getGraphMatrix() const {
        return graph;
    }

    // Función para verificar si dos vértices son adyacentes
    bool areAdjacent(int u, int v) const {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            return graph[u][v] == 1;
        } else {
            cerr << "Vértices no válidos: " << u << ", " << v << endl;
            return false;
        }
    }

    // Función para encontrar un camino entre dos vértices
    void findPath(int start, int end) const {
        vector<bool> visited(V, false);
        vector<int> path;
        bool found = false;

        path.push_back(start);
        visited[start] = true;

        while (!path.empty()) {
            int current = path.back();
            path.pop_back();

            cout << current << " ";

            if (current == end) {
                found = true;
                break;
            }

            for (int neighbor = 0; neighbor < V; ++neighbor) {
                if (graph[current][neighbor] == 1 && !visited[neighbor]) {
                    path.push_back(neighbor);
                    visited[neighbor] = true;
                }
            }
        }

        if (!found) {
            cout << "No se encontró un camino entre " << start << " y " << end << endl;
        }
    }
};

int main() {

    ifstream archivo("Cities.txt");
    ifstream archivo("Guardians.txt");

    int V = 8; // Número de vértices
    UndirectedGraph myGraph(V);

    // Agregar aristas en el orden señalado
    myGraph.addEdge(7, 3);
    myGraph.addEdge(0, 2);
    myGraph.addEdge(0, 4);
    myGraph.addEdge(0, 3);
    myGraph.addEdge(7, 6);
    myGraph.addEdge(3, 1);
    myGraph.addEdge(3, 0);
    myGraph.addEdge(3, 6);
    myGraph.addEdge(3, 7);
    myGraph.addEdge(6, 2);
    myGraph.addEdge(6, 1);
    myGraph.addEdge(6, 3);
    myGraph.addEdge(6, 7);
    myGraph.addEdge(4, 0);
    myGraph.addEdge(4, 1);
    myGraph.addEdge(4, 5);
    myGraph.addEdge(5, 4);
    myGraph.addEdge(5, 1);
    myGraph.addEdge(5, 2);
    myGraph.addEdge(2, 1);
    myGraph.addEdge(5, 6);

    // Imprimir la matriz de adyacencia
    myGraph.printGraph();

    // Encontrar un camino entre dos vértices
    int startVertex = 2;
    int endVertex = 7;

    cout << "Camino entre " << startVertex << " y " << endVertex << ": ";
    myGraph.findPath(startVertex, endVertex);

    return 0;
}