#include <iostream>

using namespace std;

const int N = 5;

void llenarMatriz(int m[N][N])
{
    int num = 1;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            m[i][j] = num ++;
        }
    }
}

void imprimirMatriz(int m[N][N])
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cout << m[i][j]<<"\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

void rotar90(int origen[N][N], int destino[N][N])
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            destino [j][N-1-i]= origen [i][j];
        }
    }
}

void copiarMatriz(int origen [N][N], int destino[N][N])
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            destino[i][j]= origen[i][j];

        }
    }
}
int main()
{
    int matriz[N][N];
    int rotada[N][N];

    llenarMatriz(matriz);

    cout << "Matriz original\n";
    imprimirMatriz(matriz);

    rotar90(matriz, rotada);
    cout << "Rotada 90\n";
    imprimirMatriz(rotada);

    int rotada180[N][N];
    rotar90(rotada, rotada180);
    cout << "Rotada 180\n";
    imprimirMatriz(rotada180);

    int rotada270[N][N];
    rotar90(rotada180, rotada270);
    cout << "Rotada 270\n";
    imprimirMatriz(rotada270);

    return 0;
}
