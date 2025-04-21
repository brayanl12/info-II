#include <iostream>
using namespace std;
void fun_a(int *px, int *py); void
fun_b(int a[], int tam);
int main()
{
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    fun_b(array, 10);
}
void fun_a(int *px,int*py){ int
        tmp = *px;
    *px = *py;
    *py = tmp;
}
void fun_b(int a[], int tam){
    int f, l;
    int *b = a;
    for (f = 0, l = tam -1; f < l; f++, l--) {
        fun_a(&b[f], &b[l]);
    }
}
/*1.Con ayuda del debugger,examina la representacion en memoria del arreglo array y responde las siguientes preguntas.*/

/*a)La direccion en memoria es (@0xa219ffb10) y cada array como es un int ocupa 4 bytes en memoria*/

/*b)La direccion en memoria y el contenido en memoria del elemento array [3] se encuentra en (@0xa219ffb1c)
A = 10

B = 11

C = 12

D = 13

E = 14

F = 15
*/

/*c)El efecto que tiene la fun_b sobre el arreglo array es el de invertir el contenido del arreglo.Lo hace mediante un ciclo que recorre el arreglo desde ambos extremos hacia el centro intercambiando los elementos de posicion opuesta usando la funcion fun_a.*/
