#include <iostream>

using namespace std;

/*1.Escriba un programa que pida dos numeros A y B e imprima en pantallla el residuo de la division A/B.*/
void ejercicio1();

/*3.Escriba un programa que pida dos numeros A y B e imprima en pantalla el mayor*/
int ejercicio3();

/*5.Escriba un programa que pida dos numeros A y B e imprima en pantalla la division A/B con redondeo.*/
int ejercicio5();

/*7.Escriba un programa que pida un numero N e imprima en pantalla la suma de todos los numeros entre 0 y N (incluyendose el mismo).*/
int ejercicio7();

/*9.Escriba un programa que pida un numero N e imprima el perimetro y area de un circulo con radio N. Nota: use 3.1416 como una aproximacion de pi.*/
float ejercicio9();

/*11.Escriba un programa que pida un numero N e imprima en pantalla su tabla de multiplicar hasta 10xN.*/
int ejercicio11();

/*13.Escriba un programa que pida un numero N e imprima todos los divisores de N*/
int ejercicio13();

/*15.Escriba un programa que pida constantemente numeros hasta que ingrese el numero cero e imprima en pantalla la suma de todos los numeros ingresados.*/
int ejercicio15();

/*17.Escriba un programa que pida constantemente numeros hasta que se ingrese el numero cero e imprima en pantalla el mayor de todos los numeros ingresados.*/
int ejercicio17();

/*19.Escriba un programa que pida un numero N e imprima si es o no un numero primo.*/
int ejercicio19();

/*21.EScriba un programa que pida un caracter C, si es una letra la debe convertir de mayuscula a minuscula y viceversa e imprimirla.*/
char ejercicio21();

/*23.Escriba un programa que pida dos numeros A y B e imprima en pantalla el minimo comun multiplo entre los dos*/
int ejercicio23();

/*25.Escriba un programa que pida un numero N e imprima en pantalla la cantidad de digitos N.*/
int ejercicio25();
/*27.Escriba un programa que actúe como una calculadora con operacion suma,resta,multiplicacion y division, el usuario debe ingresar los operandos y la operacion a realizar.*/
double ejercicio27();
/*29.Escriba un programa que adivine un numero A (entre 0 y 100) seleccionado por el usuario (el numero No se ingresa al programa), el programa imprimira en pantalla un numero B y el usuario usara los simbolos '>', '<' y '=' para indicarle al programa si B es mayor,menor o igual que A. El programa imprimira un nuevo numero B, con base en simbolo ingresdo por el usuario, y repetira el proceso hasta acertar el numero seleccionado por el usuario.*/
int ejercicio29();
/*Escriba un programa que identifique si un carcter ingresado es una vocal, una consonante o ninguna de las 2 e imprima un mensaje segun el caso.*/

