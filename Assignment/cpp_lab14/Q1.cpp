#include <iostream>
#include <string>

using namespace std;

template<typename T>
T Max(T one, T two);

int main() {
    int i_one = 3, i_two = 5;
    cout << "The max of " << i_one << " and " << i_two << " is "
         << Max(i_one, i_two) << endl;
    double d_one = 3.5, d_two = 10.3;
    cout << "The max of " << d_one << " and " << d_two << " is "
         << Max(d_one, d_two) << endl;
    string s_one = "Hello", s_two = "World";
    cout << "The max of " << s_one << " and " << s_two << " is "
         << Max(s_one, s_two) << endl;
    //Test your template on float and string types
    return 0;
}

//Make a template out of this function. Don't forget the return type.
template<typename T>
T Max(T one, T two) {
    T biggest;
    if (one < two) {
        biggest = two;
    }
    else {
        biggest = one;
    }
    return biggest;
}