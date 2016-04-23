
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Simple example on Polymorphism (2)


class Polygon {
protected:
	float width, height;
public:
	void setValues (float x1, float y1)
	{ 
		width=x1;
		height=y1; 
	}

	virtual float calculateArea(){
		cout << "Inside Polygon Class with area equal to "<< endl;
		return 0;
	}
	//virtual float calculateArea(void) = 0;
	//virtual float calculateArea() = 0; //pure virtual
	//virtual float calculateArea(void) = 0; //pure virtual 
};

class Triangle: public Polygon {
public:
	float calculateArea(void)
	{
		cout << "  Inside Triangle " ; 
		return (width*height/2.0); 
	}
};

class Rectangle: public Polygon {
public:
	float calculateArea(void)
	{ 
		cout << " Inside Rectangle ";
		return (width*height); 
	}
};



int main () {

	Triangle triangle1;
	Rectangle rectangle1;

	Polygon *polygonPtr1 = &triangle1;
	Polygon *polygonPtr2 = &rectangle1;

	polygonPtr1->setValues (4.0, 6.0);
	polygonPtr2->setValues (4.0,6.0);

	//triangle1.setValues (4.0,6.0);
	//rectangle1.setValues (4.0,6.0);

	cout << "pointer to the Base Class (1)" << endl;
	cout << "triangle1.calculateArea():  " << triangle1.calculateArea() << endl;
	cout << "polygonPtr1->calculateArea(): " << polygonPtr1->calculateArea() << endl;
	cout << " " << endl;
	cout << "pointer to the Base Class (2)" << endl;
	cout << "rectangle1.calculateArea(): " << rectangle1.calculateArea() << endl;
	cout << "polygonPtr2->calculateArea(): " << polygonPtr2->calculateArea() << endl;
	cout << " " << endl;
	cout << " --------------------------------------------------------------" << endl;
	cout << " " << endl;

	Polygon *polygonPtr3 = &triangle1;
	//polygonPtr3->setValues (4.0,6.0);
	triangle1.setValues (4.0,6.0);
	cout << "triangle1.calculateArea():  " << triangle1.calculateArea() << endl;
	cout << "polygonPtr3->calculateArea(): " << polygonPtr3->calculateArea() << endl;
	cout << " " << endl;

	polygonPtr3 = &rectangle1;
	//polygonPtr3->setValues (4.0,6.0);
	rectangle1.setValues (4.0,6.0);
	cout << "rectangle1.calculateArea():  " << rectangle1.calculateArea() << endl;
	cout << "polygonPtr3->calculateArea(): " << polygonPtr3->calculateArea() << endl;

	cout << " " << endl;
	cout << " --------------------------------------------------------------" << endl;
	cout << " " << endl;

	cout << "pointer to the Base Class (3)" << endl;
	Polygon polygon4;
	Polygon *polygonPtr4 = &polygon4;
	polygonPtr4->setValues(2.3,3.0);
	cout << "polygonPtr4->calculateArea(): " << polygonPtr4->calculateArea() << endl;

	return 0;
}
	
