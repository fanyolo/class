#include<stdio.h>
#include <stdlib.h>
#include <time.h>
main(){
    int a[5][5],i,j,n=-1; 
    srand((unsigned)time(NULL));   
    for(i=0;i<5;i++){ 
	    for(j=0;j<5;j++){n++;
	       a[i][j]= rand() % 10+ 1;
		   if(n%5==0)printf("\n");
		   if(a[i][j]<10)printf(" ");	
		   printf("%d  ",a[i][j]);
		}
	}
	printf("\n\n第1与第5行对调后");
	for(j=0;j<5;j++){n++;
	      if(n%5==0)printf("\n");
		   if(a[4][j]<10)printf(" ");
		printf("%d  ",a[4][j]);
	}
	for(i=1;i<4;i++){ 
	    for(j=0;j<5;j++){n++;
	       if(n%5==0)printf("\n");
		   if(a[i][j]<10)printf(" ");	
		   printf("%d  ",a[i][j]);
		}
	}
    for(j=0;j<5;j++){n++;
           if(n%5==0)printf("\n");
		   if(a[0][j]<10)printf(" ");
		printf("%d  ",a[0][j]);
	}
	int m;
	printf("\n\n每行最大值\n");
	for(int i=0;i<=4;i++){	
		int max=a[0][j];	
		for(int j=0;j<=4;j++){	
			if(a[i][j]>max){
			max=a[i][j];
			}
		}
		for(int j=0;j<=4;j++){if(max==a[i][j]) 
		printf("%d %d行%d列\n",max,i+1,j+1); }
			}
    return 0;
}

