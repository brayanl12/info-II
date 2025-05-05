#include <iostream>

using namespace std;

int main()
{
    const int ta = 100;
    char ori[ta];
    char text[ta];
    char num[ta];

    int t = 0;
    int n = 0;

    cout << "Ingrese cadena: ";
    cin >> ori;

    for (int i = 0; ori[i] != '\0'; i++)
    {
        char c = ori[i];
        if (c >= '0' && c <= '9')
        {
            num[++n] = c;
        }
        else{
            text[t++] = c;
        }
    }
    text[t] = '\0';
    num[n] = '\0';

    cout << "Original: " << ori <<endl;
    cout << "Texto: " << text << ", Numero: " << num << endl;

    return 0;
}
