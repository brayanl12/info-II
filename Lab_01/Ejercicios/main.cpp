#include <iostream>

using namespace std;

/*1.Escriba un programa que pida dos numeros A y B e imprima en pantallla el residuo de la division A/B.*/
void ejercicio1();

/*3.Escriba un programa que pida dos numeros A y B e imprima en pantalla el mayor*/
int ejercicio3();

/*5.Escriba un programa que pida dos numeros A y B e imprima en pantalla la division A/B con redondeo*/
int ejercicio5();


int main()
{
    ejercicio5();
    return 0;
}

void ejercicio1()
{
    int a, b;
    cout <<"Ingresar  numeros A y B: "<<endl;
    cin >> a >> b;
    cout << "El residuo de la division de "<< a <<"/"<< b << " es " << a%b <<endl;
}

int ejercicio3()
{
    int a, b;
    cout <<"Ingrese numeros A y B: "<<endl;
    cin >> a >> b;
    if( a > b)
        cout <<"El mayor es: "<< a <<endl;
    else
        cout <<"El mayor es: "<< b <<endl;
    return 0;
}

int ejercicio5()
{
    int a, b;
    cout <<"Ingrese numeros A y B: "<<endl;
    cin >> a >> b;
    cout << "La division de "<< a << "/" << b << " con redondeo es: "<< (a+b/2)/b <<endl;
    return 0;
}

