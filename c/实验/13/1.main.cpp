#include <iostream>
#include "string"
#include "1.h"
using namespace std;
int main(int argc, char** argv) {
	Body body;
	Circle c;
	Rectangle r;
	Triangle t;
	body.setpb(&c);
	c.setcir();
	cout << "输入圆柱体的高：";
	body.sethigh();
	cout<<"圆柱体的体积为："<<body.volume()<<endl;
	cout<<"圆柱体的表面积为："<<body.surfaceArea()<<endl;
	cout<<endl;
	body.setpb(&r);
	r.setrec();
	cout <<"输入四棱柱的高：";
	body.sethigh();
	cout<<"四棱柱的体积为："<<body.volume()<<endl;
	cout<<"四棱柱的表面积为："<<body.surfaceArea()<<endl;
	cout<<endl;
	body.setpb(&t);
	t.settri();
	cout << "输入三棱柱的高：";
	body.sethigh();
	cout<<"三棱柱的体积为："<<body.volume()<<endl;
	cout<<"三棱柱的表面积为："<<body.surfaceArea()<<endl; 
	return 0; 
}

