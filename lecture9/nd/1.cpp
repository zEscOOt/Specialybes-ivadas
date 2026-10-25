#include <iostream>

using namespace std;

int sum(int a[], int n);
int count_value(int a[], int n, int value);
bool is_sorted(int a[], int n);
void reverse(int a[], int n);

int main(){
    int data[6] = {4, 9, 2, 9, 1, 6};
    cout << "sum: " << sum(data, 6) << endl;
    cout << "count_value(9): " << count_value(data, 6, 9) << endl;
    cout << "is_sorted: " << boolalpha << is_sorted(data, 6) << endl;
    cout << "Reverse: ";
    reverse(data, 6);
    for(int i : data){
        cout << i << " ";
    }
    cout << endl;
}

int sum(int a[], int n){
    int sum = 0;
    for(size_t i = 0; i < n; ++i){
        sum += a[i];
    }
    return sum;
}

int count_value(int a[], int n, int value){
    int count = 0;
    for (size_t i = 0; i < n; ++i)
    {
        if(a[i] == value) count++;
    }
    return count;
}

bool is_sorted(int a[], int n){
    bool sorted = true;
    for (size_t i = 0; i < n - 1; ++i)
    {
        if(a[i] > a[i+1]){
            sorted = false;
            break;
        } 
    }
    return sorted;
}

void reverse(int a[], int n){
    for(size_t i = 0; i < n/2; i++){
        int swap = a[n-i-1];
        a[n-i-1] = a[i];
        a[i] = swap;
    }
}