int main()
{
    ejercicio17();
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

int ejercicio7()
{
    int N;
    int sumatoria=0;
    cout <<"Ingrese numero N:"<<endl;
    cin >>N;
    for(int i = 1; i<=N; i++)
    {
        sumatoria += i;
    }
    cout <<"La sumatoria desde 0 hasta "<< N << " es " << sumatoria <<endl;
    return 0;
}

float ejercicio9()
{
    double N, A, P;
    float pi= 3.1416;
    cout <<"Ingresar numero N:"<<endl;
    cin >> N;
    A= pi*N*N;
    P= 2*pi*N;
    cout <<"Perimetro: "<< P <<endl;
    cout <<"Area: "<< A <<endl;
    return 0;
}

int ejercicio11()
{
    int N, i, m;
    cout << "Ingresar numero N:"<<endl;
    cin >> N;
    for(i=1; i<=10; i++)
    {
        m= N*i;
        cout << i <<"x"<< N << "=" << m << endl;
    }
    return 0;
}

int ejercicio13()
{
    int N;
    cout <<"Ingresar numero N:"<<endl;
    cin >> N;
    cout <<"Los divisores: "<<endl;
    for(int i=1; i <= N; i++)
    {
        if(N % i == 0)
        {
            cout << i <<endl;
        }
    }
    return 0;
}

int ejercicio15()
{
    int N,suma;
    do
    {
        cout << "Ingrese numero:"<<endl;
        cin >> N;
        suma += N;
    }
    while(N != 0);
    cout <<"El resultado de la sumatoria es:"<< suma<<endl;
    return 0;
}

int ejercicio17()
{
    int N,mayor;
    do
    {
        cout << "Ingrese numero:"<<endl;
        cin >> N;
        if (N>mayor)
        {
            mayor = N;
        }
        else
        {
            mayor = mayor;
        }
    }
    while(N != 0);
    cout <<"El numero mayor fue:"<< mayor <<endl;
    return 0;
}

int ejercicio19()
{
    int N;
    cout <<"Ingrese un numero N: "<<endl;
    cin >>N;
    if(N%2 != 0)
    {
        cout << N <<" es un numero primo"<<endl;
    }
    else
    {
        cout << N <<" NO es un numero primo"<<endl;
    }
    return 0;
}

char ejercicio21()
{
    char c;
    cout <<"Ingresar un caracter: "<<endl;
    cin >> c;
    if (c >= 'A' && c <= 'Z')
    {
        c += 32;
    }
    else if (c >= 'a' && c <= 'z')
    {
        c -= 32;
    }

    else
    {
        cout << "El caracter no es una letra." <<endl;
    }
    cout <<"Letra convertida: "<< c <<endl;
    return 0;
}

int ejercicio23()
{
    int A, B, mcm, min;
    cout <<"Ingrese numero A:"<<endl;
    cin >>A;
    cout <<"Ingrese numero B:"<<endl;
    cin >>B;
    if( A < B)
    {
        min = A;
    }
    else
    {
        min = B;
    }

    for (int i=1; i<=min; i++)
    {
        if(A%i ==0 && B%i==0)
        {
            int mcd=i;
            mcm= (A*B)/mcd;
        }
    }
    cout <<"El MCM de "<< A <<" y "<< B <<" es: "<< mcm <<endl;
    return 0;
}

int ejercicio25()
{
    int D, N, x = 0;
    cout<<"Ingrese numero N: "<<endl;
    cin>> N;
    D=N;
    while(D!=0)
    {
        D= D/10;
        x++;
    }
    cout<< N <<" tiene "<< x <<" digitos."<<endl;
    return 0;
}

double ejercicio27()
{
    double A, B, resultado;
    char op;
    cout<< "Ingresar numero A: "<<endl;
    cin>>A;
    cout<< "Ingresar operacion (+,-,*,/): "<<endl;
    cin>>op;
    cout<< "Ingresar numero B: "<<endl;
    cin>>B;
    switch (op)
    {
    case'+':
        resultado = A + B;
        break;
    case'-':
        resultado = A - B;
        break;
    case'*':
        resultado = A * B;
        break;
    case'/':
        if(B !=0)
        resultado = A / B;
        else
        {
            cout <<"No se puede dividir entre cero"<<endl;
            return 1;
        }
        break;
    default:
        cout <<"El operador no se encuentra."<<endl;
        return 1;
    }
    cout << A << op << B << "="<< resultado <<endl;
    return 0;
}
int ejercicio29()
{
    int B, min=0, max=100;
    char respuesta;
    cout<<"Piense en un numero (entre 0 y 100) e ingrese '>' si es mayor, '<' es menor o '=' si es igual al numero pensado."<<endl;
    while(min<=max)
    {
        B=(min+max)/2;
        cout<< "Su numero es: "<< B <<"?"<<endl;
        cout<< "Responda con (>, <, =): "<< endl;
        cin>>respuesta;

        if (respuesta == '=')
        {
            cout<<"El programa adivino su numero: "<< B << endl;
            break;
        }
        else if (respuesta == '>')
        {
            min= B+1;
        }
        else if (respuesta == '<')
        {
            max= B-1;
        }
        else
        {
            cout <<"No usaste los operadores de comparacion." <<endl;
        }
    }

    return 0;
}


