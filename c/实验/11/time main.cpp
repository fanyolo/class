#include<iostream>
#include "time.h"
using namespace std;
int main() {
	while(1){
	Time t1,t2;
    cout<<"请输入两个时间t1,t2（时:分:秒）"<<endl;
    cin>>t1>>t2;
    cout<<"输入的两个时间为："<<endl;
	cout<<"t1:"<<t1<<endl;
    cout<<"t2:"<<t2<<endl;
    cout<<"两个时间比较："<<endl;
    if(t1>=t2){
        cout<<"结果为t1>=t2" << endl;
    } else cout<<"结果为t1<t2"<< endl;
    cout<<"输入的两个时间之和为："<<endl;
    Time t3=t1+t2;
	cout<<t3<<endl;
	if(t1>=t2){cout<<"输入的两个时间之差t1-t2为："<<endl;
    Time t4=t1-t2;
    cout<<t4<<endl;
	}else {Time t4=t2-t1;
          cout<<"t1<t2，无法计算t1-t2的差,t2-t1差为:"<<endl;
		  cout<<t4<<endl;
	}
    cout<<"(后置++)t1自增，请输入自增的次数："<<endl;
    int i,n;
	cin>>n;
	for(i=0;i<n;i++){
	t1++;
    cout<<t1<<endl;
	}
	cout<<"(前置++)t2自增，请输入自增的次数："<<endl;
	cin>>n;
	for(i=0;i<n;i++){
	++t2;
    cout<<t2<<endl;
	}
	cout<<"是否结束（1是/0否）"<<endl;
	cin>>n;
	if(n==1)break;
	}   
}
