#include <iostream>

using namespace std;

unsigned long long factorial(int n)
{
    unsigned long long resultado = 1;
    for (int i = 2; i <= n; ++i)
    {
        resultado *= i;
    }
    return resultado;
}

unsigned long long contarCaminos(int n)
{
    return factorial(2 * n) / (factorial (n) * factorial(n));
}

int main()
{
    int n;

    cout <<"Ingrese el valor de n para la malla nxn: ";
    cin >> n;

    unsigned long long caminos = contarCaminos(n);

    cout << "Para una malla de " << n << "x" << n << " puntos hay " << caminos << " caminos" <<endl;

    return 0;
}
