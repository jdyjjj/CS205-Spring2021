#include"CStereoShape.h"
class CCube : public CStereoShape {
public:
    double length;
    double width;
    double height;

    CCube() ;

    CCube(double length, double width, double height);

    CCube(const CCube &temp);

    double GetArea() override ;

    double GetVolume() override ;
    

    void Show() override ;
};