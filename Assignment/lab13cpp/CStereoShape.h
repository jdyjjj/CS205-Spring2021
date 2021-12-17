#pragma once 
#include <iostream>
#include <math.h>

using namespace std;


class CStereoShape {
private:
    static int numberOfObject;
public:
    CStereoShape() {
        numberOfObject++;
    }

    virtual double GetArea();

    virtual double GetVolume();

    virtual void Show();

    static int GetNumOfObject() {
        return numberOfObject;
    }
};




