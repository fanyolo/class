#include<stdio.h>
#include <stdlib.h>
#include <time.h>
void max(int a[],int l){
	int i,j,n;
	for(i=0;i<l;i++){
	  for(j=i+1;j<l;j++){if(a[i]>a[j]){
	  	n=a[i];a[i]=a[j];a[j]=n;
	  } 
	  }
	}
	int number=-1;
for(i=0;i<l;i++){
	number++;
	if(number%5==0)printf("\n");
    printf("%d  ",a[i]);}
	}
	
int j(int a[],int n){
	int b[n+5];
	int i,k;
	for(i=0;i<n+5;i++){
	if(i<n){	b[i]=a[i];
	}else b[i]= rand() % 100+ 1;
	
		
		}max(b,n+5);
return b[n+5];	
}
	
main(){
int a[10],i,number=0,k;
    srand((unsigned)time(NULL));
    printf("随机产生的10个数为：\n");
    for(i=0;i<10;i++){number++; 
	    a[i]= rand() % 100+ 1;	
		printf("%d  ",a[i]);
		if(number%5==0)printf("\n");
		}
	printf("\n");
	printf("排序后的数字为：");
    max(a,10);
printf("\n增加数后排序后的数字为：");   
    j(a,10);
    return 0;
}
