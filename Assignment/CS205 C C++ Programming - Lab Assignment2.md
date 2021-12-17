# CS205 C/ C++ Programming - Lab Assignment2

**Name**:金冬阳（Jin Dongyang）

**SID**:11911221

## Part 1 - Analysis

环境：

```
gcc.exe (MinGW.org GCC Build-20200227-1) 9.2.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO 
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

操作系统：Windows10 (家庭中文版64位)

CPU：Intel Core i5-9300H

内存：8G

Think about how to read and write the CSV file, and think about how to deal with the read data.

## Part 2 - Code

```c++
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>

#define MAX_NAME_LENGTH 35
#define MAX_ARRAY_SIZE 1000
#define CSV_FILE "world_cities.csv"
using namespace std;
struct City {
    string name;
    string province;
    string country;
    double latitude;
    double longitude;
};

vector< City > toSelect;
void readCSVFile(const string &filename);
void EraseSpace(string &s);
City readCity();
double calcDistance(const City &c1, const City &c2);
vector<City> g_cities;
bool judgec=true;
bool huanhang=false;
City c1;
City c2;


int main() {
    readCSVFile(CSV_FILE);
    if (g_cities.empty()) {//Check whether the read file is complete
        cout << "world_cities.csv missing";
        return 0;
    }

    while (true) {
        while (judgec) {
            cout << "please input the first city name: ";
            if(huanhang) {
                cin.ignore();//Solve the question of cin and getline
            }
            huanhang= false;
            c1=readCity();//the first city
        }
        judgec=true;
        while (judgec) {
            cout << "please input the second city name: ";
            if(huanhang) {//Solve the question of cin and getline
                cin.ignore();
            }
            huanhang= false;
            c2=readCity();//the second city
        }
        judgec=true;
        double distance = calcDistance(c1, c2);
        cout << "The distance between " << c1.name << " and " << c2.name
             << " is " << distance << "km." << endl;
        cout<< "Do you want to exit the program?"<<endl<<"(If you want, please input 'bye'. Otherwise, if you enter something else, the loop will continue):";
        string s;
        cin>>s;// if s is bye, exit
        transform(s.begin(), s.end(), s.begin(), ::toupper);//to solve the problem of uppercase and lowercase
        if(s=="BYE"){
            return 0;
        }else{
            huanhang=true;
        }

    }
}

void EraseSpace(string &s){//Solve the problem of space before and after
    const char ch = ' ';
    s.erase(s.find_last_not_of(" ") + 1);
    s.erase(0, s.find_first_not_of(" "));
}


City readCity( ) {
    City c;
    string s;
    getline(cin, s);

    EraseSpace(s);
    transform(s.begin(), s.end(), s.begin(), ::toupper);//to solve the problem of uppercase and lowercase


    if (s.size() < 3) {
        cout << "city's name need longer" << endl;
        return c;
    }

    toSelect.clear();
    for (int i=0;i<g_cities.size();i++) {
        City city = g_cities[i];
        if (city.name.find(s, 0) == 0) {
            if (toSelect.size() == 1) {
                cout << "there exist multiple cities, you can input number as city name" << endl;
                cout << "0. " << toSelect[0].name << ", " << toSelect[0].country << endl;
                cout << "1. " << city.name << ", " << city.country << endl;
            } else if (toSelect.size() > 1) {
                cout << toSelect.size() << ". " << city.name << ", " << city.country << endl;
            }
            toSelect.push_back(city);
            c=city;

        }
    }

    if (toSelect.size() >= 2) {
        huanhang=true;
        cout<<"Please input a number to choose a city:";
        string numberOFchoose;
        cin >> numberOFchoose;
        bool whenTObreak= false;
        while (true) {
            whenTObreak= false;
            for (char const &c: numberOFchoose) {//Check if the input type is int
                if (isdigit(c)) {

                } else {
                    cout << "Input type error, must be a number. please input a number:";
                    whenTObreak= true;
                    break;
                }
            }
            if(whenTObreak) {
                cin >> numberOFchoose;
            } else{
                break;
            }
        }
        int number= stoi( numberOFchoose );

        while(number>=toSelect.size() ){
            cout<<"sorry, your input is too large, please input a smaller number:";
            cin>>number;
        }
        judgec= false;

        return toSelect[number];
    }

    if (toSelect.empty()) {
        cout << "NO city can be found" << endl;
        return c;
    }

    judgec= false;
    return c;

}

void readCSVFile(const string &filename) {


    ifstream file(filename);
    if (!file.good()) {
        cout << "sorry, can not open the file: " << filename <<  endl;
        return ;
    }

    int lineCount = 1;
    string line_csv;

    while (getline(file, line_csv)) {

        if (g_cities.size() == MAX_ARRAY_SIZE) {
            cout << "sorry, the file is larger than " << MAX_ARRAY_SIZE << " lines, skip the remaining lines" << endl;
            //If the file size exceeds the maximum size, the data in this line is ignored.
            break;
        }

        string delimiter = ",";
        size_t pos = 0;
        int col = 0;
        string temp[5];

        while ((pos = line_csv.find(delimiter)) != string::npos) {
            temp[col++] = line_csv.substr(0, pos);
            line_csv.erase(0, pos + delimiter.length());
        }
        temp[col] = line_csv;


        if (temp[0].size() >= MAX_NAME_LENGTH || temp[2].size() >= MAX_NAME_LENGTH) {
            //If the maximum length is exceeded, the data in this row is ignored
            cout <<"sorry, the No."<< lineCount << " is too long, cannot load the name into char array with size " << MAX_NAME_LENGTH
                 << ", skip this line" << endl;
        } else {

            transform(temp[0].begin(), temp[0].end(), temp[0].begin(), ::toupper);

            City city = City{};

            city.name = temp[0];
            if (temp[1].size() < MAX_NAME_LENGTH) {
                city.province = temp[1];
            }
            city.country = temp[2];
            city.latitude = stod(temp[3]);
            city.longitude = stod(temp[4]);

            g_cities.push_back(city);
        }
        lineCount++;


    }

    return ;
}


