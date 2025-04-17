#include <iostream>

using namespace std;

void fun_c(double *a, int n, double *promedio, double*suma){
    int i;
    *suma = 0.0;
    for (i = 0; i < n; i++)
        *suma += *(a + i);
    *promedio = *suma / n;
}
int main()
{
    double datos[10.0, 20.0, 30.0, 40.0, 50.0];
    int n = 5;
    double promedio, suma;
    fun_c(datos, n, &promedio, &suma);
    cout<< "Suma: "<< suma <<endl;
    cout<<"Promedio: "<< promedio <<endl;
    return 0
}
