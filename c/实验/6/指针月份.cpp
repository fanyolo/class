#include<stdio.h>
main()
{
  char *months[]={"January", "February","March","April","May","June","July",
                  "August","September", "October", "November" , "December" } ;
     int n;
     printf("请输入一个月份数字：\n");
    scanf("%d",&n); 
	if(n<=12 && n>=1){ 
	printf("%d月的英文名称是:%s\n",n,months[n-1]);
	}else   printf("输入的月份错误"); 
	 return 0;
}
