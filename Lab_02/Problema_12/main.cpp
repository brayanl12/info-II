#include <iostream>

using namespace std;

bool esCuadradoMagico(int matriz[][10], int n)
{
    int sumaMagica = 0;

    for (int j = 0; j < n; j++)
    {
        sumaMagica +=matriz[0][j];
    }

    for(int i = 1; i < n; i++)
    {
        int sumaFila = 0;
        for(int j = 0; j < n; j++)
        {
            sumaFila += matriz[i][j];
        }
        if(sumaFila != sumaMagica)
        {
            return false;
        }
    }

    for(int j = 0; j < n; j++)
    {
        int sumaColumna = 0;
        for(int i = 0; i < n; i++)
        {
            sumaColumna += matriz[i][j];
        }
        if (sumaColumna != sumaMagica)
        {
            return false;
        }
    }

    int sumaDiagonal1 = 0;
    for (int i = 0; i < n; i++)
    {
        sumaDiagonal1 += matriz [i][i];
    }
    if(sumaDiagonal1 != sumaMagica)
    {
        return false;
    }
    int sumaDiagonal2 = 0;
    for (int i = 0; i < n; i++)
    {
        sumaDiagonal2 += matriz [i][n - i - 1];
    }
    if (sumaDiagonal2 != sumaMagica)
    {
        return false;
    }
    return true;
}
int main()
{
    int n;
    cout <<"Ingrese el tamaño de la matriz cuadrada (n x n): ";
    cin >> n;

    int matriz [10][10];

    cout << "Ingrese los elementos de la matriz: "<< endl;
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> matriz [i][j];
        }
    }

    if(esCuadradoMagico(matriz, n))
    {
        cout <<"La matriz es un cuadrado magico" << endl;
    }
    else
    {
        cout <<"La matriz NO es un cuadrado magico" << endl;
    }
    return 0;
}
