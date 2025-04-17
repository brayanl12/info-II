#include <iostream>

using namespace std;

/*Problema 1. Escribe un programa que identifique si un caracter ingresado es una vocal, una consonante o ninguna de las 2 e imprima un mensaje segun el caso.*/
char problema1();
/*Problema 3. Escriba un programa que debe leer un mes y un dia de dicho mes para luego decir esa combinacion de mes y dia son validos. El caso mas especial es 29 de febrero, en dicho caso imprimir "posiblemente año bisiesto*/
int problema3();
/*Problema 5. Escriba un programa que muestre el siguiente patron en la pantalla:*/
int problema5();
/*Problema7. En la serie de Fibonacci, cada numero es la suma de los 2 anteriores e inicia con 1 y 1.Ej:1,1,2,3,5,8, ... Esciba un programa que reciba un numero n y halle la suma de todos los numeros pares en la serie de FIbonacci menores a n*/
int problema7();
/*Problema 9. Escriba un programa que pida un numero entero N e imprima el resultado de la suma de todod sus digitos elevados a si mismos.*/
int problema9();
/*Problema 11. Escriba un programa que reciba un numero y calcule el minimo comun multiplo de todos los numero enteros entre 1 y el numero ingresado.*/
int problema11();
/*Problema 13. Escriba un programa que reciba un numero y calcule la suma de todos los primos menores que el numero ingresado.*/
int problema13();
/*Problema 15. Empezando con el numero 1 y moviendose hacia la izquierda y en sentido horario se genera una espiral de numeros como la siguiente:*/
int problema15();
/*Problema 17. La secuencia de los numeros triangulares se forma al sumar su posicion en el arreglo con el valor del numero anterior:1,1+2=3,3+3=6,6+4=10,10+5=15,15+6=21,21+7=28...Si listamos los numeros triangulares y sus divisores tenemos:*/
int problema17();

int main()
{
    problema17();
    return 0;
}

char problema1()
{
    char car;
    cout<< "Ingrese caracter: "<<endl;
    cin>> car;
    if ((car>= 'a' && car<= 'z' )||(car>= 'A' && car<= 'Z'))
    {
        if (car >= 'A' && car <= 'Z')
        {
            car = car + 32;
        }
        if(car == 'a'|| car == 'e'|| car == 'i'|| car == 'o'|| car == 'u' )
        {
            cout<< car << " es una vocal."<<endl;
        }
        else
        {
            cout<< car << " es una consonante."<<endl;
        }
    }
    else
    {
        cout<< car << " No es una letra."<< endl;
    }
    return 0;
}

int problema3()
{
    int m, d;
    int lista[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    cout<< "Ingrese dia: "<<endl;
    cin>> d;
    cout<<"Ingrese mes:"<<endl;
    cin>> m;
    if (m < 1|| m > 12)
    {
        cout << m << " es un mes invalido."<<endl;
        return 0;
    }
    if(d<1||d> lista[m-1])
    {
        if(m ==2 && d== 29)
        {
            cout<< d << "/"<< m << " es valida en bisiesto."<<endl;
        }
        else
        {
            cout<< d << "/"<< m << " es una fecha invalida."<<endl;
        }
    }
    else{
        cout<< d << "/"<< m << " es una fecha valida."<<endl;

    }
    return 0;
}

int problema5()
{
    int N;
    cout<<"Ingrese numero N entero impar: "<<endl;
    cin>>N;
    if (N % 2 ==0)
    {
        cout<< "El numero no es impar."<<endl;
        return 0;
    }
    int m = (N/2)+ 1;

    for(int i = 1;i<= m; i++)
    {
        for(int j= 0; j< m -i;j++)
        {
            cout<< " ";
        }
        for(int j = 0;j<2*i-1; j++)
        {
            cout <<"*";
        }
        cout<<endl;
    }

    for(int i= m-1; i>= 1; i--)
        {
            for(int j= 0; j<m - i; j++)
            {
                cout<<" ";
            }
            for(int j =0; j<2*i-1;j++)
            {
                cout<<"*";
            }
            cout<<endl;
    }
    return 0;
}

int problema7()
{
    int N, a= 1, b= 1, suma= 0, x;
    cout<<"Ingrese numero N:"<<endl;
    cin>>N;

    while(true)
    {
        x=a + b;
        if(x >= N) break;
        if(x % 2== 0)
        {
            suma += x;
        }
        a=b;
        b=x;
    }
    cout <<"El resultado de la suma es:"<< suma <<endl;
    return 0;
}

int problema9()
{
    int N, suma = 0;
    cout<< "Ingresa un numero N:"<<endl;
    cin>> N;
    while (N>0)
    {
        int d= N% 10;
        int p=1;
        for (int i= 0;i < d; i++)
        {
            p*=d;
        }
        suma += p;
        N /=10;
    }
    cout << "El resultado de la suma es: "<< suma <<endl;
    return 0;
}
int problema11()
{
    int N;
    cout <<"Ingresa un numero N: "<<endl;
    cin >>N;
    long long mcm = N;
    while(true)
    {
        bool esMCM= true;

        for(int i = 1; i<= N; i++)
        {
            if(mcm % i != 0)
            {
                esMCM=false;
                break;
            }
        }
        if (esMCM) break;
        mcm +=N;
    }
    cout<< "El minimo comun multiplo es: "<< mcm <<endl;
    return 0;
}

int problema13()
{
    int N, suma = 0;
    cout<<"Ingrese un numero N: "<<endl;
    cin>> N;
    for(int n= 2; n< N; n++)
    {
        bool primo=true;
        for(int i = 2;i * i<=n;i++)
        {
            if(n % i == 0)
            {
                primo=false;
                break;
            }
        }
        if(primo)
        {
            suma += n;
        }
    }
    cout <<"El resultado de la suma es: "<< suma <<endl;
    return 0;
}

int problema15()
{
    int N;
    cout <<"Ingrese el tamaño de la matriz: "<<endl;
    cin >> N;
    if (N% 2 ==0)
    {
        cout<<"El numero de tamaño de la matriz debe ser impar."<<endl;
        return 1;
    }
    int matriz[100][100]={0};

    int x= N / 2, y= N/ 2;
    int num = 1, paso = 1;
    int dx[]={0, 1, 0, -1};
    int dy[]={1, 0, -1, 0};
    int di= 0;

    matriz[x][y]= num++;

    while(num<=N*N)
    {
        for(int i=0; i<2; i++)
        {
            for(int j=0;j<paso && num <= N*N; j++)
            {
                x += dx[di];
                y += dy[di];
                matriz[x][y]= num++;
            }
            di=(di + 1)%4;
        }
        paso++;
    }


    for(int i= 0; i<N; i++)
    {
        for(int j= 0; j< N; j++)
        {
            cout<< matriz[i][j]<<"\t";
        }
        cout<<endl;
    }

    return 0;
}

int problema17()
{
    int k, n = 1, tri=1;
    cout<<"Ingrese un numero k: "<<endl;
    cin>> k;

    while(true)
    {
        int div = 0;
        for(int i = 1; i<= tri; i++)
        {
            if(tri % i == 0)
                div++;
        }
        if(div> k)
        {
            cout <<"El numero es:"<< tri <<" que tiene "<< div<< " divisores."<<endl;
            break;
        }
        n++;
        tri=n *(n+1)/ 2;
    }
return 0;
}
