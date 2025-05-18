#include<stdio.h>
main(){
	int n,x,sum,sum1,sum2;
	n=1000;sum1=0;sum2=0;
	int number1=0,number2=0;
	for(x=2;x<n;x++){int a,b=1;
		for(a=2;a<x;a++){
			if(x%a==0){
				b=0;
				break;
			}
		}
	        if(b==1){number1++;
		    if(number1==1)printf("最小素数：");
		    if(number1<=10){
			printf("%d",x);printf("   ");
			if(number1==5)printf("\n          ");
			if(number1==10)printf("\n");
			sum1+=x;}  
		}
	}
    for(x=n;x>1;x--){int a,b=1;
		for(a=2;a<x;a++){
			if(x%a==0){
				b=0;
				break;
			}
		}
	        if(b==1){number2++;
		    if(number2==1)printf("最大素数：");
		    if(number2<=10){
			printf("%d",x);printf("   ");
			if(number2==5)printf("\n          ");
			if(number2==10)printf("\n");
			sum2+=x;}  
			}
		}
	sum=sum1+sum2;
	printf("\n素数之和：%d",sum);
}

