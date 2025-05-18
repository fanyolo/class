#include<stdio.h>
 main()
{   printf("100匹马驮100担货，大马一匹驮3担，中马一匹驮2担，小马两匹驮一担\n");int a,b,c,n;
    
    printf("1.大马、中马、小马每种不能少于一匹，有多少种组合法\n");
     n=0;
    a=0;b=0;c=0;
	while(a<34){a++;b=0;
     while(b<=50){b++;
      c=100-a-b;
     if(a+b+c==100&&a*3+b*2+c*0.5==100){n++;
	printf("大马%d   中马%d   小马%d\n ",a,b,c);   }
	 }}printf("种数为%d\n\n",n);
	 
	printf("2.当可以缺少一种或缺二种，又有多少种组合法？\n");
	n=0;a=b=c=0;
	do{a++;
	  do{c++;
      b=100-a-c;
     if(a+b+c==100&&a*3+b*2+c*0.5==100){n++;
	printf("大马%d   中马%d   小马%d\n ",a,b,c);
	}}while(c<=100&&b>=0); c=0;}while(a<34);
	printf("种数为%d\n\n",n);
	 
	printf("对于问题1.\n");n=0;
	for(a=1;a<34;a++)
     for(b=1;b<=50;b++)
      for(c=1;c<=100;c++)
     if(a+b+c==100&&a*3+b*2+c*0.5==100){n++;
	printf("大马%d   中马%d   小马%d\n ",a,b,c);    }
	printf("种数为%d\n\n",n);
	
	printf("对于问题2.\n");n=0;
	for(a=0;a<34;a++)
     for(b=0;b<=50;b++)
      for(c=0;c<=100;c++)
     if(a+b+c==100&&a*3+b*2+c*0.5==100){n++;
	printf("大马%d   中马%d   小马%d\n ",a,b,c);    }
	printf("种数为%d\n\n",n);
}
