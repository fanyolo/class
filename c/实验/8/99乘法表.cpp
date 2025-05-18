#include <iostream>
#include <iomanip>
using namespace std;
int main()
{ int i,j;
  cout<<"99乘法表"<<endl<<"格式一：左下三角"<<endl;
    for(i=1;i<=9;i++)
    {for(j=1;j<=i;j++)
        {
        cout<<j<<'*'<<i<<'='<<setw(2)<<i*j;
        if(j<i)cout<<"\t";
        }
        cout<<endl;
    }
cout<<"格式二：右下三角"<<endl; 
for(i=1;i<=9;i++)
    {int k;
	for(k=1;k<=9-i;k++){
		cout<<"\t";
	}
	for (j=1;j<=i;j++)
        { 
       cout<<std::right<<j<<'*'<<i<<'='<<setw(2)<<i*j;
        if(j<i)cout<<"\t";
        }
        cout<<endl;
    }
}
