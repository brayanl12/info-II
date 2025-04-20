#include <iostream>

using namespace std;

int contarEstrellas (int m[][7], int filas, int columnas)
{
    int estrellas = 0;
    for(int i = 1; i < filas - 1; i++)
    {
        for(int j = 1; j < columnas - 1; j++)
        {
            int suma = m[i][j] + m[i][j - 1]+ m[i][j + 1] + m[i - 1][j] + m[i + 1][j];
            if (suma / 5.0 > 6)
            {
                estrellas++;
            }
        }
    }
    return estrellas;
}

int main()
{
    int matriz [7][7]=
    {
        {0,3,4,0,0,6,8},
        {5,13,6,0,2,0,3},
        {0,0,2,6,7,0,0},
        {0,0,4,15,4,0,0},
        {0,0,7,12,6,0,0},
        {5,0,6,10,8,4,0},
        {5,0,6,0,8,0,0}
    };

    int total = contarEstrellas(matriz, 7,7);
    cout << "Numero de estrellas encontradas: " << total << endl;
    return 0;
}
