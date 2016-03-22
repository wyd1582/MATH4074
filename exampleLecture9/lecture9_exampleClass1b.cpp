
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// class example 
// friend class


class Rectangle {
	int width, height;
public:
	Rectangle (){width=4; height=10;}
	Rectangle (int x1, int y1){width=x1; height=y1;}
	int area (){
		return (width * height);
	}
	// Not considered a member of class Rectangle. Just has access to its private & procteded members
	friend Rectangle duplicate (const Rectangle&); // friend function of class Rectangle
};

Rectangle duplicate (const Rectangle& param)
{
	Rectangle res;
	res.width = param.width*2;
	res.height = param.height*2;
	return res;
}

int main() 
{

	Rectangle foo;
	Rectangle bar (2,3);
	foo = duplicate (bar);
	cout << "rectangle bar.area():" << bar.area() << endl;
	cout << "rectangle foo.area():" << foo.area() << endl;

	return 0;
}
