#include <iostream>
#include"CCube.h"
#include"CStereoShape.h"
#include"CSphere.h"
using namespace std;

int main() {
    CCube cube(4.0, 5.0, 6.0);
    CSphere sphere(7.9);
    CStereoShape *c;
    c = &cube;
    c->Show();
    cout << endl;
    c = &sphere;
    c->Show();
    //cout << CStereoShape::GetNumOfObject() <<"objects are created"<< endl;

    return 0;
}