#include <iostream>

using namespace std;

void entCadena(int n, char* cadena){
    int i = 0;
    bool negativo= false;

    if (n < 0){
        negativo = true;
        n = -n;
    }

    do{
        cadena[i++]= (n % 10) +'0';
        n/=10;
    }
    while( n > 0);
    if (negativo){
        cadena[i++]='-';
    }
    cadena[i]= '\0';

    int inicio = 0, fin = i -1;
    while (inicio < fin){
        char temp = cadena[inicio];
        cadena[inicio] = cadena[fin];
        cadena[fin] = temp;
        inicio++;
        fin--;
    }

}

int main()
{
    int n;
    char cadena[100];
    cout<<"Ingrese un numero entero: ";
    cin >> n;
    entCadena(n,cadena);
    cout <<"la cadena es:" << cadena <<endl;
    return 0;
}
