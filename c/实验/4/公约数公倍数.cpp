#include<stdio.h>
int f(int x,int y)
{   int c,i,n=0;
    c=x<y?x:y;
    for(i=c;i<=c&&i>0;i--){
    	if(x%i==0&&y%i==0){n++;
    		if(n==1){printf("最大公约数为%d\n",i);
			}
		}
	}    
	return 0;
}
int g(int x,int y)
{   int c,i,n;
    c=x>y?x:y;
    n=0;
    for(i=c;i>=c;i++){
    	if(i%x==0&&i%y==0){n++;
    		if(n==1){printf("最小公倍数为%d\n",i);
			}
		}
	}
	return 0;
}
int inNumber(int n){
    if(n>0) {return n;
	}else printf("输入错误，请输入正确的正整数\n");
    
}
main(){int a,b,c,d;
   	printf("请输入两个正整数\n");
   	scanf("%d%d",&a,&b);
	c=inNumber(a); 
	d=inNumber(b);
	f(c,d);
	g(c,d);
}
