#include <iostream>

using namespace std;

int main(){
    int suma = 0, skaicius = 0;
    cout << "iveskite skaiciu: ";
    cin >> skaicius;
    for(int i = 0; i <= skaicius; i++){
        suma += i;
    }

    cout << suma;

    return 0;
}