#include <stdio.h>
#define  f(x) (x)*(x)*3.14
main() 
{
	double s,r1,r2;
	printf("请输入圆台上下底面半径r1和r2:\n");
	scanf("%lf %lf",&r1,&r2);
	
	s=f(r1)+f(r2);
	printf("圆台上下底面面积之和");
	printf("s=%f\n",s);
}
