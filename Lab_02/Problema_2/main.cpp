#include <iostream>

using namespace std;

int main()
{
    const int size = 200;
    char letras [size];

    for(int i = 0; i < size; ++i){
        letras [i]='A' +(i % 26);
    }

    cout<< "Arreglo generado:"<< endl;
    for(int i = 0; i< size; ++i){
        cout<< letras[i];
    }
    cout << endl;

    int contador[26] = {0};

    for (int i = 0; i < size; ++i) {
        contador[letras[i]-'A']++;
    }

    cout <<"\nFrecuencia de cada letra:"<< endl;
    for (int i = 0; i < 26; ++i){
        if(contador[i]>0){
            cout << char(i + 'A')<<":"<< contador[i]<< endl;
        }
    }
    return 0;
}
