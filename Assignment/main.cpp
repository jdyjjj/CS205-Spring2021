#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

#define DATA_CSV_FILE "select_course.csv"
using namespace std;
struct Student {
    //string name;
    //char name[20];
    string name[20];
    string gender;
    int id;
    string college;
    string course[6];
};
void makeTXTFile(const vector<Student> &stdents);
vector<Student> readCSVFile(const string &filename);

int main() {
    vector<Student> students = readCSVFile(DATA_CSV_FILE);
    if (students.empty()) {
        cout << "world_cities.csv missing";
        return 0;
    }
    makeTXTFile(students);

    char str[20];
    cin>>str;

    return 0;
}
void makeTXTFile(const vector<Student> &stdents){
    ofstream myfile2;
    myfile2.open("f2.txt");
    if(myfile2.is_open()) {
        for (Student c: stdents) {
            myfile2 << c.name;
            myfile2 << ',';
            myfile2 << c.gender;
            myfile2 << ',';
            myfile2 << c.id;
            myfile2 << ',';
            myfile2 << c.college;
            myfile2 << ',';
            myfile2 << c.course[0];
            myfile2 << ',';
            myfile2 << c.course[1];
            myfile2 << ',';
            myfile2 << c.course[2];
            myfile2 << ',';
            myfile2 << c.course[3];
            myfile2 << ',';
            myfile2 << c.course[4];
            myfile2 << ',';
            myfile2 << c.course[5];
            myfile2 << endl;
        }
    }

    myfile2.close();
}



vector<Student> readCSVFile(const string &filename) {
    vector<Student> students;
    ifstream file(filename);
    if (!file.good()) {
        cout << "sorry, cannot open the file: " << filename << endl;
        return students;
    }
    int lineCnt = 1;
    string line;

    while (getline(file, line)) {
        string delimiter = ",";
        size_t pos = 0;
        int column = 0;
        string token[10];

        while ((pos = line.find(delimiter)) != string::npos) {
            token[column++] = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
        }
        token[column] = line;
        //char m[20] = token[0];
        string a;
        //cout<<token[0]<<endl;


        Student student = Student{};

        for(int i=0;i<token[0].size();i++){
            a = token[0].substr(i,1);
            cout<<a<<endl;
            student.name[i]=a;
        }
        //cout<<student.name[0]<<endl;
        //student.name = token[0];
        student.gender = token[1];
        student.college = token[2];
        student.id=stod(token[3]);
        student.course[0]= token[4];
        student.course[1] = token[5];
        student.course[2] = token[6];
        student.course[3] = token[7];
        student.course[4] = token[8];
        student.course[5] = token[9];

        students.push_back(student);

        lineCnt++;

    }

    return students;
}


