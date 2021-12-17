#include <cstring>
#include <iostream>
using namespace std;
struct stringy{
    char *str;
    int ct = 0;
};

void set(stringy &beany,char testing[]){
    beany.ct = strlen(testing);
    beany.str = new char[beany.ct + 1];
    strcpy(beany.str, testing);
}


void show(stringy &beany, int n = 1){
    for(int i=0;i<n;i++){
        cout<< beany.str <<endl;
    }
}


void show(const string &temp, int n = 1){
    for (int i = 0; i < n; i++){
        cout << temp << endl;
    }
}


int main()
{
    stringy beany;
    char testing[] = "Reality isn't what it used to be.";
    set(beany,testing);

    show(beany);
    show(beany,2);

    testing[0]='D';
    testing[1]='u';
    show(testing);
    show(testing,3);
    show("Done!");
    delete[] beany.str;
    return 0;

}