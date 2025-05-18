#include<iostream>
#include "person.h"
using namespace std;
void person::out1(){
	cout<<"姓名："<<name<<"   性别："<<sex<<"   年龄："<<age<<endl;
};
void teacher::out2(){
	person::out1();
	cout<<"工资："<<money<<"  职称："<<title<<endl;
}
void student::out3(){
	person::out1();
	cout<<"学号："<<number<<"  专业："<<major<<"  成绩:"<<score<<endl;
}
void graduate::out4(){
	teacher::out2();
	cout<<"学号："<<number<<"  专业："<<major<<"  成绩:"<<score<<endl;
	cout<<"工作单位"<<place<<endl;
}
