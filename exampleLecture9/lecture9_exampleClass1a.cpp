
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// class example 
// friend class


class Square; // forward declaration of Square needed by Rectangle

class Rectangle {
	int width, height;
public:
	Rectangle (){width=4; height=10;}
	Rectangle (int x1, int y1){width=x1; height=y1;}
	int area (){
		return (width * height);
	}
	void convert (Square a);
};

void Rectangle::convert (Square a) {
	width = a.side;
	height = a.side;
}

class Square {
	friend class Rectangle;
private:
	int side;
public:
	Square (int a) : side(a) {}
};

// has to be here 
//void Rectangle::convert (Square a) {
//	width = a.side;
//	height = a.side;
//}


int main() 
{

	Rectangle rect;
	cout << "rectangle area:" << rect.area() << endl;
	Square sqr (4);
	rect.convert(sqr);
	cout << "rectangle area:" << rect.area() << endl;

	return 0;
}
