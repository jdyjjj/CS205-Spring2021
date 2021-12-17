#include"CSphere.h"

    CSphere::CSphere() : radius(0) {}

    CSphere::CSphere(double radius) : radius(radius) {}

    CSphere::CSphere(const CSphere &temp) : radius(temp.radius) {}

    double CSphere::GetArea()  {
        return 4 * radius * radius * PI;
    }

    double CSphere::GetVolume(){
        return 4.0 / 3.0 * PI * radius * radius * radius;
    }

    void CSphere::Show()  {
        cout << "Sphere" 
             << " radius:" << radius 
             << " area:" << GetArea() 
             << " volume:" << GetVolume() << endl;
    }


