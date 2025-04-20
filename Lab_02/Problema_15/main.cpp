#include <iostream>

using namespace std;

void interseccionRectangulos(int A[4], int B[4], int C[4])
{
    int x1 = max(A[0], B[0]);
    int y1 = max(A[1], B[1]);
    int x2 = min(A[0] + A[2], B[0] + B[2]);
    int y2 = min(A[1] + A[3], B[1] + B[3]);

    if(x2 > x1 && y2 > y1)
    {
        C[0] = x1;
        C[1] = y1;
        C[2] = x2 - x1;
        C[3] = y2 - y1;
    }
    else
    {
        C[0] = 0;
        C[1] = 0;
        C[2] = 0;
        C[3] = 0;
    }
}
int main()
{
    int A[4], B[4],C[4];

    cout << "Ingrese los datos del primer rectangulo (x y ancho alto): ";
    for (int i = 0; i < 4; i++)
    {
        cin >> A[i];
    }

    cout << "Ingrese los datos del rectangulo B (x y ancho alto): ";
    for (int i = 0; i < 4; i++)
    {
        cin >> B[i];
    }

    interseccionRectangulos(A,B,C);

    cout << "La interseccion es: ";
    for  (int i = 0; i < 4; i++)
    {
        cout << C[i]<< " ";
    }
    cout << endl;

    return 0;
}
