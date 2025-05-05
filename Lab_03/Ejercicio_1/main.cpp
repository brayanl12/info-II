#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string leerArchivoComoBinario(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo '" << filename << "'.\n";
        exit(1);
    }

    string binario;
    char c;
    while (file.get(c)) {
        for (int i = 7; i >= 0; --i)
            binario += ((c >> i) & 1) ? '1' : '0';
    }
    file.close();
    return binario;
}

void contarBits(const string& bloque, int& ceros, int& unos) {
    ceros = unos = 0;
    for (char bit : bloque) {
        if (bit == '0') ceros++;
        else unos++;
    }
}

string invertirTodos(const string& bloque) {
    string result = "";
    for (char bit : bloque)
        result += (bit == '0') ? '1' : '0';
    return result;
}

void codificarMetodo1(vector<string>& bloques) {
    int total = bloques.size();
    for (int i = 0; i < total; ++i) {
        string codificado = "";
        if (i == 0) {
            codificado = invertirTodos(bloques[i]);
        } else {
            int ceros = 0, unos = 0;
            contarBits(bloques[i - 1], ceros, unos);
            if (ceros == unos) {
                codificado = invertirTodos(bloques[i]);
            } else if (ceros > unos) {
                for (int j = 0; j < bloques[i].size(); ++j) {
                    codificado += (j % 2 == 1) ? ((bloques[i][j] == '0') ? '1' : '0') : bloques[i][j];
                }
            } else {
                for (int j = 0; j < bloques[i].size(); ++j) {
                    codificado += (j % 3 == 2) ? ((bloques[i][j] == '0') ? '1' : '0') : bloques[i][j];
                }
            }
        }
        bloques[i] = codificado;
    }
}

void codificarMetodo2(vector<string>& bloques) {
    for (string& bloque : bloques) {
        if (!bloque.empty()) {
            string rotado = bloque.back() + bloque.substr(0, bloque.size() - 1);
            bloque = rotado;
        }
    }
}

void escribirBinario(const string& binario, const string& filename) {
    ofstream file(filename, ios::binary);
    for (size_t i = 0; i < binario.size(); i += 8) {
        string byteStr = binario.substr(i, 8);
        while (byteStr.size() < 8)
            byteStr += '0';
        char byte = 0;
        for (int j = 0; j < 8; ++j)
            byte |= (byteStr[j] - '0') << (7 - j);
        file.put(byte);
    }
    file.close();
}

int main() {
    string inputFile, outputFile;
    int n, metodo;

    cout << "Archivo de entrada: ";
    cin >> inputFile;
    cout << "Archivo de salida: ";
    cin >> outputFile;
    cout << "Semilla (n): ";
    cin >> n;
    cout << "Metodo (1 o 2): ";
    cin >> metodo;

    string binario = leerArchivoComoBinario(inputFile);
    int totalBloques = (binario.size() + n - 1) / n;

    vector<string> bloques;
    for (int i = 0; i < totalBloques; ++i) {
        bloques.push_back(binario.substr(i * n, n));
    }

    if (metodo == 1) {
        codificarMetodo1(bloques);
    } else if (metodo == 2) {
        codificarMetodo2(bloques);
    } else {
        cout << "Metodo invalido.\n";
        return 1;
    }

    string resultado = "";
    for (const string& bloque : bloques)
        resultado += bloque;

    escribirBinario(resultado, outputFile);
    cout << "Codificacion completa.\n";
    return 0;
}
