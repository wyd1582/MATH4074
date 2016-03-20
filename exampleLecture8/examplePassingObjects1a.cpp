#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>

using namespace std;

// Passing Objects (reference vs. value)

#ifndef _class_dummyClass
#define _class_dummyClass

class dummyClass{

public:

	int size1;
	int size2;

	dummyClass(int, int);

	~dummyClass();
};
#endif

dummyClass::dummyClass(int x1, int y1){

	cout << "Inside Constructor" << endl;
	size1 = x1;
	size2 = y1;

};

dummyClass::~dummyClass(){
	cout << "Inside Destructor" << endl;
};                                             

void builder1(dummyClass myArray)
{
	cout << "inside builder1" << endl;

	cout << "size1&size2 " << myArray.size1  << " " << myArray.size2 << endl;

}

int main()
{
	int size1(20), size2(40);

	cout << " we are here " << endl;
	dummyClass myArray(size1, size2);

	builder1(myArray);

	cout << "exiting " << __FILE__ << endl;
	return 1;
}
