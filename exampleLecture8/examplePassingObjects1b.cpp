#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>

using namespace std;

// Copy Constructor

#ifndef _class_dummyClass
#define _class_dummyClass

class dummyClass{

public:

	int size1;
	int size2;

	dummyClass(int x1=0, int x2=0){
		cout << "Inside Constructor" << endl;
		size1 = x1;
		size2 = x2;
	}
	//copy constructor
	dummyClass (const dummyClass & myArray)
	{
		cout << "Inside Constructor (2)" << endl;
		size1 = myArray.size1;
		size2 = myArray.size2;
	}

	~dummyClass(){
		cout << "Inside Destructor" << endl;
	}
};
#endif    

void builder1(dummyClass myArray)
{
	cout << "inside builder1" << endl;

	cout << "size1&size2 " << myArray.size1  << " " << myArray.size2 << endl;

}

int main()
{
	int size1(20), size2(40);
	dummyClass myArray1(size1, size2);

	cout << "setting myArray2 equal to myArray1" << endl;
	dummyClass myArray2=myArray1;

	//myArray2 = myArray1;

	cout << "before builder1 " << endl;
	builder1(myArray2);
	cout << "after builder1 " << endl;

	cout << "exiting " << __FILE__ << endl;
	return 1;
}
