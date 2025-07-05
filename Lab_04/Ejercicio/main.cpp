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
        for (auto& par : routers) //Recorrer router y auto deduce el tipo automaticamente (pair<string,Router*>)
            delete par.second; //Elimina el router apuntado por el puntero
    }

    void agregarRouter(const string& nombre) { //Recibe nombre del router
        if (!routers.count(nombre)) { //Devuelve 1 si el router existe y 0 si no existe
            routers[nombre] = new Router(nombre); //Crea un nuevo Router
            historial.push_back("Agregado router: " + nombre); //Agrega al final el vector cadena
        }
    }

    void eliminarRouter(const string& nombre) {
        if (!routers.count(nombre)) {
            cout << "Router no existe.\n";
            return;
        }

        for (auto& [_, router] : routers) //Recorre todos los routers y se ignora "_"
            router->vecinos.erase(nombre); //Para cada router de la red,se elimina al router de su lista de vecinos

        delete routers[nombre]; //Libera memoria dinamica
        routers.erase(nombre); //Elimina la entrada del mapa de routers
        historial.push_back("Eliminado router: " + nombre); //Registra la accion en el historial
    }

    void conectarRouters(const string& a, const string& b, int costo) {
        if (routers.count(a) && routers.count(b)) { //Verifica que ambos routers existen en el mapa
            routers[a]->vecinos[b] = costo; //puntero al objeto accede al mapa de vecinos de este router
            routers[b]->vecinos[a] = costo;
            historial.push_back("Conectado " + a + " <--> " + b + " con costo " + to_string(costo));
        }
    }

    void cargarTopologia(const string& archivo) {
        ifstream file(archivo); //Lee el archivo con file que fue creado con ifstream
        if (!file.is_open()) { //Verifica si el archivo se abrió
            cout << "No se pudo abrir el archivo.\n";
            return;
        }

        string linea;
        while (getline(file, linea)) { //Lee el archivo por linea
            istringstream ss(linea); //Crea un stream sobre la linea para estraer sus componentes con >>
            string a, b;
            int costo;
            ss >> a >> b >> costo; //Extrae componentes con >>
            agregarRouter(a);
            agregarRouter(b);
            conectarRouters(a, b, costo);
        }

        historial.push_back("Topología cargada desde: " + archivo);
    }

    void generarRedAleatoria(int cantidad) {
        limpiarRed(); //Borra todos los routers existentes
        srand(time(0)); //Inializar el generador de numeros aleatorios con una semilla en la basada en la hora actual

        for (int i = 0; i < cantidad; ++i) //Crea routers segun la cantidad
            agregarRouter("R" + to_string(i));

        for (int i = 0; i < cantidad; ++i) { // recorre todas las combinaciones posibles entre routers sin repetir ni conectar un router consigo mismo
            for (int j = i + 1; j < cantidad; ++j) {
                if (rand() % 2) { //Genera un numero aleatorio del 0 al 1 si da 1 conecta Ri con Rj
                    int costo = rand() % 10 + 1;
                    conectarRouters("R" + to_string(i), "R" + to_string(j), costo);
                }
            }
        }

        historial.push_back("Red aleatoria generada con " + to_string(cantidad) + " routers.");
    }

    void mostrarEstadoRed() {
        for (auto& [nombre, router] : routers) { //Recorre todos los  conectados
            cout << nombre << " --> ";
            for (auto& [vecino, costo] : router->vecinos) //Recorre todos los vecinos (Conectados)
                cout << "(" << vecino << ", " << costo << ") ";
            cout << "\n";
        }
    }

    void mostrarEstadisticas() {
        int totalEnlaces = 0;
        for (auto& [_, router] : routers) //Recorre todos los routers de la red y no nos interesa "_", solo el puntero router
            totalEnlaces += router->vecinos.size(); //Da el numero de conexion que tiene ese router

        cout << "Total de routers: " << routers.size() << "\n"; //Obtiene el numero de elementos  que hay detro de una estructura de datos
        cout << "Total de enlaces: " << totalEnlaces / 2 << "\n";
    }

    void mostrarHistorial() {
        for (const string& evento : historial) //Referencia constante para evitar copiar cada string y asegurar que no se modifique y recorre todos los elemntos del vector historial
            cout << "- " << evento << "\n";
    }

    void encontrarRutaMasCorta(const string& origen, const string& destino) {
        auto [distancia, camino] = dijkstra(origen, destino); //Llama  funcion de dijkstra, distancia representa el costo total de la ruta mas corta
        if (distancia == numeric_limits<int>::max()) { //Si la distancia es el valor mas alto significa que no hay conexion entre origen y el destino
            cout << "No hay ruta entre " << origen << " y " << destino << ".\n";
            return;
        }

        cout << "Costo: " << distancia << " | Camino: ";
        for (const string& nodo : camino) //Recorre el vector camino para imprimir los nombres de los routers por donde pasa la ruta
            cout << nodo << " ";
        cout << "\n";

        historial.push_back("Ruta consultada de " + origen + " a " + destino);
    }

private:
    void limpiarRed() {
        for (auto& [_, router] : routers) //recorre el mapa routers
            delete router; //Libera memoria
        routers.clear(); //Limpia el mapa
    }

    pair<int, vector<string>> dijkstra(string origen, string destino) { //Funcion dijkstra
        map<string, int> dist; //Guarda la distancia minima actual conocida desde origen
        map<string, string> anterior; //Para reconstruir el camino, almacena cada nodo cual fue su nodo anterior en la ruta mas corta

        for (auto& [nombre, _] : routers)
            dist[nombre] = numeric_limits<int>::max(); //Se inicializa con un valor maximo infinito a todos los nodos menos al origen

        dist[origen] = 0; //Empieza desde cero
        using P = pair<int, string>; //Define cola de prioridades de pares donde el nodo con menor distancia sale primero
        priority_queue<P, vector<P>, greater<>> cola; //Para obtener el elemento con la menor distancia acumulada primero
        cola.push({0, origen}); //Agrega el nodo inicial con costo cero

        while (!cola.empty()) { //Mientras la cola no este vacia sigue procesando nodos
            auto [d, u] = cola.top(); cola.pop(); //La letra 'd' distancia minima y 'u' nodo actual

            for (auto& [vecino, costo] : routers[u]->vecinos) { //Revisar vecinos u
                int nuevoDist = d + costo;
                if (nuevoDist < dist[vecino]) {
                    dist[vecino] = nuevoDist;
                    anterior[vecino] = u;
                    cola.push({nuevoDist, vecino});
                }
            }
        }

        vector<string> camino; //Reconstruir camino
        if (dist[destino] == numeric_limits<int>::max()) return {dist[destino], camino};

        for (string v = destino; v != origen; v = anterior[v]) //reconstruye el camino desde el destido hacia el origen usando mapa anterior y insert pone los nodos al inicio del vector para que queden orden correcto
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
