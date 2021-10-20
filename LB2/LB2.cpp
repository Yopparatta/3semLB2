#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Time {
public:
    Time(int h, int m, int s,int _ms) {
        hour = h;
        min = m;
        sec = s;
        ms = _ms;
    }
    Time() {}
    Time operator+(const Time& t) {
        Time res;
        res.ms = (t.ms + ms) % 1000;
        res.sec = (t.sec + sec) % 60 + ((t.ms + ms)/1000);
        res.min = (t.min + min) % 60 + ((t.sec + sec) / 60);
        res.hour = (t.hour + hour + ((t.min + min) /60))%24;
        return res;
    }
    Time operator-(const Time& t)
    {
        Time res;
        res.ms = (ms - t.ms) % 1000;
        res.sec = (sec - t.sec) % 60;
        res.min = (min- t.min)%60;
        res.hour = (hour - t.hour)%24;
        if (res.ms<0)
        {
            res.ms += 1000;
            res.sec -= 1;
        }
        if (res.sec<0)
        {
            res.sec += 60;
            res.min -= 1;
        }
        if (res.min < 0)
        {
            res.min += 60;
            res.hour -= 1;
        }
        if (res.hour < 0) res.hour += 24;
        return res;
    }
    int hour;
    int min;
    int sec;
    int ms;
};

Time operator+(const Time& t1, const Time& t2) {
    return { t1.hour + t2.hour, t1.min + t2.min, t1.sec+t2.sec, t1.ms + t2.ms };
}

ostream& operator<<(ostream& os, const Time& t) {
    os << t.hour << ":" << t.min << ":" << t.sec << ":" << t.ms;
    return os;
}

istream& operator>>(istream& is, Time& t)
{
    is >> t.hour;
    is >> t.min;
    is >> t.sec;
    is >> t.ms;
    return is;
}

ofstream& operator<<(ofstream& ofs, Time& t)
{
    ofs << t.hour << " " << t.min << " " << t.sec << " " << t.ms;
    return ofs;
}

ifstream& operator>>(ifstream& ifs, Time& t)
{
    ifs >> t.hour;
	ifs >> t.min;
    ifs >> t.sec;
    ifs >> t.ms;
    return ifs;
}

void main() {
    setlocale(LC_ALL, "Russian");
    Time time;
    Time testtime;
    Time time1 = { 8, 29,30,150 };
    Time time2 = { 10, 29,15,73 };
    Time time3 = time2 - time1;
    cout << "Введите время" << endl;
    cin >> time;
    cin >> testtime;
    cout << time + testtime << endl;
    //iostream
    cout << "iostream" << endl;
    cout << time3 << endl;
    cout << time << endl;

    //filestream
    ofstream of;
    of.open("outtext.txt");
    of << time;
    of.close();
    ifstream ifs;
    ifs.open("outtext.txt");
    ifs >> testtime;
    ifs.close();
    cout << "filestream " << testtime << endl;

    //stringstream
    stringstream ss;
    ss << time3+time2 << endl;
    cout << "stringstream " << ss.str();
}