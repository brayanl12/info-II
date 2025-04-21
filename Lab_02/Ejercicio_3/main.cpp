#include <iostream>

using namespace std;

int main()
{
    unsigned short b[4][2] = {
        {77, 50},
        {5, 2},
        {28, 39},
        {99, 3}};
}
/*1. La figura 1, que se presenta a continuacion, ilustra la representacion del arreglo b en memoria. Completa la numeracion de las direcciones de memoria, en notacion hexadecimal, para cada elemento del arreglo b.*/
/* Figura 1.
 *
 * b[0]=0x0A12
 * b[0][0]=0x0A12 y b[0][1]=0x0A14
 *
 *
 * b[1]=0x0A16
 * b[1][0]=0x0A16 y b[1][1]=0x0A18
 *
 *
 * b[2]=0x0A1A
 * b[2][0]=0x0A1A y b[2][1]=0x0A1C
 *
 *
 * b[3]=0x0A1E
 * b[3][0]=0x0A1E y b[3][1]=0x0A20
 */

/*Determinar, deacuerdo a lo ilustrado en la figura 1, el valor correspondiente de las siguites expresiones:
 *
 * 1.b
 * b[0]=0x0A12
 *
 * 2.b+2
 * b[2]=0x0A1A
 *
 * 3.*(b+2)
 * (b+2)=b[2]=0x0A1A
 * *(b+2)=b[2][0]=0x0A1A
 *
 *
 * 4.*(b+2)+1
 * (b+2)=b[2]=0x0A1A
 * *(b+2)=b[2][0]=0x0A1A
 * *(b+2)+1=b[2][1]=0x0A1C
 *
 * 5.*(*(b+2)+1)
 * (b+2)=b[2]=0x0A1A
 * *(b+2)=b[2][0]=0x0A1A
 * *(b+2)+1=b[2][1]=0x0A1C
 * (*(b+2)+1)=b[2][1]=39
 *
 * 6.b[3][1]
 * b[3][1]=3
 *
 * 7.*b++
 * No se puede, porque es un arreglo fijo, no un puntero modificable (Error)
 */

