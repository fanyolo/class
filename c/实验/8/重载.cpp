#include<iostream>
#include<cmath>
using namespace std;
double s(double r)
{
return 3.14*r*r;
}
double s(double a,double b)
{
return a*b;
}
double s(double a,double b,double c)
{
	return sqrt((a+b+c)*(a+b-c)*(a+c-b)*(b+c-a)/16); 
}
int main()
{
	double a,b,c;
	cout<<"请输入圆的半径"<<endl;            
	cin>>a;
	if(a>0){
	cout<<"圆的面积="<<s(a)<<endl<<endl;
	}else cout<<"输入有误"<< endl; 
	cout<<"请输入长方形的长和宽"<< endl;        
	cin>>a>>b; 
	if(a>0&&b>0){
	cout<<"长方形的面积="<<s(a,b)<<endl<<endl;
	}
	else cout<<"输入有误"<<endl;
	cout<<"请输入三角形三边长"<<endl;	
	cin>>a>>b>>c;                                 
	if(a>0 && b>0 && c>0)
	{if((a+b-c>0)&&(a+c-b>0)&&(b+c-a>0))
		{
		cout <<"三角形的面积= "<<s(a,b,c)<< endl;
		}else
		{cout<<"输入有误，请重新输入"<<endl;
		cin>>a>>b>>c;
		cout<<"三角形面积="<<s(a,b,c)<< endl;
		}
	}else cout<<"输入有误"<< endl;
	return 0;
}
