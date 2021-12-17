#include"CStereoShape.h"
using namespace std;

int CStereoShape::numberOfObject = 0;

 double CStereoShape::GetArea() {return 0.0;}

 double CStereoShape::GetVolume() {return 0.0;}

  void CStereoShape::Show() {}




/*
class CCube : public CStereoShape {
public:
    double length;
    double width;
    double height;

    CCube() : length(0), width(0), height(0) {}

    CCube(double length, double width, double height): length(length), width(width), height(height) {}

    CCube(const CCube &temp) : length(temp.length), width(temp.width), height(temp.height) {}

    double GetArea() override {
        return 2 * (length * width + length * height + width * height);
    }

    double GetVolume() override {
        return length * width * height;
    }

    void Show() override {
        cout << "Cube length: " << length 
             << "  width: " << width 
             << "  height: " << height << endl
             << "Cube area:" << GetArea() 
             << "  volume:" << GetVolume();
    }

};

class CSphere : public CStereoShape {
public:
    double radius;

    CSphere() : radius(0) {}

    CSphere(double radius) : radius(radius) {}

    CSphere(const CSphere &temp) : radius(temp.radius) {}

    double GetArea() override {
        return 4 * radius * radius * PI;
    }

    double GetVolume() override {
        return 4.0 / 3.0 * PI * radius * radius * radius;
    }

    void Show() override {
        cout << "Sphere" 
             << " radius:" << radius 
             << " area:" << GetArea() 
             << " volume:" << GetVolume() << endl;
    }

};
*/