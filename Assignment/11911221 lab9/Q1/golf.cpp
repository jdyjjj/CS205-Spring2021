#include <iostream>
#include <iomanip>
#include "golf.h"
#include <string>
#include <cstring>
using namespace std;

void setgolf(golf &g,const char* name, int hc){
    g.handicap=hc;
     strcpy(g.fullname, name);
}

void setgolf(golf & g) {
    cout << "Enter the name of golf: ";
    string s;
    getline(cin , s);
    if(s==""){
        int i;
        cout << "Enter handicap (an integer value) in the golf: ";
        cin>>i;
        cin.ignore();
        setgolf(g);
    }else{
    strcpy(g.fullname, s.c_str());
    cout << "Enter handicap (an integer value) in the golf: ";
    cin >> g.handicap;
    }
}

void handicap(golf &g,int hc){
    g.handicap=hc;
}

void showgolf(const golf& g){
  cout << "fullname: " << g.fullname << endl
         << "handicap: " << g.handicap << endl;
} 