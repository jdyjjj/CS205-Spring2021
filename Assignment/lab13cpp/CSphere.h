#define PI acos(-1)
#include"CStereoShape.h"
class CSphere : public CStereoShape {
public:
    double radius;

    CSphere() ;

    CSphere(double radius);

    CSphere(const CSphere &temp) ;

    double GetArea() override ;

    double GetVolume() override ;

    void Show() override ;

};
