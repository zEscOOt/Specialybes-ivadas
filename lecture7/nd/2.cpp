#include <iostream>

using namespace std;

int factorial(int n){
    int answer = n;
    if (n > 1) answer *= factorial(n - 1);
    return answer;
}

unsigned long int fibonacci(int n){
    unsigned long int answer = 0;
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n > 1) return answer += fibonacci(n - 1) + fibonacci(n - 2);
    return answer;
}

int main(){
    cout << "factorial(5): " << factorial(5) << endl;
    cout << "factorial(0): " << factorial(1) << endl;
    cout << "fibonacci(7): " << fibonacci(7) << endl;
    cout << "fibonacci(0): " << fibonacci(0) << endl;
    return 0;
}