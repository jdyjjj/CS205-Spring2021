#ifndef EXC_CANDYBAR_H
#define EXC_CANDYBAR_H

#include <iostream>

const int Len = 30;
struct CandyBar {
    char brand[Len];
    double weight;
    int calorie;
};

void setCandyBar(CandyBar &cb) ;

void setCandyBar(CandyBar * cb) ;

void showCandyBar(const CandyBar &cb) ;

void showCandyBar(const CandyBar *cb) ;

#endif
