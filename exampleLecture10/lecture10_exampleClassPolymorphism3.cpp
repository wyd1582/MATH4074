
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Simple example on Polymorphism (3)

class Polygon {
protected:
	float width, height;
public:
	Polygon (float x1, float y1): width(x1), height(y1){}
	//virtual float calculateArea(void) = 0; //pure virtual 
	virtual float calculateArea(){} //pure virtual 
	void printAreaOnScreen(){
		cout << "Inside Polygon Class with area equal to ";
		cout << this->calculateArea() << endl;
	}
};

class Triangle: public Polygon {
public:
	Triangle (float x1, float y1): Polygon(x1,y1){}
	float calculateArea(){ 
		cout << "Inside Triangle Class with area equal to ";
		return (width*height/2.0);
	}
};

class Rectangle: public Polygon {
public:
	Rectangle (float x1, float y1): Polygon(x1,y1){}
	float calculateArea(){
		cout << "Inside Rectangle Class with area equal to ";
		return (width*height);
	}
};


int main () {
	
	/*--------------------------
	 With pure Vitual function
	--------------------------*/
	 Polygon p1(2.0,2.0);

	Triangle triangle1(2.5,3.0);
	Rectangle rectangle1(2.5,3.0);

	Polygon *polygonPtr1 = &triangle1;
	Polygon *polygonPtr2 = &rectangle1;

	cout << "---------------------------" << endl;
	cout << " With pure Vitual function " << endl;
	cout << "---------------------------" << endl;
	cout << "Pure Virtual: polygonPtr1->calculateArea(): " << polygonPtr1->calculateArea() << endl;
	cout << "Pure Virtual: polygonPtr1->calculateArea(): " << polygonPtr2->calculateArea() << endl;

	/*----------------------------------------------------------------
	 Pure virtual member can be called from the Abstract Base Class
	 -----------------------------------------------------------------*/

	 cout << "--------------------------------------------------" << endl;
	 cout << " Pure virtual called from the Abstract Base Class " << endl;
	 cout << "--------------------------------------------------" << endl;
	
	cout << "polygonPtr1->printAreaOnScreen() ";
	polygonPtr1->printAreaOnScreen();

	cout << "polygonPtr2->printAreaOnScreen() ";
	polygonPtr2->printAreaOnScreen();
	

	/*-----------------------------------------------------------
	 Constructor initilaizer, dynamic allocation and polymorphism
	 ------------------------------------------------------------*/

	cout << "--------------------------------------" << endl;
	 cout << " dynamic allocation and polymorphism " << endl;
	 cout << "-------------------------------------" << endl;

	Polygon *polygonPtr3 = new Triangle(2.5,3.0);
	Polygon *polygonPtr4 = new Rectangle(2.5,3.0);


	cout << "polygonPtr3->printAreaOnScreen() ";
	polygonPtr3->printAreaOnScreen();

	cout << "polygonPtr4->printAreaOnScreen() ";
	polygonPtr4->printAreaOnScreen();

	delete [] polygonPtr3;
	delete [] polygonPtr4;


	return 0;
}
	
