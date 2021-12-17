#include <iostream>
using namespace std;
void Fill_array(double arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "Enter value #" << i+1 << ": ";

        cin >> arr[i];
    }
}

void Show_Array(double *arr, int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void Reverse_array(double *arr, int size) {
    if (size <= 1) {
        return;
    }
    double tmp = arr[0];
    arr[0] = arr[size - 1];
    arr[size - 1] = tmp;
    Reverse_array(arr + 1, size - 2);
}

int main() {
    cout << "Enter the size of the array:";
    int size;
    cin >> size;
    double arr[size];
    Fill_array(arr, size);
    Show_Array(arr, size);

    Reverse_array(arr, size);
    Show_Array(arr, size);


    Reverse_array(arr + 1, size - 2);
    Show_Array(arr, size);
    return 0;
}