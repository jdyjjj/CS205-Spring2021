#include <iostream>
#include <iomanip>
#include "fun.h"
#include <string>
#include <cstring>
using namespace std;
void setCandyBar(CandyBar &cb) {
    cout << "Enter brand name of a Candy bar: ";
    //cin >> cb.brand;
    cin.ignore();
    string s;
    getline(cin , s);
    strcpy(cb.brand, s.c_str());

    cout << "Enter weight of the candy bar: ";
    cin >> cb.weight;
    cout << "Enter calories (an integer value) in the candy bar: ";
    cin >> cb.calorie;
}

void setCandyBar(CandyBar * cb) {
    setCandyBar(*cb);
}

void showCandyBar(const CandyBar &cb) {
    cout << "Brand: " << cb.brand << endl
         << "Weight: " << cb.weight << endl
         << "Calories: " << cb.calorie << endl;
}

void showCandyBar(const CandyBar *cb) {
    showCandyBar(*cb);
}