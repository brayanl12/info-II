#include <iostream>
#include <fstream>
#include <cstring>  // Para strlen, strncpy, etc.

using namespace std;

const int MAX_BITS = 1000000;       // Tamaño máximo del binario total
const int MAX_BLOQUES = 10000;      // Máximo número de bloques
const int MAX_TAM_BLOQUE = 128;     // Tamaño máximo por bloque

// Leer el archivo binario y convertirlo a una cadena de bits ('0' y '1')
void leerArchivoComoBinario(const char* filename, char* binario, int& longitud) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo\n";
        exit(1);
    }

    longitud = 0;
    char c;
    while (file.get(c)) {
        for (int i = 7; i >= 0; --i) {
            binario[longitud++] = ((c >> i) & 1) ? '1' : '0';
        }
    }
    binario[longitud] = '\0';
    file.close();
}

// Contar la cantidad de ceros y unos en un bloque
void contarBits(const char* bloque, int& ceros, int& unos) {
    ceros = unos = 0;
    for (int i = 0; bloque[i] != '\0'; ++i) {
        if (bloque[i] == '0') ceros++;
        else unos++;
    }
}

// Invertir todos los bits en un bloque
void invertirTodos(char* bloque) {
    for (int i = 0; bloque[i] != '\0'; ++i) {
        bloque[i] = (bloque[i] == '0') ? '1' : '0';
    }
}

// Rotar bits a la izquierda
void rotarIzquierda(char* bloque) {
    int len = strlen(bloque);
    if (len <= 1) return;
    char primero = bloque[0];
    for (int i = 0; i < len - 1; ++i) {
        bloque[i] = bloque[i + 1];
    }
    bloque[len - 1] = primero;
}

// Rotar bits a la derecha
void rotarDerecha(char* bloque) {
    int len = strlen(bloque);
    if (len <= 1) return;
    char ultimo = bloque[len - 1];
    for (int i = len - 1; i > 0; --i) {
        bloque[i] = bloque[i - 1];
    }
    bloque[0] = ultimo;
}

// Codificación método 1: Inversión del primer bloque y decisiones en los siguientes
void codificarMetodo1(char** bloques, int totalBloques) {
    invertirTodos(bloques[0]);
    for (int i = 1; i < totalBloques; ++i) {
        int ceros, unos;
        contarBits(bloques[i - 1], ceros, unos);
        if (unos > ceros) {
            rotarIzquierda(bloques[i]);
        } else if (ceros > unos) {
            rotarDerecha(bloques[i]);
        } else {
            invertirTodos(bloques[i]);
        }
    }
}

// Codificación método 2: Invertir todos los bits de todos los bloques
void codificarMetodo2(char** bloques, int totalBloques) {
    for (int i = 0; i < totalBloques; ++i) {
        invertirTodos(bloques[i]);
    }
}

// Convertir el binario en cadena a bytes y escribirlo como archivo binario
void escribirBinario(const char* binario, int longitud, const char* filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error al abrir archivo de salida\n";
        exit(1);
    }

    for (int i = 0; i < longitud; i += 8) {
        char byte = 0;
        for (int j = 0; j < 8; ++j) {
            byte <<= 1;
            if (i + j < longitud && binario[i + j] == '1') {
                byte |= 1;
            }
        }
        file.put(byte);
    }
    file.close();
}

// Programa principal
int main() {
    char inputFile[100], outputFile[100];
    int n, metodo;

    cout << "Archivo de entrada: ";
    cin >> inputFile;
    cout << "Archivo de salida: ";
    cin >> outputFile;
    cout << "Semilla (n): ";
    cin >> n;
    cout << "Metodo (1 o 2): ";
    cin >> metodo;

    if (n <= 0 || n > MAX_TAM_BLOQUE) {
        cerr << "La semilla n debe estar entre 1 y " << MAX_TAM_BLOQUE << endl;
        return 1;
    }

    // Reservar memoria dinámica
    char* binario = new char[MAX_BITS];
    char* resultado = new char[MAX_BITS];
    char** bloques = new char*[MAX_BLOQUES];
    for (int i = 0; i < MAX_BLOQUES; ++i) {
        bloques[i] = new char[MAX_TAM_BLOQUE];
    }

    int longitud;
    leerArchivoComoBinario(inputFile, binario, longitud);

    // Dividir en bloques
    int totalBloques = (longitud + n - 1) / n;
    for (int i = 0; i < totalBloques; ++i) {
        int start = i * n;
        int len = (start + n <= longitud) ? n : longitud - start;
        strncpy(bloques[i], &binario[start], len);
        bloques[i][len] = '\0';
    }

    // Aplicar el método de codificación
    if (metodo == 1) {
        codificarMetodo1(bloques, totalBloques);
    } else if (metodo == 2) {
        codificarMetodo2(bloques, totalBloques);
    } else {
        cout << "Metodo invalido\n";
        return 1;
    }

    // Reconstruir binario final
    int pos = 0;
    for (int i = 0; i < totalBloques; ++i) {
        for (int j = 0; bloques[i][j] != '\0'; ++j) {
            resultado[pos++] = bloques[i][j];
        }
    }
    resultado[pos] = '\0';

    escribirBinario(resultado, pos, outputFile);
    cout << "Codificacion completa.\n";

    // Liberar memoria dinámica
    delete[] binario;
    delete[] resultado;
    for (int i = 0; i < MAX_BLOQUES; ++i) {
        delete[] bloques[i];
    }
    delete[] bloques;

    return 0;
}
