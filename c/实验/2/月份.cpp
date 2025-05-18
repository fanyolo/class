#include<stdio.h>
int main()
{   
    int m;
	printf("请输入一个月份数字\n");
	scanf("%d",&m);
	if(m>=1&&m<=12){
	printf("对应的英文为\n");
		switch(m){
			case 1:printf("January");break;
			case 2:printf("February");break;
			case 3:printf("March");break;
			case 4:printf("April");break;
			case 5:printf("May");break;
			case 6:printf("June");break;
			case 7:printf("July");break;
			case 8:printf("August");break;
			case 9:printf("September");break;
			case 10:printf("October");break;
			case 11:printf("November");	break;
			case 12:printf("December");break;
		}
}else printf("输入有误，请输入一个正确的月份数字\n");
  
}
