#include <iostream>
using namespace std;
int main() {
    char str[20];
    char str1[21];
    string name;
    string name1;
    char ch;
    int age;
    cout << "What is your first name? "<<endl;
    getline(cin,name);
    cout << "What is your last name? "<<endl;
    getline(cin,name1);
    cout << "What letter grade do you deserve? "<<endl;
    cin>>ch;
    cout<<"What is your age?"<<endl;
    cin>>age;
    cout<<"The information you entered is:"<<endl;
    cout<<"Name:"<<name<<","<<name1<<endl;
    cout<<"Grade:"<<ch<<endl;
    cout<<"Age:"<<age<<endl;

    return 0;
}
