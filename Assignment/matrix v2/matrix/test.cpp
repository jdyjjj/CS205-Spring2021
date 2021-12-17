#include <iostream>
#include "matrix.cpp"

using namespace std;

int main(void) {
    int arr0[]{10, 30, 50, 20};
    matrix<int> mat0(arr0, 2, 2);
    cout << mat0;

    int arr2[]{1, 2, 1, 3, 6, 3};
    matrix<int> mat2(arr2, 2, 3);
    cout << mat2;

    cout << mat0 * mat2;

    return 0;
}
