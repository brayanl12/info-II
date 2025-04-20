#include <iostream>
using namespace std;

int factorial(int n) {
    int f = 1;
    for (int i = 2; i <= n; i++) {
        f *= i;
    }
    return f;
}

void enesimaPermutacion(int n) {
    int nums[10];
    for (int i = 0; i < 10; i++) {
        nums[i] = i;
    }

    int original_n = n;
    n--;  // porque las permutaciones empiezan desde 0
    string resultado = "";

    for (int i = 10; i > 0; i--) {
        int fact = factorial(i - 1);
        int index = n / fact;
        resultado += to_string(nums[index]);

        for (int j = index; j < i - 1; j++) {
            nums[j] = nums[j + 1];
        }

        n %= fact;
    }

    cout << "La permutacion numero " << original_n << " es: " << resultado << endl;
}

int main() {
    int n;
    cout << "Ingrese el numero de la permutacion: ";
    cin >> n;

    enesimaPermutacion(n);

    return 0;
}
