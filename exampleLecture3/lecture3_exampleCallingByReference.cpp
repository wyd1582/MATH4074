#include "functions.h"

// very simple example on calling by value & reference

int main()
{

	double width(0);
	double height(0);

	double factor = 2.5;

	width = 2.5;
	height = 3.5;

	cout << " " << endl;
	cout << "width=" << width << " height=" << height << endl;

	cout << " " << endl;
	cout << "---------------------------------------" << endl;
	multiplyFunc1(factor, width, height);
	cout << "after multiplyFunc1: width=" << width << " height=" << height << endl;

	cout << " " << endl;
	cout << "---------------------------------------" << endl;
	multiplyFunc2(factor, width, height);
	cout << "after multiplyFunc2: width=" << width << " height=" << height << endl;


	return 1;

}
