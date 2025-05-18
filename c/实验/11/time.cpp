#include<iostream>
#include "time.h"
using namespace std;
//+，-，++（后置），++（前置），<<,>>,>=或<=（用于减法时保证被减数大于等于减数）。
Time::Time() {
    hour=0;
    minute=0;
    second=0;
}
Time::Time(int h,int m,int s) {
    hour=h;
    minute=m;
    second=s;
}
Time Time::operator+(Time&t){    //+
    int h = hour + t.hour;
    int m = minute + t.minute;
    int s = second + t.second;
    if (s>=60) {
        s-=60;
        m++;
    }
    if (m>= 60) {
        m-= 60;
        h++;
    }
    return Time(h,m,s);
}
Time Time::operator-(Time& t){   //-
    int h = hour - t.hour;
    int m = minute - t.minute;
    int s = second - t.second;
    if (s < 0) {
        s += 60;
        m--;
    }
    if (m < 0) {
        m += 60;
        h--;
    }
    return Time(h, m, s);
}
Time Time::operator++(int) {    //后置++
    Time t(*this);
    second++;
    if (second>= 60) {
        second-= 60;
        minute++;
    }
    if (minute>= 60) {
        minute-= 60;
        hour++;
    }
    return t;
}
Time& Time::operator++() {		//前置++
    second++;
    if (second>= 60) {
        second-= 60;
        minute++;
    }
    if (minute>= 60) {
        minute-= 60;
        hour++;
    }
    return *this;
}
ostream&operator<<(ostream&output,Time&t) {   //<<
    output<< t.hour << ":" << t.minute << ":" << t.second;
    return output;
}
istream&operator>>(istream&input,Time&t) {    //>>
    input>>t.hour>>t.minute>>t.second;
    return input;
}
bool Time::operator>=(Time& t){
    if (hour > t.hour) {
        return true;
    } else if (hour == t.hour && minute > t.minute) {
        return true;
    } else if (hour == t.hour && minute == t.minute && second >= t.second) {
        return true;
    } else return false;
}
