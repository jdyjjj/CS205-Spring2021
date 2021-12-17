#include <iostream>

void displaymenu();

using namespace std;
int Add(int a,int b){
    int c=a+b;
    return c;
}
int Substract(int a,int b){
    int c=a-b;
    return c;
}
int Multiply(int a,int b){
    int c=a*b;
    return c;
}
int Divide(int a,int b){
    int c=a/b;
    return c;
}

int Modulus(int a,int b){
    int c=a%b;
    return c;
}

void displaymenu() {
    cout << "=====================================" << endl
         << "                MENU              " << endl
         << "=====================================" << endl
         << "   1.Add" << endl
         << "   2.Subtract" << endl
         << "   3.Multiply" << endl
         << "   4.Divide" << endl
         << "   5.Modulus" << endl;
}

int main(int argc, char *argv[]) {
    //show menu
    displaymenu();
    int yourchoice;
    int a;
    int b;
    char confirm;
    {
        cout << "Enter your choice(1-5):";
        cin >> yourchoice;
        cout << "Enter your two integer numbers:";
        cin >> a >> b;
        cout << "\n";
        switch (yourchoice) {
            case 1:
                cout << "Result: " << Add(a,b) << endl;
                break;
            case 2:
                cout << "Result: " << Substract(a,b) << endl;
                break;
            case 3:
                cout << "Result: " << Multiply(a,b) << endl;
                break;
            case 4:
                cout << "Result: " << Divide(a,b) << endl;
                break;
            case 5:
                cout << "Result: " << Modulus(a,b) << endl;
                break;
        }
        cout << "\nPress y or Y to continue:";
        cin >> confirm;
    }
    while (confirm == 'y' || confirm == 'Y'){
        confirm='a';
        displaymenu();
        cout << "Enter your choice(1-5):";
        cin >> yourchoice;
        cout << "Enter your two integer numbers:";
        cin >> a >> b;
        cout << "\n";
        switch (yourchoice) {
            case 1:
                cout << "Result: " << Add(a,b) << endl;
                break;
            case 2:
                cout << "Result: " << Substract(a,b) << endl;
                break;
            case 3:
                cout << "Result: " << Multiply(a,b) << endl;
                break;
            case 4:
                cout << "Result: " << Divide(a,b) << endl;
                break;
            case 5:
                cout << "Result: " << Modulus(a,b) << endl;
                break;
        }
        cout << "\nPress y or Y to continue:";
        cin >> confirm;
    };
    return 0;
}