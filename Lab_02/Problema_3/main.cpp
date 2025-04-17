#include <iostream>

using namespace std;

bool compararCadenas(const char* a, const char* b){
    for (int i = 0;;i++){
        if(a[i] != b[i]) return false;
        if(a[i] == '\0') return true;
    }
}

int main()
{
    char cadena1[100];
    char cadena2[100];

    cout <<"Ingrese la primera cadena: ";
    cin >> cadena1;

    cout <<"Ingrese la segunda cadena: ";
    cin >> cadena2;

    if(compararCadenas(cadena1, cadena2)){
        cout <<"Las cadenas son iguales."<< endl;
    }
    else{
        cout <<"Las cadenas son diferentes."<<endl;
    }

    return 0;
}
