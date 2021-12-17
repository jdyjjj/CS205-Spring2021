#include <iostream>
#include "sale.h"
#include <string>
#include <cstring>
using namespace SALES;

using namespace std;

int main() {
    Sales s{};
    cout<<"Non-interactive version of setSales() to provide values:"<<endl;
    double ar[]={345.2,621.8,1073.5};
    setSales(s, ar, 3);
    showSales(s);
    cout<<"Interactive version of setSales() to provide values:"<<endl;
    Sales s1{};
    setSales(s1);
    showSales(s1);



    return 0;
}