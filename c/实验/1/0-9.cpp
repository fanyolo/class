#include <stdio.h>
main()
{   printf("请输入整型\n");
	char n;
	n=getchar(); putchar('\n');
	printf("字符型为");
	putchar(n);putchar('\n');
	printf("整型为");
	printf("%d\n",n);
	int a;
	a=n-48;
	printf("十进制整数为");
	printf("%d\n",a);
	
}

