#ifndef TV_H_
#define TV_H_
#include <iostream>
using namespace std;

class Tv
{
    public:
    friend class Remote; // Remote can access Tv private parts
    enum {Off, On};
    enum {MinVal,MaxVal = 20};
    enum {Antenna, Cable};
    enum {TV, DVD};
    
    Tv(int s = Off, int mc = 125) : state(s), volume(5),maxchannel(mc), channel(2), mode(Cable), input(TV) {}
    
    void onoff() {state = (state == On)? Off : On;}
    bool ison() const {return state == On;}
    bool volup();
    bool voldown();
    void chanup();
    void chandown();
    
    void set_mode() {mode = (mode == Antenna)? Cable : Antenna;}
    void set_input() {input = (input == TV)? DVD : TV;}
    void settings() const; // display all settings
    
    private:
    int state; // on or off
    int volume; // assumed to be digitized
    int maxchannel; // maximum number of channels
    int channel; // current channel setting
    int mode; // broadcast or cable
    int input; // TV or DVD
};

class Remote
{
    private:
    int mode; // controls TV or DVD
    int state = Normal;//normal or interactive
    public:
    enum {Normal,Interactive};
    Remote(int m = Tv::TV) : mode(m) {}
    void toggle(Tv& t) const;
    void ShowState() { std::cout << "the state of Remote is: " << (state==Normal?"Normal":"Interactive") << std::endl; }
    //void ShowState() { state = (state == Normal) ? Normal : Interactive; }
    bool volup(Tv & t) { return t.volup();}
    bool voldown(Tv & t) { return t.voldown();}
    void onoff(Tv & t) { t.onoff(); }
    void chanup(Tv & t) {t.chanup();}
    void chandown(Tv & t) {t.chandown();}

    void set_chan(Tv & t, int c) {t.channel = c;}//access the private member

    void set_mode(Tv & t) {t.set_mode();}
    void set_input(Tv & t) {t.set_input();}
};
#endif
