#include<string>
using namespace std;
class person{//定义一个人员基类，包括数据成员姓名、性别、年龄；
	public: 
   		 person(string nam,char b,int c)   //利用构造函数对类对象进行初始化
		 {name=nam;
		  sex=b;
		  age=c;}
	void out1();
	protected:	
    string name;
	char sex;
	int age;
};

class teacher:virtual public person{//教师类增加数据成员：工资、职称，
	public:
	teacher(string a,char b,int c,int f,string g):person(a,b,c){
		money=f;
		title=g;}
	void out2();
	private:
	int money;
	string title;	
};

class student:virtual public person{//学生类增加数据成员：学号、专业和成绩
     public:
	 student(string a,char b,int c,int n,string e,float d):person(a,b,c)
	 {number=n;
	  major=e;
	  score=d;
	  
	 }
	 void out3();
	 protected:
	 int number;
     float score;
     string major;  
};

class graduate:public teacher,public student{//由学生类和教师类派生在职研究生类，增加工作单位
	public:
	graduate(string a,char b,int c,int f,string g,int n,string e,float d,string h)
	:person(a,b,c),teacher(a,b,c,f,g),student(a,b,c,n,e,d){
	place=h;
	}
	void out4();
	private:
	string place;
};
