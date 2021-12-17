#include <iostream>

using namespace std;

template<typename T>
T max5(T temp[5]) {
    T max = temp[0];
    for (int i = 1; i < 5; ++i) {
        if (temp[i] > max) {
            max = temp[i];
        }
    }
    return max;
}


int main() {

    cout << "Max int = " << max5(new int[5]{1, 2, 3, 4, 5}) << endl;
    cout << "Max double = " << max5(new double[5]{1.1, 2.0, 3.0, 4.0, 5.5}) << endl;
    return 0;
}