
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// some simple on Class
// setting up Constructor & Destructor
// Default Constructor & Destructor


class Circle{
	double radius;
public:
	//Circle(double r1) : radius(r1) { }
	//Circle(double r1){radius=r1;}
	Circle ();
	Circle (double);
	double calculateArea(){return 3.1415*radius*radius;}
	~Circle ();
};

Circle::Circle(){
	radius = 1.0;
}

Circle::Circle(double r1){
radius = r1;
}

Circle::~Circle(){
}


class Rectangle{
	double width;
	double length;
public:
	//Rectangle(double w1, double l1) : width(w1), length(l1) { }
	Rectangle(double w1, double l1){width=w1; length=l1;}
	double calculateArea(){return width*length;}
};

class RectangularPrismA{
	double width;
	double length;
	double height;
public:
	RectangularPrismA(double w1, double l1, double h1) : width(w1), length(l1), height(h1) { }
	//RectangularPrismA(double w1, double l1, double h1)(width=w1; length=l1; height=h1;)
	double calculateVolume(){return width*length*height;}
};


class RectangularPrismB{
	Rectangle itsBase;
	double height;
public:
	RectangularPrismB(double w1, double l1, double h1) : itsBase(w1, l1), height(h1) { }
	//RectangularPrismB(double w1, double l1, double h1) : width(w1), length(l1), height(h1)
	//RectangularPrismB(double w1, double l1, double h1)(width=w1; length=l1; height=h1;)
	double calculateVolume(){return itsBase.calculateArea()*height;}
};

class Vector3D {
public:
	double xCoord;
	double yCoord;
	double zCoord;
	Vector3D () {};
	Vector3D (double x1 , double y1, double z1) : xCoord(x1), yCoord(y1), zCoord(z1) {}
	Vector3D operator + (const Vector3D&); //overloading operator+ as member function
	Vector3D operator - (const Vector3D&); //overloading operator- as member function
	double calculateLength(){return sqrt(xCoord*xCoord+yCoord*yCoord+zCoord*zCoord);}
};

Vector3D Vector3D::operator+ (const Vector3D& vector1) {
	Vector3D vector2;
	vector2.xCoord = xCoord + vector1.xCoord;
	vector2.yCoord = yCoord + vector1.yCoord;
	vector2.zCoord = zCoord + vector1.zCoord;
	return vector2;
}

Vector3D Vector3D::operator- (const Vector3D& vector1) {
	Vector3D vector2;
	vector2.xCoord = xCoord - vector1.xCoord;
	vector2.yCoord = yCoord - vector1.yCoord;
	vector2.zCoord = zCoord - vector1.zCoord;
	return vector2;
}

Vector3D operator* (const double alpha, const Vector3D& vector1) { //non-member operator overloads
	Vector3D vector2;
	vector2.xCoord = alpha*vector1.xCoord;
	vector2.yCoord = alpha*vector1.yCoord;
	vector2.zCoord = alpha*vector1.zCoord;
	return vector2;
}


int main() 
{

	double alpha = 10.0;

	Circle cir1 = 5.0;
	Circle cir2;
	//Circle cir3 {4.0};
	//Circle cir4 = {3.0};
	Circle cir5(6.0);

	cout << "     " << endl;
	cout << "cir1's area is equal to " << cir1.calculateArea() << endl;
	cout << "cir2's area is equal to " << cir2.calculateArea() << endl;
	//cout << "cir3's area is equal to " << cir3.calculateArea() << endl;
	//cout << "cir4's area is equal to " << cir4.calculateArea() << endl;
	cout << "cir5's area is equal to " << cir5.calculateArea() << endl;

	cir2 = cir1;

	cout << "cir2's area is equal to " << cir2.calculateArea() << endl;

	//

	RectangularPrismA rectP1(2.0, 3.0, 4.0);
	RectangularPrismB rectP2(2.0, 3.0, 4.0);

	cout << "     " << endl;
	cout << "rectP1 volume is equal to " << rectP1.calculateVolume() << endl;
	cout << "rectP2 volume is equal to " << rectP2.calculateVolume() << endl;

	Vector3D vector1 (3,1,2);
	Vector3D vector2 (1,2,3);

	cout << "vector1 coordinates: " << vector1.xCoord << ',' << vector1.yCoord << ',' << vector1.zCoord << endl;
	cout << "vector2 coordinates: " << vector2.xCoord << ',' << vector2.yCoord << ',' << vector2.zCoord << endl;

	Vector3D vector3, vector4, vector5, vector6;

	vector3 = vector1 + vector2;
	vector4 = vector1 - vector2;

	vector5 = vector1;

	cout << "vector3 coordinates: " << vector3.xCoord << ',' << vector3.yCoord << ',' << vector3.zCoord << endl;
	cout << "vector4 coordinates: " << vector4.xCoord << ',' << vector4.yCoord << ',' << vector4.zCoord << endl;

	cout << "vector5 coordinates: " <<  vector5.xCoord << ',' << vector5.yCoord << ',' << vector5.zCoord << endl;
	cout << "vector5's length: " << vector5.calculateLength() << endl;

	vector6 = alpha*vector1;
	cout << "vector6 coordinates: " <<  vector6.xCoord << ',' << vector6.yCoord << ',' << vector6.zCoord << endl;

	return 0;
}
