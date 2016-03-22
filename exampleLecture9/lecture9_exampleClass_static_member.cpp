
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

using namespace std;

// Class Example with static member
// Class Templates

class arraysClass {
public:

	double *myArray;

	arraysClass(int arraySize){
		myArray = new double [arraySize];
		cout << "constructor: out of arraysClass constructor successfully" << endl;
		usleep(500000);
	};

	~arraysClass(){
		delete [] myArray;
		cout << "destructor: out of arraysClass destructor successfully" << endl;
		usleep(500000);
	};

};


class CountObj {
public:

	static int nCounts;

	CountObj(){
		nCounts++;
		cout << "inside constructor of CountObj: " << nCounts << endl;
		usleep(500000);
	};

	~CountObj(){
		nCounts--;
		cout << "inside destructor of CountObj: " << nCounts << endl;
		usleep(500000);
	};
};

int CountObj::nCounts=0;


class ConstClass {
	double value;
public:

	ConstClass(double x1) : value(x1) {}
	const double& getValue() const {return value;} // const member function returning a const&
	double& getValue() {return value;}
};

template <class T>
class Array1 {
	T x1, x2, x3;
public:
	Array1 (T y1, T y2, T y3)
	{x1=y1; x2=y2; x3=y3;}
	T calculateMax();
};

template <class T>
T Array1<T>::calculateMax()
{
	T max1;
	max1=x1;
	if (x2>max1)
		max1=x2;
	if (x3>max1)
		max1=x3;
	return max1;
}

template <class T>
class Class2 {
	T input;
public:
	Class2 (T x1) {input=x1;}
	T increaseFunc() {return ++input;}
};

// class template specialization:
template <> class Class2 <char> {
	char input;
public:
	Class2 (char x1) {input=x1;}
	char changeItToUpperCase ()
	{
		if ( (input>='a') && (input<='z') )
			input = input + 'A' - 'a';
		return input;
	}
};


int main() 
{

	/* ----------------------
	constructor & destructor
	-----------------------*/

	int arraySize = 100;
	cout << "calling arraysClass ... " << endl;
	arraysClass arrays(arraySize);
	cout << "arraysClass called!" << endl;

	cout << "dynamic allocation (1) started ..." << endl;
	CountObj *countPtr1 = new CountObj [6];
	cout << "dynamic allocation (1) ended." << endl;

	cout << "dynamic allocation (2) started ..." << endl;
	CountObj *countPtr2 = new CountObj [7];
	cout << "dynamic allocation (2) ended." << endl;

	cout << "static array (3) started ..." << endl;
	CountObj dummy[10];
	cout << "static array (3) ended ..." << endl;

	cout << "just an object stated" << endl;
	CountObj temp;
	cout << "ended " << endl;

	cout << temp.nCounts << endl;
	cout << CountObj::nCounts << endl;

	delete [] countPtr1;

	cout << "temp.nCounts:" << temp.nCounts << endl;
	cout << "CountObj::nCounts" << CountObj::nCounts << endl;

	delete [] countPtr2;

	cout << temp.nCounts << endl;
	cout << CountObj::nCounts << endl;

	/* -------
	Const
	---------*/

	ConstClass tmp1(1.5);
	const ConstClass tmp2(2.5);

	tmp1.getValue() = 3.14159; 
	tmp2.getValue() = 4.2;

	cout << "tmp1.getValue(): " << tmp1.getValue() << endl;
	cout << "tmp2.getValue(): " << tmp2.getValue() << endl;

	/* ------------------------------------
	Tempplates & Templates Specialization
	---------------------------------------*/

	cout << "     " << endl;
	cout << " ---------------- " << endl;
	cout << " Class Templates  " << endl;
	cout << " ---------------  " << endl;
	Array1 <double> array1(1.3, 0.7, 3.1);
	Array1 <int> array2(7, 0, 3);
	cout << "array1.calculatesMax():" << array1.calculateMax() << endl;
	cout << "array2.calculateMax():" << array2.calculateMax() << endl;

	cout << "     " << endl;


	cout << " ------------------------------- " << endl;
	cout << " Class Templates Specialization  " << endl;
	cout << " ------------------------------- " << endl;
	Class2 <int> intClass(7);
	Class2 <char> charClass1('m'), charClass2('q'), charClass3('1');

	cout << "intClass.increaseFunc():" << intClass.increaseFunc() << endl;
	cout << "charClass1:" << charClass1.changeItToUpperCase() << endl;
	cout << "charClass2:" << charClass2.changeItToUpperCase() << endl;
	cout << "charClass3:" << charClass3.changeItToUpperCase() << endl;

	cout << "        " << endl;

	cout << "temp.nCounts:" << temp.nCounts << endl;
	cout << "CountObj::nCounts:" << CountObj::nCounts << endl;

	cout << " at the end of the program" << endl;
	return 0;
}
