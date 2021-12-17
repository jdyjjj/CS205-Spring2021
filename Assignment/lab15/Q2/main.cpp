#include <iostream>
#include <exception>

using namespace std;

class OutOfRangeException : public exception {
public:
    string message;

    explicit OutOfRangeException(string message) : message(std::move(message)) {}
};

float  calculateAverage(int a,int b,int c,int d);

int main() {
    cout << "Please enter marks for 4 courses:";
    int a;
    int b;
    int c;
    int d;
    while (true) {
        try {
            cin>>a;
            cin>>b;
            cin>>c;
            cin>>d;
            float result=calculateAverage(a,b,c,d);
            cout << "The average of the four courses is " << result << endl;
        } catch (const OutOfRangeException &e) {
            cout << e.message << endl;
        }

        cout << "Would you want to enter another marks for 4 courses(y/n)?";
        char temp;
        cin>>temp;
        if(temp=='n'){
            cout << "Bye. See you next time. ";
            break;
        } else{
            cout << "Please enter marks for 4 courses:";
        }
    }
    return 0;
}

float  calculateAverage(int a,int b,int c,int d) {
    float sum = 0;
    for (int i = 1; i < 5; i++) {
        int it;
        if(i==1){
            it=a;
        } else if (i==2){
            it=b;
        } else if(i==3){
            it=c;
        } else{
            it=d;
        }
        if (it < 0 || it > 100) {
            throw OutOfRangeException(
                    "The parameter" + to_string(i) +
                      " is " + to_string(it) +
                      " which out of range(0-100)");
        }
        sum += it;
    }

    return sum/4;
}

