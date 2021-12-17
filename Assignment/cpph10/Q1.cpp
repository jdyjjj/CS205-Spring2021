#include <iostream>
#include <string>
using namespace std;

class CandyBar {
private:
    string name;
    double weight;
    int calories;
public:
    void setCandyBar() {
        cout << "Enter the name of the candy bar: ";
        //cin.ignore();
        string s;
        getline(cin , name);
        cout << "Enter weight of the candy bar: ";
        cin >> weight;
        cout << "Enter calories (an integer value) in the candy bar: ";
        cin >> calories;
    }

    void showCandyBar() {
        cout << "Brand: " << name << endl
             << "Weight: " << weight << endl
             << "Calorie: " << calories << endl;
    }
};


int main() {
    CandyBar candybar{};
    candybar.setCandyBar();
    candybar.showCandyBar();
    return 0;
}
