#include <iostream>

using namespace std;

bool is_even(int n){
    return n % 2 == 0;
}

int maximum(int a, int b, int c){
    return max(a, max(b, c));
}

double celsius_to_fahrenheit(double c){
    return c * 9 / 5 + 32;
}

int clamp(int number, int min, int max){
    if (number < min) number = min;
    if (number > max) number = max;
    return number;
}

int main()
{
    cout << boolalpha;
    int n;
    cout << "Enter an integer: ";
    cin >> n;
    cout << "is_even(" << n << "): " << is_even(n) << "\n";

    int a, b, c;
    cout << "Enter three integers (a b c): ";
    cin >> a >> b >> c;
    cout << "maximum(" << a << ", " << b << ", " << c << "): " << maximum(a, b, c) << "\n";

    double celsius;
    cout << "Enter temperature in Celsius: ";
    cin >> celsius;
    cout << "celsius_to_fahrenheit(" << celsius << "): " << celsius_to_fahrenheit(celsius) << "\n";

    int number, min_value, max_value;
    cout << "Enter number, minimum, and maximum: ";
    cin >> number >> min_value >> max_value;
    cout << "clamp(" << number << ", " << min_value << ", " << max_value << "): " << clamp(number, min_value, max_value) << "\n";

    return 0;
}