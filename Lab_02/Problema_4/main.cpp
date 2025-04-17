#include <iostream>

using namespace std;

int convNumero(const char* cadena){
    int n = 0;
    for (int i = 0; cadena[i] != '\0'; i++){
        n = n * 10 + (cadena[i]-'0');
    }
    return n;
}
int main()
{
    char cadena[100];
    cout << "Ingrese un cadena de caracteres numericos: ";
    cin >> cadena;

    int n = convNumero(cadena);

    cout <<"El numero entero es: "<< n <<endl;

    return 0;
}

