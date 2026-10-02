#include <iostream>

using namespace std;

int main(){
    int skaicius = 0;
    cout << "iveskite skaiciu: ";
    cin >> skaicius;
    for (int i = 0; i <= skaicius; i++)
    {
        if(i % 3 == 0 && i % 5 == 0) cout << "FizzBuzz\n";
        else if (i % 5 == 0) cout << "Buzz\n";
        else if (i % 3 == 0) cout << "Fizz\n";
        else cout << i << endl;
    }

    return 0;
}