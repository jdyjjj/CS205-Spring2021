// stock02.h -- augmented version
#ifndef STOCK20_H_
#define STOCK20_H_
#include <string>
#include <cstring>
class Stock
{
    public:
    char* name;
    std::string company;
    int shares;
    double share_val;
    double total_val;

    void set_tot() { total_val = shares * share_val; }
    
    public:
    Stock(); // default constructor
    Stock(const char* cstr = 0, long n = 0, double pr = 0.0);
    //Stock(const std::string & co, long n = 0, double pr = 0.0);
    ~Stock(); // do-nothing destructor


    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show()const;
    const Stock & topval(const Stock & s) const;

    friend std::ostream & operator <<(std::ostream & out, const Stock & other);
};
#endif