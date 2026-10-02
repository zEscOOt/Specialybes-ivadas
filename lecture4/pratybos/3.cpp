#include <iostream>

using namespace std;

int main()
{
    cout << "Pirminiai nuo 1 iki 100: \n";
    bool isPrime = true;

    for (int i = 2; i <= 100; i++){
        isPrime = true;
        for (size_t j = 2; j*j <= i; j++)
        {
            if(i % j == 0){
                isPrime = false;
                break;
            }
        }

        if (isPrime)
            cout << i << endl;
        
    }
    return 0;
}