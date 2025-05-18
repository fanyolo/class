#include<stdio.h>
#include<string.h>
 struct student {
    long no;   		    /*学号*/
    char name[10];  	/*姓名*/
    char sex;			/*性别*/
    int age;			/*年龄*/
    float score;		/*平均成绩*/
};
int nn(struct student t[] ,int n){               //统计男、女生人数
	int i,count=0;                                
	for(i=0;i<n;i++){
	if(t[i].sex=='m') 
	count++;
	}
	return count;
}
float a(struct student t[],int n){    //计算全班平均成绩
  int av=0,sum=0;
  int i;
  for(i=0;i<n;i++){
  	sum+=t[i].score;
  }
  av=sum/n;
  return av;
}
void d(struct student t[] ,int n,float p){
	int i;
	for(i=0;i<n;i++){
	if(t[i].score<p) 
	printf("学号%ld 姓名%s 性别%c 年龄%d 平均成绩%f\n",
	     t[i].no ,t[i].name,t[i].sex,t[i].age,t[i].score);
	}	
}
main(){
	int n;
	printf("请输入实际学生人数(2<n<6)：\n");
	scanf("%d",&n);
	if(2<n&&n<6){
	struct student t[n];                        //输入实际学生人数n (2<n<6)
	printf("请输入每个学生的信息（学号,姓名,性别(f/m),年龄,平均成绩五项）：\n");
	int i;                                //输入每个学生的信息，组成结构数组，并输出
	for(i=0;i<n;i++){
	  scanf("%ld %s %c %d %f",&t[i].no ,&t[i].name,&t[i].sex,&t[i].age,&t[i].score);
	}
	printf("\n学号  姓名  性别  年龄  平均成绩\n");
	for(i=0;i<n;i++){
		printf("%ld   %s    %c    %d   %f\n",
	     t[i].no ,t[i].name,t[i].sex,t[i].age,t[i].score);
	}
	printf("男生人数：%d   女生人数：%d\n",nn(t,n),n-nn(t,n));
	printf("\n全班平均成绩为：%f\n",a(t,n));
	float p=a(t,n);
	// 将低于全班平均成绩的学生信息按行输出
	printf("\n低于全班平均成绩的学生信息为\n");
	d(t,n,p); 
	}else printf("输入的实际人数有误");	
}

