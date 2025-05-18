#include<stdio.h>
main()
{   int number,a,b,c,d;
	printf("请输入一个4位正整数");
	scanf("%d",&number);
	if(number>999&&number<=9999){
    a=number%10;
    b=number%100/10;
    c=number%1000/100;
	d=number/1000;
    printf("个位是%d,十位是%d,百位是%d,千位是%d\n",a,b,c,d);
    //开始比较各个数大小 
    int n,n1,n2,n3,n4,max,min;
	n1=a;n2=b,n3=c,n4=d;
	if(n1>n2) 
  {n=n1;n1=n2;n2=n;
  }
  if(n1>n3)
  {n=n1;n1=n3;n3=n;
  }
  if(n1>n4)
  {n=n1;n1=n4;n4=n;
  }
  if(n2>n3)
  {n=n2;n2=n3;n3=n;
  } 
  if(n2>n4)
  {n=n2;n2=n4;n4=n;
  } 
  if(n3>n4)
  {n=n3;n3=n4;n4=n;
  }
	min=n1*1000+n2*100+n3*10+n4;
	max=n4*1000+n3*100+n2*10+n1;
	printf("最大数为%d\n最小数为%d\n",max,min);
	}else printf("输入的4位正整数不正确");
}
