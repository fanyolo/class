#include <iostream>
#include "2.h" 
using namespace std;
main(){
	int number;
	cout<<"请输入学生人数（2-6）"<<endl;
	while(1){
	cin>>number;
	if(number>2&&number<6){
	student s[number];
	cout<<"请输入学生信息：学号、姓名、性别、成绩"<<endl;
	int i;
	for(i=0;i<number;i++){
	s[i].in();
	}
	cout<<endl;//输出 
	for(i=0;i<number;i++){
	s[i].out(); 
	}
	cout<<endl;//修改
	while(1){
	cout<<"请输要修改第几个学生(输入0退出)"<<endl;
	int m;
	cin>>m;
	if(m==0)break; 
	s[m-1].x();
	cout<<"修改后信息为"<<endl;
	for(i=0;i<number;i++){
	s[i].out(); 
	}
	}
	//查找 
	while(1){
	cout<<"是否要查找学生(1是/0否)"<<endl;
	int m;
	cin>>m;
	if(m==0)break;
	cout<<"请输入要查找的学生学号或姓名(学号0/姓名1)"<<endl;
	int choice;
	cin>>choice;
	if(choice==0){
	cout<<"学号";
	int q,q1,q2=0;
	cin>>q;
	for(i=0;i<number;i++){
    q1=s[i].c(q);
	if(q1==1)q2=1;
	}
	if(q2==0)cout<<"未找到该学生"<<endl;
	}
	
	if(choice==1){
	cout<<"姓名";
	int m1,m2=0;
	char na[10];
	cin>>na;
	for(i=0;i<number;i++){
    m1=s[i].c(na);
    if(m1==1)m2=1;
	}
	if(m2==0)cout<<"未找到该学生"<<endl;}
    }
	
	cout<<endl<<"所有学生情况如下："<<endl;
	for(i=0;i<number;i++){
	s[i].a();
	}
	cout<<"学生的平均成绩："<<student::b(number)<<endl;
	break;	
	}else cout<<"输入错误，则重新输入"<<endl;
		}	
}
