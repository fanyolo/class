#include <iostream>
#include "1.h" 
using namespace std;
float a();
main(){
	int number;
	cout<<"请输入学生人数"<<endl;
	cin>>number;
	student s[number];
	int i;
	cout<<"请输入学生信息：学号、姓名、性别、年龄、三门课程的成绩(语数英)"<<endl;
	for(i=0;i<number;i++){
	cin>>s[i].n>>s[i].name>>s[i].sex>>s[i].age>>s[i].score1>>s[i].score2>>s[i].score3;
	}
	cout<<endl; 
	for(i=0;i<number;i++){
	s[i].a();
	s[i].p();
	s[i].out();
	cout<<endl; 
	}
	//输出所有学生某一课程的平均成绩；
	float m1=0,m2=0,m3=0;
	for(i=0;i<number;i++){
	m1+=s[i].score1;
	m2+=s[i].score2;
	m3+=s[i].score3;
	}
	float a1=m1/number;
	float a2=m2/number;
	float a3=m3/number;
	cout<<"语文平均成绩为："<<a1<<endl;
	cout<<"数学平均成绩为："<<a2<<endl; 
	cout<<"英语平均成绩为："<<a3<<endl;  
}
