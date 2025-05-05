#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <tuple>
#include <filesystem> // C++17

using namespace std;
namespace fs = filesystem;

string simpleEncrypt(const string& input, int seed) {
    string result = input;
    for (char& c : result)
        c = c ^ seed;
    return result;
}

string simpleDecrypt(const string& input, int seed) {
    return simpleEncrypt(input, seed);
}

void crearArchivoAdminSiNoExiste(const string& archivo, int seed) {
    if (!fs::exists(archivo)) {
        string claveAdmin = "claveAdmin123";
        string claveEncriptada = simpleEncrypt(claveAdmin, seed);
        ofstream file(archivo);
        file << claveEncriptada;
        cout << "Archivo '" << archivo << "' creado con la clave admin por defecto.\n";
    }
}

bool validarAdmin(const string& archivo, const string& claveIngresada, int seed) {
    ifstream file(archivo);
    string claveGuardada;
    if (getline(file, claveGuardada)) {
        claveGuardada = simpleDecrypt(claveGuardada, seed);
        return claveGuardada == claveIngresada;
    }
    return false;
}

void registrarUsuario(const string& archivo, int seed) {
    ofstream file(archivo, ios::app);
    string cedula, clave;
    double saldo;
    cout << "Cedula: "; cin >> cedula;
    cout << "Clave: "; cin >> clave;
    cout << "Saldo: "; cin >> saldo;

    string linea = cedula + "," + clave + "," + to_string(saldo);
    linea = simpleEncrypt(linea, seed);
    file << linea << endl;
    cout << "Usuario registrado.\n";
}

void cargarUsuarios(const string& archivo, map<string, tuple<string, double>>& usuarios, int seed) {
    ifstream file(archivo);
    string linea;
    while (getline(file, linea)) {
        linea = simpleDecrypt(linea, seed);
        stringstream ss(linea);
        string cedula, clave, saldoStr;
        getline(ss, cedula, ',');
        getline(ss, clave, ',');
        getline(ss, saldoStr);
        usuarios[cedula] = make_tuple(clave, stod(saldoStr));
    }
}

void guardarUsuarios(const string& archivo, const map<string, tuple<string, double>>& usuarios, int seed) {
    ofstream file(archivo);
    for (const auto& [cedula, datos] : usuarios) {
        string linea = cedula + "," + get<0>(datos) + "," + to_string(get<1>(datos));
        linea = simpleEncrypt(linea, seed);
        file << linea << endl;
    }
}

void menuUsuario(map<string, tuple<string, double>>& usuarios, const string& cedula) {
    int opcion;
    do {
        cout << "1. Consultar saldo\n2. Retirar dinero\n0. Salir\nOpcion: ";
        cin >> opcion;
        if (opcion == 1 || opcion == 2) {
            get<1>(usuarios[cedula]) -= 1000; // costo por operación
            if (opcion == 1) {
                cout << "Saldo actual: " << get<1>(usuarios[cedula]) << endl;
            } else {
                double monto;
                cout << "Monto a retirar: "; cin >> monto;
                if (monto + 1000 <= get<1>(usuarios[cedula])) {
                    get<1>(usuarios[cedula]) -= monto;
                    cout << "Retiro exitoso. Saldo restante: " << get<1>(usuarios[cedula]) << endl;
                } else {
                    cout << "Fondos insuficientes.\n";
                }
            }
        }
    } while (opcion != 0);
}

void accesoCliente(const string& archivo, int seed) {
    map<string, tuple<string, double>> usuarios;
    cargarUsuarios(archivo, usuarios, seed);
    string cedula, clave;
    cout << "Cedula: "; cin >> cedula;
    cout << "Clave: "; cin >> clave;
    if (usuarios.find(cedula) != usuarios.end() && get<0>(usuarios[cedula]) == clave) {
        menuUsuario(usuarios, cedula);
        guardarUsuarios(archivo, usuarios, seed);
    } else {
        cout << "Credenciales invalidas.\n";
    }
}

int main() {
    string archivoUsuarios = "usuarios.txt";
    string archivoAdmin = "sudo.txt";
    int seed;

    cout << "Semilla de encriptacion: ";
    cin >> seed;

    crearArchivoAdminSiNoExiste(archivoAdmin, seed);

    int opcion;
    cout << "1. Acceder como administrador\n2. Acceder como cliente\nOpcion: ";
    cin >> opcion;
    cin.ignore();

    if (opcion == 1) {
        string clave;
        cout << "Clave admin: ";
        getline(cin, clave);
        if (validarAdmin(archivoAdmin, clave, seed)) {
            cout << "Acceso concedido.\n";
            registrarUsuario(archivoUsuarios, seed);
        } else {
            cout << "Clave incorrecta.\n";
        }
    } else if (opcion == 2) {
        accesoCliente(archivoUsuarios, seed);
    }

    return 0;
}
