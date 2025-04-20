#include <iostream>
using namespace std;

const int FILAS = 15;
const int COLUMNAS = 20;
char sala[FILAS][COLUMNAS];

void iniSala() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            sala[i][j] = '-';
        }
    }
}

void mosSala() {
    cout << "    ";
    for (int i = 1; i <= COLUMNAS; i++) {
        if (i < 10) cout << i << "  ";
        else cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < FILAS; i++) {
        cout << char('A' + i) << " | ";
        for (int j = 0; j < COLUMNAS; j++) {
            cout << sala[i][j] << "  ";
        }
        cout << endl;
    }
}

int leerEntero() {
    int valor = 0;
    while (true) {
        cin >> valor;
        if (valor >= 1 && valor <= 20) break;
        cout << "Entrada invalida. Ingrese un numero entre 1 y 20: ";
    }
    return valor;
}

void gestAsiento(bool reservar) {
    char filaLetra;
    int numAsiento;

    cout << "Ingrese la fila (A-O): ";
    cin >> filaLetra;
    if (filaLetra >= 'a' && filaLetra <= 'z') filaLetra -= 32;

    cout << "Ingrese el numero de asiento (1-20): ";
    numAsiento = leerEntero();

    int fila = filaLetra - 'A';
    int columna = numAsiento - 1;

    if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) {
        cout << "Asiento invalido.\n";
        return;
    }

    if (reservar) {
        if (sala[fila][columna] == '-') {
            sala[fila][columna] = '+';
            cout << "Asiento reservado con exito.\n";
        } else {
            cout << "Ese asiento ya esta reservado.\n";
        }
    } else {
        if (sala[fila][columna] == '+') {
            sala[fila][columna] = '-';
            cout << "Reserva cancelada con exito.\n";
        } else {
            cout << "Ese asiento ya esta disponible.\n";
        }
    }
}

int main() {
    iniSala();
    char opcion;

    do {
        cout << "\n--- Menu Cine ---\n";
        cout << "1. Ver sala\n";
        cout << "2. Reservar asiento\n";
        cout << "3. Cancelar reserva\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion != '1' && opcion != '2' && opcion != '3' && opcion != '0') {
            cout << "Opcion invalida. Por favor, intente de nuevo.\n";
            continue;
        }

        switch (opcion) {
        case '1':
            mosSala();
            break;
        case '2':
            gestAsiento(true);
            break;
        case '3':
            gestAsiento(false);
            break;
        case '0':
            cout << "Saliendo...\n";
            break;
        }

    } while (opcion != '0');

    return 0;
}
