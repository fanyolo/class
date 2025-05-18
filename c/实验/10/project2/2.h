class student 
{   
public:
	student(){//定义不需参数的构造函数完成类成员变量的初始化，并将课程成绩全部初始化为0
	n=100;              
    name;  	 
    sex=18;      	  	  
    score=0;
	}
	void in();   	
    void out();
    void a();
    void x();
    static float b(int number);
    int c(int n);
	int c(char*name);  
private:
	long n;              	/*学号*/
    char name[10];  	   /*姓名*/
    char sex;      	  	  /*性别*/
    float score;    	 /*成绩*/
	static float sum;// 所有学生课程成绩之和
    static float max; // 最高分
    static float min; // 最低分	
};
 
