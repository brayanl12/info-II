#include <iostream>

using namespace std;

int main()
{
    const int t= 100;
    char ori[t];
    char sre[t];
    int k = 0;

    cout << "Ingrese una palabra: ";
    cin >> ori;

    for (int i = 0; ori[i] != '\0'; i++)
    {
        char actual = ori[i];
        bool ex = false;

        for(int j = 0; j < k; j++)
        {
            if (sre[j] == actual)
            {
                ex = true;
                break;
            }
        }
        if (!ex)
        {
            sre[k] = actual;
            k++;
        }
    }
    sre[k] = '\0';

    cout << "Original: " << ori <<endl;
    cout << "Sin repeticion: " << sre <<endl;

    return 0;
}
