#include<stdio.h>
int facsum(int n){
	int i,sum=0;
	for(i=1;i<n;i++){
		if(n%i==0){
		sum+=i;                               //求500以内每个数的因子并求和 
		}
	}
	return sum;
}
main(){int a,b,sum=0;
  int n=500;
   for(a=1;a<n;a++){if(a==facsum(a)){printf("(%d,%d)",a,a);   
		sum+=a;                                        //求完数并求和 
		}
   	   for(b=1;b<n;b++){
   	 	if(a==facsum(b)&&b==facsum(a)&&a!=b)          //判断亲密数 
			{
   	 		if(a<b){printf("(%d,%d)",a,b);   //对亲密数前后大小判断 
				}
   	 		
			}
		
		}
		
   }
   printf("\n完数和%d\n",sum);
}
