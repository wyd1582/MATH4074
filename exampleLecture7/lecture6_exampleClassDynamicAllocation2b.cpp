#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>

// ===========================================
// Call Example - Dynamic Allocation 

// Case 2: Note that for this case size1&size2 
//         can be declared PUBLIC or PRIVATE
//--------------------------------------------
using namespace std;

#ifndef _class_arraysClass
#define _class_arraysClass

class arraysClass{

	int size1;
	int size2;

public:

	int **frequencies;
	//Constructor
	arraysClass(int size1, int size2);

	//Destructor
	~arraysClass();
};
#endif

arraysClass::arraysClass(int size1, int size2){


	//size1 = _size1;
	//size2 = _size2;

	cout << "Constructor: size1&size2 " << size1 << " " << size2 << endl;
	frequencies = new int*[size1+1];
	for (int i=0; i<=size1; i++){
		frequencies[i] = new int[size2+1];
	}
};

arraysClass::~arraysClass(){
	cout << "Destructor: size1&size2 " << size1 << " " << size2 << endl;
	for (int i=0; i<=size1; i++){
		delete [] frequencies[i];
	}
	delete [] frequencies;
};                                             

void builder1(arraysClass &arrays, int size1, int size2)
{
	int i1, i2;
	for (i1=0; i1<=size1; i1++){
		for (i2=0; i2<=size2; i2++){
			arrays.frequencies[i1][i2] = 0; 
		}
	}
}

int main()
{
	int size1 = 20;
	int size2 = 30;
	arraysClass arrays1(size1, size2);
	//arraysClass arrays2 = arrays1;

	builder1(arrays1, size1, size2);

	return 1;
}
