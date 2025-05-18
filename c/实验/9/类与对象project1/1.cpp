#include <iostream>
#include "1.h" 
using namespace std;
//设计成员函数，计算每个学生的平均成绩；
float student::a(){
	float sum=0;
	sum=(score1+score2+score3)/3;
	cout<<name<<"平均成绩:"<<sum<<endl;
	return sum;
}
//设计成员函数，判断每个学生是否有不及格的课程；
void student::p(){
	if(score1<60)cout<<name<<"的语文成绩不合格"<<endl;
	if(score2<60)cout<<name<<"的数学成绩不合格"<<endl;
	if(score3<60)cout<<name<<"的英语成绩不合格"<<endl;
	if(score1>=60&&score2>=60&&score3>=60)cout<<name<<"成绩合格"<<endl;
	
}
//设计成员函数，输出学生信息；
void student::out(){
	cout<<name<<"的信息为:"<<endl;
	cout<<"学号:"<<n<<"姓名:" <<name<<"性别:" <<sex <<"年龄:"<<age <<"三门课程的成绩:"<<score1<<"  "<<score2<<"  "<<score3<<endl;
}
//输出所有学生某一课程的平均成绩；

