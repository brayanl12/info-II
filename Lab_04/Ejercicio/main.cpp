#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Clase Router
class Router {
public:
    string nombre;
    map<string, int> vecinos;

    Router(string nombre) : nombre(nombre) {}
};

// Clase Network
class Network {
private:
    map<string, Router*> routers;
    vector<string> historial;

public:
    ~Network() {
        for (auto& par : routers)
            delete par.second;
    }

    void agregarRouter(const string& nombre) {
        if (!routers.count(nombre)) {
            routers[nombre] = new Router(nombre);
            historial.push_back("Agregado router: " + nombre);
        }
    }

    void eliminarRouter(const string& nombre) {
        if (!routers.count(nombre)) {
            cout << "Router no existe.\n";
            return;
        }

        for (auto& [_, router] : routers)
            router->vecinos.erase(nombre);

        delete routers[nombre];
        routers.erase(nombre);
        historial.push_back("Eliminado router: " + nombre);
    }

    void conectarRouters(const string& a, const string& b, int costo) {
        if (routers.count(a) && routers.count(b)) {
            routers[a]->vecinos[b] = costo;
            routers[b]->vecinos[a] = costo;
            historial.push_back("Conectado " + a + " <--> " + b + " con costo " + to_string(costo));
        }
    }

    void cargarTopologia(const string& archivo) {
        ifstream file(archivo);
        if (!file.is_open()) {
            cout << "No se pudo abrir el archivo.\n";
            return;
        }

        string linea;
        while (getline(file, linea)) {
            istringstream ss(linea);
            string a, b;
            int costo;
            ss >> a >> b >> costo;
            agregarRouter(a);
            agregarRouter(b);
            conectarRouters(a, b, costo);
        }

        historial.push_back("Topología cargada desde: " + archivo);
    }

    void generarRedAleatoria(int cantidad) {
        limpiarRed();
        srand(time(0));

        for (int i = 0; i < cantidad; ++i)
            agregarRouter("R" + to_string(i));

        for (int i = 0; i < cantidad; ++i) {
            for (int j = i + 1; j < cantidad; ++j) {
                if (rand() % 2) {
                    int costo = rand() % 10 + 1;
                    conectarRouters("R" + to_string(i), "R" + to_string(j), costo);
                }
            }
        }

        historial.push_back("Red aleatoria generada con " + to_string(cantidad) + " routers.");
    }

    void mostrarEstadoRed() {
        for (auto& [nombre, router] : routers) {
            cout << nombre << " --> ";
            for (auto& [vecino, costo] : router->vecinos)
                cout << "(" << vecino << ", " << costo << ") ";
            cout << "\n";
        }
    }

    void mostrarEstadisticas() {
        int totalEnlaces = 0;
        for (auto& [_, router] : routers)
            totalEnlaces += router->vecinos.size();

        cout << "Total de routers: " << routers.size() << "\n";
        cout << "Total de enlaces: " << totalEnlaces / 2 << "\n";
    }

    void mostrarHistorial() {
        for (const string& evento : historial)
            cout << "- " << evento << "\n";
    }

    void encontrarRutaMasCorta(const string& origen, const string& destino) {
        auto [distancia, camino] = dijkstra(origen, destino);
        if (distancia == numeric_limits<int>::max()) {
            cout << "No hay ruta entre " << origen << " y " << destino << ".\n";
            return;
        }

        cout << "Costo: " << distancia << " | Camino: ";
        for (const string& nodo : camino)
            cout << nodo << " ";
        cout << "\n";

        historial.push_back("Ruta consultada de " + origen + " a " + destino);
    }

private:
    void limpiarRed() {
        for (auto& [_, router] : routers)
            delete router;
        routers.clear();
    }

    pair<int, vector<string>> dijkstra(string origen, string destino) {
        map<string, int> dist;
        map<string, string> anterior;

        for (auto& [nombre, _] : routers)
            dist[nombre] = numeric_limits<int>::max();

        dist[origen] = 0;
        using P = pair<int, string>;
        priority_queue<P, vector<P>, greater<>> cola;
        cola.push({0, origen});

        while (!cola.empty()) {
            auto [d, u] = cola.top(); cola.pop();

            for (auto& [vecino, costo] : routers[u]->vecinos) {
                int nuevoDist = d + costo;
                if (nuevoDist < dist[vecino]) {
                    dist[vecino] = nuevoDist;
                    anterior[vecino] = u;
                    cola.push({nuevoDist, vecino});
                }
            }
        }

        vector<string> camino;
        if (dist[destino] == numeric_limits<int>::max()) return {dist[destino], camino};

        for (string v = destino; v != origen; v = anterior[v])
            camino.insert(camino.begin(), v);
        camino.insert(camino.begin(), origen);

        return {dist[destino], camino};
    }
};

// Menú
void mostrarMenu() {
    cout << "\nSistema de Gestion de Red\n";
    cout << "1. Cargar topologia desde archivo\n";
    cout << "2. Generar red aleatoria\n";
    cout << "3. Agregar enrutador\n";
    cout << "4. Eliminar enrutador\n";
    cout << "5. Actualizar enlace\n";
    cout << "6. Encontrar ruta mas corta\n";
    cout << "7. Mostrar estado de la red\n";
    cout << "8. Mostrar estadisticas\n";
    cout << "9. Mostrar historial\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
}

// Función principal
int main() {
    Network red;
    int opcion;
    string a, b;
    int costo;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
        case 1:
            red.cargarTopologia("topologia.txt");
            break;
        case 2:
            red.generarRedAleatoria(5);
            break;
        case 3:
            cout << "Nombre del enrutador: ";
            cin >> a;
            red.agregarRouter(a);

            char opcionVecinos;
            cout << "¿Desea agregar vecinos a " << a << "? (s/n): ";
            cin >> opcionVecinos;

            while (opcionVecinos == 's' || opcionVecinos == 'S') {
                cout << "Nombre del vecino: ";
                cin >> b;
                cout << "Costo de enlace entre " << a << " y " << b << ": ";
                cin >> costo;

                red.agregarRouter(b); // se asegura que el vecino exista
                red.conectarRouters(a, b, costo);

                cout << "¿Desea agregar otro vecino a " << a << "? (s/n): ";
                cin >> opcionVecinos;
            }
            break;

        case 4:
            cout << "Nombre del enrutador a eliminar: ";
            cin >> a;
            red.eliminarRouter(a);
            break;
        case 5:
            cout << "Router A: "; cin >> a;
            cout << "Router B: "; cin >> b;
            cout << "Costo: "; cin >> costo;
            red.conectarRouters(a, b, costo);
            break;
        case 6:
            cout << "Origen: "; cin >> a;
            cout << "Destino: "; cin >> b;
            red.encontrarRutaMasCorta(a, b);
            break;
        case 7:
            red.mostrarEstadoRed();
            break;
        case 8:
            red.mostrarEstadisticas();
            break;
        case 9:
            red.mostrarHistorial();
            break;
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción no válida\n";
        }

    } while (opcion != 0);

    return 0;
}
