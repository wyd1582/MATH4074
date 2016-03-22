
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Simple example on Inheritance (2)

// Base Class
class Polygon {
protected:
	float width, height;
public:
	void setWidth  (float x1) {width = x1;}
	void setHeight (float y1) {height = y1;}
};

// Base class PaintCost
class PaintCost 
{
public:
	float calculatePaintCost(float area)
	{
		return area*50.0;
	}
};


//Derived class
class Triangle: public Polygon, public PaintCost {
public:
	float calculateArea(){ 
		return (width*height/2.0); 
	}
};


//Derived class
class Rectangle: public Polygon, public PaintCost {
public:
	float calculateArea(){
		return (width*height);
	}
};

int main () {

	Rectangle rectangle1;
	Triangle triangle1;

	float area1, area2;

	rectangle1.setWidth(2.5);
	rectangle1.setHeight(3.0);

	triangle1.setWidth(2.5);
	triangle1.setHeight(3.0);

	// Print the area of the object.
	cout << "Rectangle area is equal to " << rectangle1.calculateArea() << endl;
	cout << "Triangle area is equal to " << triangle1.calculateArea() << endl;

	area1 = rectangle1.calculateArea();
	area2 = triangle1.calculateArea();

	cout << "Total paint cost for rectangle: $" << rectangle1.calculatePaintCost(area1) << endl;
	cout << "Total paint cost for triangle: $" << triangle1.calculatePaintCost(area2) << endl;

	return 0;
}

