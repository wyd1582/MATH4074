
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// class example 
// Friend & Derived Class
class Circle{
	double radius;
public:
	//Circle(double r1) : radius(r1) { }
	Circle(double r1){radius=r1;}
	Circle ();
	//Circle (double);
	double calculateArea(){return 3.1415*radius*radius;}
};

Circle::Circle(){
	radius = 1.0;
}

/*
Circle::Circle(double r1){
	radius = r1;
}
*/

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



class Rectangle {
    int width, height;
  public:
    Rectangle() {}
    Rectangle (int x, int y) : width(x), height(y) {}
    int area() {return width * height;}
    friend Rectangle duplicate (const Rectangle&);
};

Rectangle duplicate (const Rectangle& param)
{
  Rectangle res;
  res.width = param.width*2;
  res.height = param.height*2;
  return res;
}

// friend class
#include <iostream>
using namespace std;

class Square;

class Rectangle {
    int width, height;
  public:
    int area ()
      {return (width * height);}
    void convert (Square a);
};

class Square {
  friend class Rectangle;
  private:
    int side;
  public:
    Square (int a) : side(a) {}
};

void Rectangle::convert (Square a) {
  width = a.side;
  height = a.side;
}

// derived classes
class Polygon {
protected:
	int width, height;
public:
	void set_values (int a, int b)
	{ width=a; height=b;}
};

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

	Rectangle foo;
	Rectangle bar (2,3);
	foo = duplicate (bar);
	cout << foo.area() << endl;

	Rectangle rect;
	Square sqr (4);
	rect.convert(sqr);
	cout << rect.area();

	Rectangle rect;
	Triangle trgl;
	rect.set_values (4,5);
	trgl.set_values (4,5);
	cout << rect.area() << '\n';
	cout << trgl.area() << '\n';

	return 0;
}
