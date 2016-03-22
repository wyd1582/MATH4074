
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Class Example with constant member function

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
	// not the most efficient way
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

	/* -------
	Const
	---------*/

	ConstClass tmp1(1.5);
	const ConstClass tmp2(2.5);

	tmp1.getValue() = 3.14159; 
	//tmp2.getValue() = 4.2;

	cout << "     " << endl;
	cout << " ---------------- " << endl;
	cout << " Const  " << endl;
	cout << " ---------------  " << endl;
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
	cout << array1.calculateMax() << endl;
	cout << array2.calculateMax() << endl;

	cout << "     " << endl;


	cout << " ------------------------------- " << endl;
	cout << " Class Templates Specialization  " << endl;
	cout << " ------------------------------- " << endl;
	Class2 <int> intClass(7);
	Class2 <char> charClass1('m'), charClass2('q'), charClass3('1');

	cout << intClass.increaseFunc() << endl;
	cout << charClass1.changeItToUpperCase() << endl;
	cout << charClass2.changeItToUpperCase() << endl;
	cout << charClass3.changeItToUpperCase() << endl;

	cout << "exampleClass3.cpp ends (1)" << endl;
	cout << __FILE__ << " ends (2) at line " << __LINE__ << endl;

	return 0;
}
