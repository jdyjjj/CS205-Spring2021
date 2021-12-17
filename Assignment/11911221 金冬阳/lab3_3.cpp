#include <iostream>
using namespace std;
struct Brand{
    string name ;
    float weight;
    int calories;
};
int main() {
    Brand b[3];
    cout << "Please enter three CandyBar's information: "<<endl;
    //Brand b1;
    cout<<"Enter brand name of a Candy bar:";
    cin.get();
    getline(cin,b[0].name);

    cout<<"Enter weight of the Candy bar:";
    cin>>b[0].weight;
    cout<<"Enter calories(an integer value) of the Candy bar:";
    cin>>b[0].calories;

    cout<<"Enter brand name of a Candy bar:";
    cin.get();
    getline(cin,b[1].name);

    cout<<"Enter weight of the Candy bar:";
    cin>>b[1].weight;
    cout<<"Enter calories(an integer value) of the Candy bar:";
    cin>>b[1].calories;

    cout<<"Enter brand name of a Candy bar:";
    cin.get();
    getline(cin,b[2].name);
    cout<<"Enter weight of the Candy bar:";
    cin>>b[2].weight;
    cout<<"Enter calories(an integer value) of the Candy bar:";
    cin>>b[2].calories;
    for(int i=0;i<3;i++){
        cout << "Displaying the CandyBar array contents "<<endl;
        cout<<"Brand:"<<b[i].name<<endl;
        cout<<"Weight:"<<b[i].weight<<endl;
        cout<<"Calories:"<<b[i].calories<<endl;
    }

    cout<<"The greatest calories per weight is:"<<endl;

    if(b[0].weight>b[1].weight&&b[0].weight>b[2].weight){
        cout<<"Brand:"<<b[0].name<<endl;

    }
    if(b[1].weight>b[0].weight&&b[1].weight>b[2].weight){
        cout<<"Brand:"<<b[1].name<<endl;

    }
    if(b[2].weight>b[0].weight&&b[2].weight>b[1].weight){
        cout<<"Brand:"<<b[2].name<<endl;

    }
    float aver=(b[0].weight+b[1].weight+b[2].weight)/3;
    cout<<"Calories per weight:"<<aver<<endl;

}
