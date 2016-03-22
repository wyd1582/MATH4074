
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Simple example on Inheritance (1)

// Base class
class Polygon {
protected:
	int width, height;
public:
	void set_values (int a, int b){ width=a; height=b;}
};

// Derived classes
class Rectangle: public Polygon {
public:
	int area ()
	{ return width * height; }
};

class Triangle: public Polygon {
public:
	int area ()
	{ return width * height / 2; }
};
  

int main() 
{

	Rectangle rect;
	Triangle trgl;
	rect.set_values (4, 5);
	trgl.set_values (4, 5);
	cout << "rectangle area:" << rect.area() << endl;
	cout << "triangle area: " << trgl.area() << endl;

	return 0;
}
