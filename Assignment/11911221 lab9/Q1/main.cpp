#include <iostream>
#include "golf.h"
#include <string>
#include <cstring>


using namespace std;

int main() {
    golf ann{};

    setgolf(ann, "Ann Birdfree", 24);
    showgolf(ann);
    cout << endl;

    golf andy;
    setgolf(andy);
    showgolf(andy);
    cout << endl;
    
 



    return 0;
}