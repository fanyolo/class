#include <iostream>
#include <string.h>
#include "2.h" 
using namespace std;
//输入 
void student::in(){
   cin>>n>>name>>sex>>score;
}
//设计成员函数，输出学生信息；
void student::out(){
	cout<<name<<"的信息为:"<<endl;
	cout<<"学号: "<<n<<" 姓名: " <<name<<" 性别: " <<sex  <<" 成绩: "<<score<<endl;
}
//定义成员函数，修改学生信息。
void student::x(){
	cout<<"请输入修改后的学生信息：学号、姓名、性别、成绩"<<endl;
	cin>>n>>name>>sex>>score;
}

//定义类静态成员函数，统计所有学生课程的平均成绩、最高分和最低分
float student::sum=0;
float student::max=0;
float student::min=100;
void student::a(){
	sum+=score;
	if(score>max)max=score;
	if(score<min)min=score;
}
float student::b(int number) {
	cout<<"最高分："<<max<<endl<<"最低分："<<min<<endl;
	return(sum/number);
}
//定义成员函数，利用函数的重载实现通过输入学生学号或姓名查询某学生的信息
int student::c(int q){
	if(n==q){
		cout<<"查找到的学生信息如下："<<endl;
		cout<<"学号: "<<n<<" 姓名: " <<name<<" 性别: " <<sex  <<" 成绩: "<<score<<endl;
		return 1;
	}else return 0;
}
int student::c(char*na){
	if (strcmp(na,name) == 0){
		cout<<"查找到的学生信息如下："<<endl;
		cout<<"学号: "<<n<<" 姓名: " <<name<<" 性别: " <<sex  <<" 成绩: "<<score<<endl;
		return 1;
	}else return 0;
}
