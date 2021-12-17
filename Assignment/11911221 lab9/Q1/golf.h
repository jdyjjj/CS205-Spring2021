#ifndef EXC_CANDYBAR_H
#define EXC_CANDYBAR_H
#include <iostream>
const int Len = 40;
struct golf {
    char fullname[Len];
    int handicap;
};

void setgolf(golf &g,const char* name, int hc) ;

void setgolf(golf & g) ;

void handicap(const golf &g,int hc) ;

void showgolf(const golf& g) ;

#endif