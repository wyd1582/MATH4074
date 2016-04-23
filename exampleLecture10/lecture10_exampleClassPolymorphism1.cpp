#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Simple example on Polymorphism (1)

class Polygon {
protected:
	float width, height;
public:
	Polygon (float x1=0, float y1=0){width=x1; height=y1;}

	//virtual float calculateArea(void)=0;
	//virtual float calculateArea(){};
	virtual float calculateArea(){
		cout << "Inside Polygon Class with area equal to "<< endl;
		return 0;
	}
};

class Triangle: public Polygon {
public:
	Triangle (float x1, float y1): Polygon(x1,y1){}
	float calculateArea(){ 
		cout << "Inside the derived class Triangle with area equal to ";
		return (width*height/2.0); 
	}
};

class Rectangle: public Polygon {
public:
	Rectangle (float x1, float y1): Polygon(x1,y1){}
	float calculateArea(){
		cout << "Inside the derived class Rectangle with area equal to ";
		return (width*height);
	}
};


int main () {
		
	cout << "---------------------------" <<  endl;
	cout << " CASE 1 ------------ Direct" << endl;
	cout << "---------------------------" <<  endl;

	Triangle triangle1(2.5, 3.0);
	Rectangle rectangle1(2.5, 3.0);

	cout << triangle1.calculateArea() << endl;
	cout << rectangle1.calculateArea() << endl;
	
	cout << "---------------------------" <<  endl;
	cout << " CASE 2 ------ Polymorphism" << endl;
	cout << "---------------------------" <<  endl;
	
	Polygon *polygonPtr;

	Triangle triangle2(2.5,3.0);
	polygonPtr = &triangle2;
	cout << polygonPtr->calculateArea() << endl;

	Rectangle rectangle2(2.5,3.0);
	polygonPtr = &rectangle2;
	cout << polygonPtr->calculateArea() << endl;
	
	return 0;
}

