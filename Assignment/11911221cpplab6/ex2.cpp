#include <iostream>
#include <cstring>

using namespace std;

struct box {
    char maker[40];
    //string maker;
    float height;
    float width;
    float length;
    float volume;
};

box setBox(const char *m , float w, float h, float l, box b){
    strcpy(b.maker, m);
    //b.maker =  m;
    b.width = w;
    b.height = h;
    b.length = l;
    return b;

}

void setVolume(box *b) {
    b->volume = b->width * b->height * b->length;
}

void printBox(const box b) {
    cout << "maker: " << b.maker << endl
         << "width: " << b.width << endl
         << "height: " << b.height << endl
         << "length: " << b.length << endl
         << "volume: " << b.volume << endl;
}

int main() {
    box b{};
    char m[]="Jack Smith";
    float w=4.5;
    float h=3.4;
    float l=5.6;
    b=setBox(m,w,h,l,b);
    cout << "Before setting volume:" << endl;
    printBox(b);

    setVolume(&b);
    cout << "After setting volume:" << endl;
    printBox(b);
    return 0;
}