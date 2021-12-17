#include <iostream>
#include <iomanip>

using namespace std;
void change(int &x, int &y);
int readNum();
int calculate_length(int nm);

int main() {
    int n, m;
    n=readNum();
    m=readNum();
    int length = calculate_length(n*m);//in order to fill in the space when aligning left

    int **array;
    array= new int *[n];
    for(int i=0;i<n;i++){
        array[i]=new int [m];
    }
    for(int j=0;j<n;j++) {
        for (int i = 0; i < m; i++) {
            array[j][i] = 0;
        }
    }


    int x = m, y = 0;
    int direction_x = -1, direction_y = 0;

    for (int i = 1; i <= n * m; i++) {
        x += direction_x, y += direction_y;
        array[y][x] = i;

        int nx = x + direction_x;
        int ny = y + direction_y;
        if (nx < 0 || nx >= m || ny < 0 || ny >= n || array[ny][nx] != 0) {
            change(direction_x, direction_y);
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<setiosflags(ios::left) << setw(length) << setfill(' ') << array[i][j] << " ";//align left, fill in space
        }
        cout<<endl;
    }

    return 0;

}
void change(int &x, int &y) {
    if (x == -1) {
        x = 0;
        y = 1;
    } else if (y == 1) {
        y = 0;
        x = 1;
    } else if (x == 1) {
        x = 0;
        y = -1;
    } else {
        y = 0;
        x = -1;
    }
}

int readNum() {
    int num;
    cin>>num;
    if (cin.fail() || num < 1 ) {
        cout << "error input, exit" << endl;
        exit(1);
    }

    return num;

}
int calculate_length(int nm) {
    int length=1;
    while(nm/10>0){
        length++;
        nm=nm/10;
    }

    return length;

}
