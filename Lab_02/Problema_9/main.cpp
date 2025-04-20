#include <iostream>

using namespace std;

int longitud (const char* cadena)
{
    int len = 0;
    while (cadena [len]!= '\0')
    {
        len++;
    }
    return len;
}

int convNum(const char* cadena, int inicio, int n)
{
    int num = 0;
    for(int i = 0; i < n; i++)
    {
        num = num * 10 + (cadena[inicio + i] - '0');
    }
    return num;
}
int main()
{
    const int t = 100;
    char entrada[t];
    char comp[t];
    int n;

    cout <<"Ingrese el valor n: ";
    cin >> n;

    cout <<"Ingrese la cadena de numeros: ";
    cin >> entrada;

    int len = longitud(entrada);
    int faltante = (n - (len % n)) % n;
    int total = len + faltante;

    for(int i = 0; i < faltante; i++)
    {
        comp[i] = '0';
    }
    for(int i = 0; i < len; i++)
    {
        comp[ faltante + i] = entrada[i];
    }
    comp[total] = '\0';

    int suma = 0;

    for(int i = 0; i < total; i += n)
    {
        suma += convNum(comp, i, n);
    }

    cout <<"Original: " << entrada << endl;
    cout << "Suma: " << suma <<endl;
}
