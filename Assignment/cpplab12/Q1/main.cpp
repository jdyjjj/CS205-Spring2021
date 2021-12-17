// usestok02.cpp -- using the Stock class
// compile with stock02.cpp
#include <iostream>
#include <cstring>
#include "stock02.h"
using namespace std;
const int STKS = 4;
int main()
{
    // create an array of initialized objects
    char name1[] = "NanoSmart";
    char* name11 = new char[strlen(name1) + 1]();
    strcpy(name11, name1);

    char name2[] = "Boffo Objects";
    char* name22 = new char[strlen(name2) + 1]();
    strcpy(name22, name2);

    char name3[] = "Monolithic Obelisks";
    char* name33 = new char[strlen(name3) + 1]();
    strcpy(name33, name3);

    char name4[] = "Fleep Enterprises";
    char* name44 = new char[strlen(name4) + 1]();
    strcpy(name44, name4);

    Stock stocks[STKS] =
    {
        Stock(name11, 12, 20.0),
        Stock(name22, 200, 2.0),
        Stock(name33, 130, 3.25),
        Stock(name44, 60, 6.5)
    };
    
    std::cout << "Stock holdings:\n";
    int st;
    for (st = 0; st < STKS; st++)
    {
        std::cout << stocks[st];
        //stocks[st].show();
    }
    
    // set pointer to first element
    const Stock * top = &stocks[0];
    // for (st = 1; st < STKS; st++)
    //     top = &top->topval(stocks[st]);// & access the address
    
    // // now top points to the most valuable holding
    // std::cout << "\nMost valuable holding:\n";
    // top->show();
    
    return 0;
}