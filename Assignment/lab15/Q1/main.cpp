#include <iostream>
#include "tv.h"
using namespace std;

int main()
{
    using std::cout;
    Tv s42;
    Remote r;
    cout << "Initial settings for 42\" TV:\n";
    s42.settings();
    // s42.onoff();
    r.ShowState();
    r.toggle(s42);
    s42.chanup();
    cout << "\nAdjusted settings for 42\" TV:\n";
    s42.onoff();
    s42.settings();
    r.toggle(s42);  
    return 0;
}
