#include<iostream>
using namespace std;
class Time {
public:
    Time(); 						// 无参构造函数
    Time(int h, int m, int s);	 	// 带三个参数的构造函数  
    
    Time operator+(Time&t); 			// 重载+运算符
    Time operator-(Time&t);				 // 重载-运算符
    Time operator++(int); 				// 重载后置++运算符
    Time&operator++(); 				// 重载前置++运算符
    friend ostream&operator<<(ostream&,Time&t); // 重载<<运算符
    friend istream&operator>>(istream&,Time&t); // 重载>>运算符
    bool operator>=(Time&t);
private:
    int hour; 	// 时
    int minute; // 分
    int second; // 秒
};

