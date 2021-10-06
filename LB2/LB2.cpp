#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Time {
public:
    Time(int h, int m) {
        hour = h;
        min = m;
    }
    Time() {}
    void Print() {
        cout << hour << ' ' << min;
    }
    Time operator+(const Time& t) {
        Time res;
        res.min = (t.min + min)%60;
        res.hour = (t.hour + hour + (res.min/60))%24;
        return res;
    }
    Time operator-(const Time& t)
    {
        Time res;
        res.min = (min- t.min)%60;
        res.hour = (hour - t.hour)%24;
        if (res.min < 0)
        {
            res.min += 60;
            hour -= 1;
        }
        if (res.hour < 0) res.hour += 24;
        return res;
    }
    int hour;
    int min;
};

Time operator+(const Time& t1, const Time& t2) {
    return { t1.hour + t2.hour, t1.min + t2.min };
}

ostream& operator<<(ostream& os, const Time& t) {
    os << t.hour << ":" << t.min;
    return os;
}

istream& operator>>(istream& is, Time& t)
{
    is >> t.hour;
    is >> t.min;
    return is;
}

ofstream& operator<<(ofstream& ofs, Time& t)
{
    ofs << t.hour << " " << t.min << endl;
    return ofs;
}

ifstream& operator>>(ifstream& ifs, Time& t)
{
    ifs >> t.hour;
	ifs >> t.min;
    return ifs;
}

void main() {
    setlocale(LC_ALL, "Russian");
    Time time;
    Time testtime;
    Time time1 = { 8, 29 };
    Time time2 = { 10, 29 };
    Time time3 = time2 - time1;
    cout << "Введите время" << endl;
    cin >> time;

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
    ss << time3 << endl;
    cout << "stringstream " << ss.str();
}