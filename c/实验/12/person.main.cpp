#include<iostream>
#include<string>
#include "person.h"
using namespace std;
//对各种类的对象信息进行修改、显示等操作
main(){
	cout<<"请输入人员信息(姓名、性别、年龄)"<<endl;
	string nam;char b;int c;
	cin>>nam>>b>>c; 
	person a1(nam,b,c);
	cout<<"人员信息为："<<endl;
	a1.out1();
	cout<<"是否需要修改信息（1是/0否）"<<endl;
	int i;
	cin>>i;
	if(i==1){
	cout<<"请输入修改后的人员信息(姓名、性别、年龄)"<<endl;
	string nam;char b;int c;
	cin>>nam>>b>>c; 
	person a1(nam,b,c);
	cout<<"修改后的人员信息为："<<endl;
	a1.out1();
	}
	cout<<endl;
	
 	cout<<"请输入老师信息(姓名、性别、年龄、工资、职称)"<<endl;	
	int f;string g;
	cin>>nam>>b>>c>>f>>g;
	teacher a2(nam,b,c,f,g);
	cout<<"老师信息为："<<endl;
	a2.out2();
	cout<<"是否需要修改信息（1是/0否）"<<endl;
	cin>>i;
	if(i==1){
	cout<<"请输入修改后的老师信息(姓名、性别、年龄、工资、职称)"<<endl;	
	int f;string g;
	cin>>nam>>b>>c>>f>>g;
	teacher a2(nam,b,c,f,g);
	cout<<"修改后的老师信息为："<<endl;
	a2.out2();}
	cout<<endl;
	
	cout<<"请输入学生信息(姓名、性别、年龄、学号、专业、成绩)"<<endl;
	int n;string e;float d;
	cin>>nam>>b>>c>>n>>e>>d;
	student a3(nam,b,c,n,e,d);
	cout<<"学生信息为："<<endl;
	a3.out3();
	cout<<"是否需要修改信息（1是/0否）"<<endl;
	cin>>i;
	if(i==1){
	cout<<"请输入修改后的学生信息(姓名、性别、年龄、学号、专业、成绩)"<<endl;
	int n;string e;float d;
	cin>>nam>>b>>c>>n>>e>>d;
	student a3(nam,b,c,n,e,d);
	cout<<"修改后的学生信息为："<<endl;
	a3.out3();}
	cout<<endl;
	
	cout<<"请输入在职研究生信息(姓名、性别、年龄、工资、职称、学号、专业、成绩、工作单位)"<<endl;
	string h;
	cin>>nam>>b>>c>>f>>g>>n>>e>>d>>h;
	graduate a4(nam,b,c,f,g,n,e,d,h);
	cout<<"在职研究生信息为："<<endl;
	a4.out4();
	cout<<"是否需要修改信息（1是/0否）"<<endl;
	cin>>i;
	if(i==1){
	cout<<"请输入修改后的在职研究生信息(姓名、性别、年龄、工资、职称、学号、专业、成绩、工作单位)"<<endl;
	string h;
	cin>>nam>>b>>c>>f>>g>>n>>e>>d>>h;
	graduate a4(nam,b,c,f,g,n,e,d,h);
	cout<<"修改后的在职研究生信息为："<<endl;
	a4.out4();}
}
