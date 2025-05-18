#include <stdio.h>
#include <math.h>
main()
{
    double a,b,c;
    printf("请输入斜边长c和一条直角边长a\n");
    scanf("%lf %lf",&c,&a);

    b=sqrt(c*c-a*a);
    printf("输出另一条直角边");
    printf("b=%lf\n",b);
}
