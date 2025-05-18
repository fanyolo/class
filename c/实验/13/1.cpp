#include <iostream>
#include "string"
#include "1.h"
#include "cmath" 
using namespace std; 
float Body::volume(){
	return pbasic->area()*high;
}
float Body::surfaceArea(){
	return 2*pbasic->area()+pbasic->girth()*high;
}
void Body::setpb(Plane *p){
	pbasic=p;
}
void Body::sethigh(){
	cin >>high;
}
void Rectangle :: setrec(){
	cout << "输入四棱柱底面的长：" ;cin >>a; 
	cout << "输入四棱柱底面的宽：" ;cin >> b; 
}
float Rectangle :: area ()const{
	return a*b;
}
float Rectangle ::girth ()const{
	return 2*(a+b);
}
void Circle :: setcir(){
	cout <<"输入圆柱的半径：" ;
	cin >> a;
}
float Circle :: area ()const{
	return 3.14159*a*a;
}
float Circle :: girth() const{
	return 2*3.14159*a;
}
void Point ::setpoint(){
	cin >> x >>y;
}
void Triangle :: settri(){
	cout << "输入三棱柱底面顶点A的<x y>坐标：" ;
	A.setpoint();
	cout << "输入三棱柱底面顶点B的<x y>坐标：" ;
	B.setpoint();
	cout << "输入三棱柱底面顶点C的<x y>坐标：" ;
	C.setpoint();
}
float Triangle :: area() const{
	float m;
	m=A.x*B.y+A.y*C.x+B.x*C.y-A.x*C.y-A.y*B.x-B.y*C.x;
	if(m>0) return m/2;
	else return -m/2;
}
float Triangle :: girth()const{
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y))+sqrt((C.x-B.x)*(C.x-B.x)+(C.y-B.y)*(C.y-B.y))+sqrt((A.x-C.x)*(A.x-C.x)+(A.y-C.y)*(A.y-C.y));
}


