#include <iostream>
#include <string>
#include <cstring>
using namespace std;


class Rectangle {
private:
    double width;
    double height;
public:
    Rectangle() : width(1), height(1) {}

    Rectangle(double width, double height) : width(width), height(height) {}

    double getArea() {
        double area=width * height;
        return area;
    }

    double getPerimeter() {
        double perimeter=2 * width + 2 * height;
        return perimeter;
    }

    void display() {
        cout << "Width:     " << width << endl
             << "Height:    " << height << endl
             << "Area:      " << (int)this->getArea() << endl
             << "Perimeter: " << (int)this->getPerimeter() << endl;
    }
};

int main() {
    Rectangle r1(4, 40);
    Rectangle r2(3.5, 35.9);

    cout << "Rectangle1" << endl
         << "----------" << endl;
    r1.display();

    cout << "Rectangle2" << endl
         << "----------" << endl;
    r2.display();

    return 0;
}
