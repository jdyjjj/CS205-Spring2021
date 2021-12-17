#include <iostream>

using namespace std;
int input(const string& n);
int readNum(int a);
int readDirection();
int main() {
    int n,m,k;
    n= input("n");
    m= input("m");
    k= input("k");

    if(k==0){
        cout<<"there are no bullets on the screen."<<endl;
        cout<<n*m;
        return 0;
    }

    int **array;
    array= new int *[n];
    for(int i=0;i<n;i++){
        array[i]=new int [m];
    }

    for (int i = 0; i < k; i++) {
        int x, y, direction_x, direction_y;
        x=readNum(n);
        y=readNum(m);
        direction_x=readDirection();
        direction_y=readDirection();

        while ((x >= 0 && x < n) && (y >= 0 && y < m)) {
            array[x][y] = 1;
            x += direction_x;
            y += direction_y;
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(array[i][j]!=1){
                count++;
            }
        }
    }

    cout << count;

    return 0;

}

int input(const string& n){
    int num;
    cin>>num;
    if(cin.fail()){
        cout<<n<<": type error, must be an integer "<<endl;
        exit(1);
    } else if(num<=0&&n!="k"){//m,n must be a positive integer!
        cout<<n<<": number error, must be a positive integer"<<endl;
        exit(1);
    } else if(num<0&&n=="k") {//k may be 0
        cout<<n<<": number error, must be a positive integer"<<endl;
        exit(1);
    }
    return num;
}

int readNum(int a){
    int num;
    cin>>num;
    if(cin.fail()) {
        cout << "bullet: type error, must be an integer " << endl;
        exit(1);
    } else if(num < 0 || num >= a){
        cout << "bullet missing, bullet must be in screen!" << endl;
    }
    return num;
}
int readDirection(){
    int num;
    cin>>num;
    if(cin.fail()) {
        cout << "direction: type error, must be an integer " << endl;
        exit(1);
    } else if(abs(num) > 1){
        cout << "direction error, exit" << endl;
    }
    return num;
}