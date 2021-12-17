#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>
#include "utf8.c"

using namespace std;
struct utf8_block {
    string name;
    int start;
    int end;
    int count = 0;
};

vector<utf8_block > read_utf8_blocks(const string& loadingway) ;

int main() {
    vector<utf8_block > array=read_utf8_blocks("Blocks.txt");
    string full;
    char input;
    while ((input = cin.get()) != char_traits<char>::eof()) {
        full += input;
    }

    unsigned char *u;
    int bytesWithchar;
    unsigned int num;

    u=(unsigned char*)full.data();
    while (*u) {
        num = utf8_to_codepoint(u, &bytesWithchar);
        if (num) {
            u += bytesWithchar;
            _utf8_incr(u);
        } else {
            u++;
        }
        for (int j = 0; j < array.size(); j++) {
            if (num >= array[j].start && num <= array[j].end) {
                array[j].count += 1;
                break;
            }
        }
    }
    utf8_block language = array[0];
    for (int j = 0; j < array.size(); j++) {
        if (language.count < array[j].count) {
            language = array[j];
        }
    }
    cout << language.name<<" matches.";
    return 0;
}

vector<utf8_block > read_utf8_blocks(const string& loadingway) {
    vector<utf8_block > array;
    array.clear();
    ifstream myfile(loadingway);
    if (myfile.fail()) {
        cout << "Input failed.";
        exit(1) ;
    }
    string line;
    int count = 0;
    int judge_if_cin = 0;
    while (getline(myfile, line)) {
        if (judge_if_cin < 34) {
            judge_if_cin += 1;
            continue;
        }
        if (line.empty()||line[0]=='#') {
            continue;
        }
        utf8_block temp;
        stringstream sin(line);
        string field;
        string whole;
        vector<string> token;
        getline(sin, field,'.');
        token.push_back(field);
        getline(sin, field,'.');
        getline(sin, field,';');
        token.push_back(field);
        getline(sin, field);
        token.push_back(field);
        temp.name=token[2];
        temp.start = stoi(token[0], nullptr, 16);
        temp.end = stoi(token[1], nullptr, 16);
        array.push_back(temp);
        count += 1;
    }
    myfile.close();
    return array;
}