double calcDistance(const City &city1, const City &city2) {
    double latitudeOffirst  = city1.latitude;
    double longitudeOffirst = city1.longitude;
    double phiOffirst = (90 - latitudeOffirst )/ 180.0 * 3.1415926536;
    double thetaOffirst = (longitudeOffirst)/ 180.0 * 3.1415926536;
    double latitudeOfsecond = city2.latitude;
    double longitudeOfsecond = city2.longitude;
    double phiOfsecond = (90 - latitudeOfsecond)/ 180.0 * 3.1415926536;;
    double thetaOfsecond = (longitudeOfsecond)/ 180.0 * 3.1415926536;;

    double c = sin(phiOffirst) * sin(phiOfsecond) * cos(thetaOffirst - thetaOfsecond) + cos(phiOffirst) * cos(phiOfsecond);

    double result = 6371.0 * acos(c);
    return result;
}

```

## Part 3 - Result & Verification

#### Test case #1:

##### input:

```
new y
beij
bye
```

##### output:

```
please input the first city name: new y
please input the second city name: beij
The distance between NEW YORK CITY and BEIJING is 10995.5km.
Do you want to exit the program?
(If you want, please input 'bye'. Otherwise, if you enter something else, the loop will continue):bye
```



#### Test case #2:

##### input:

```
new
0
   new
2
no
1
jin
BYE
```

##### output:

```
please input the first city name: new
there exist multiple cities, you can input number as city name
0. NEW DELHI, India
1. NEW ORLEANS, United States
2. NEW YORK CITY, United States
3. NEWCASTLE UPON TYNE, United Kingdom
4. NEWCASTLE, Australia
Please input a number to choose a city:0
please input the second city name:   new
there exist multiple cities, you can input number as city name
0. NEW DELHI, India
1. NEW ORLEANS, United States
2. NEW YORK CITY, United States
3. NEWCASTLE UPON TYNE, United Kingdom
4. NEWCASTLE, Australia
Please input a number to choose a city:2
The distance between NEW DELHI and NEW YORK CITY is 11756.6km.
Do you want to exit the program?
(If you want, please input 'bye'. Otherwise, if you enter something else, the loop will continue):no
please input the first city name: bei
there exist multiple cities, you can input number as city name
0. BEIJING, China
1. BEIRUT, Lebanon
Please input a number to choose a city:1
please input the second city name: jin
The distance between BEIRUT and JINAN is 7163.43km.
Do you want to exit the program?
(If you want, please input 'bye'. Otherwise, if you enter something else, the loop will continue):BYE
```



#### Test case #3:

##### input:

```
ne
new
s
1
gogo
go
qing
bye
```

##### output:

```
please input the first city name: ne
city's name need longer
please input the first city name: new
there exist multiple cities, you can input number as city name
0. NEW DELHI, India
1. NEW ORLEANS, United States
2. NEW YORK CITY, United States
3. NEWCASTLE UPON TYNE, United Kingdom
4. NEWCASTLE, Australia
Please input a number to choose a city:s
Input type error, must be a number. please input a number:1
please input the second city name: gogo
NO city can be found
please input the second city name: go
city's name need longer
please input the second city name: qing
The distance between NEW ORLEANS and QINGDAO is 12013.7km.
Do you want to exit the program?
(If you want, please input 'bye'. Otherwise, if you enter something else, the loop will continue):bye
```

#### Test case #4:

##### input:

```
     jin
new
s
6
5
4
no
bei
0
bei
0
bye
```

##### output:

```
please input the first city name:     jin
please input the second city name: new
there exist multiple cities, you can input number as city name
0. NEW DELHI, India
1. NEW ORLEANS, United States
2. NEW YORK CITY, United States
3. NEWCASTLE UPON TYNE, United Kingdom
4. NEWCASTLE, Australia
Please input a number to choose a city:s
Input type error, must be a number. please input a number:6
sorry, your input is too large, please input a smaller number:5
sorry, your input is too large, please input a smaller number:4
The distance between JINAN and NEWCASTLE is 8537.97km.
Do you want to exit the program?
(If you want, please input 'bye'. Otherwise, if you enter something else, the loop will continue):no
please input the first city name: bei
there exist multiple cities, you can input number as city name
0. BEIJING, China
1. BEIRUT, Lebanon
Please input a number to choose a city:0
please input the second city name: bei
there exist multiple cities, you can input number as city name
0. BEIJING, China
1. BEIRUT, Lebanon
Please input a number to choose a city:0
The distance between BEIJING and BEIJING is 0km.
Do you want to exit the program?
(If you want, please input 'bye'. Otherwise, if you enter something else, the loop will continue):bye
```

## Part 4 - Difficulties & Solutions

At first, I couldn't read and write CSV files, but later I found a solution through the Internet.

The pointer problem also bothered me for a long time, and later it was solved through the network.

In the beginning, I read the space before and after the string one by one. Later, I found that I could use the function method to deal with it directly.

cin.ignore( ) is very important for this homework. 



