#include"CCube.h"

    CCube::CCube() : length(0), width(0), height(0) {}

    CCube::CCube(double length, double width, double height): length(length), width(width), height(height) {}

    CCube::CCube(const CCube &temp) : length(temp.length), width(temp.width), height(temp.height) {}

    double CCube::GetArea() {
        return 2 * (length * width + length * height + width * height);
    }

    double CCube::GetVolume() {
        return length * width * height;
    }

    void CCube::Show() {
        cout << "Cube length: " << length 
             << "  width: " << width 
             << "  height: " << height << endl
             << "Cube area:" << GetArea() 
             << "  volume:" << GetVolume();
    }


