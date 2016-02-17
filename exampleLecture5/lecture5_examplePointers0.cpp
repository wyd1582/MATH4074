#include <sys/time.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;

// First Example on pointers 
// simple example on pointers 


int main(){

	double *dummy;
	double myVariable;
	double myVar2;
	
	myVariable = 30;
	dummy = &myVariable;

	myVar2 = myVariable;

	cout << "address of myVariable: " << &myVariable << endl;
	cout << "address of myVariable: " << dummy << endl;
	cout << "address of myVariable: " << dummy+1 << endl;

	cout << "value of myVariable: " << myVariable << endl;
	cout << "value of myVariable: " << *dummy << endl;

	int firstValue, secondValue;
	int *myPointer;
	myPointer = &firstValue;
	*myPointer = 10;

	myPointer = &secondValue;
	*myPointer = 20;

	cout << "1st value is: " << firstValue << endl;
	cout << "2nd value is: " << secondValue << endl;

	cout << "-----------------------------------------------------" << endl;

	
	firstValue = 0;
	secondValue = 0;

	int *p1, *p2;

 	p1 = &firstValue;  // address of first value
	p2 = &secondValue; // address of second value

	*p1 = 30;   // value pointed to by p1 is equal to 30
	cout << "(a)1st value is: " << firstValue << endl;
	cout << "(a)2nd value is: " << secondValue << endl;
        cout << " " << endl;

	*p2 = *p1;  // value pointed to by p2 is equal to value pointed to by p1
	cout << "(b)1st value is: " << firstValue << endl;
	cout << "(b)2nd value is: " << secondValue << endl;
        cout << " " << endl;

	p1 = p2;    // value of pointer is copied
	cout << "(c)1st value is: " << firstValue << endl;
	cout << "(c)2nd value is: " << secondValue << endl;
        cout << " " << endl;

	*p1 = 40;   // value pointed by p1 is equal to 40 
	cout << "(d)1st value is: " << firstValue << endl;
	cout << "(d)2nd value is: " << secondValue << endl;
        cout << " " << endl;

	cout << "------------------------" << endl;
	cout << "mixing arrays & pointers" << endl;
	cout << "------------------------" << endl;
	int myArray[5];
	int *myPointer2;

	myPointer2 = myArray; // valid
	//myArray = myPointer2; // not valid

	*myPointer2 = 10;
	myPointer2++;
	
	*myPointer2 = 20;
	myPointer2 = &myArray[2];

	*myPointer2 = 30;
	myPointer2 = myArray+3;

	*myPointer2 = 40;
	myPointer2 = myArray;

	*(myPointer2+4) = 50;

	for(int i1=0; i1<5; i1++){
		cout << myArray[i1] << ",";
	}
	cout << endl;

	cout << "----------------------------" << endl;
	cout << " Initialization of Pointers " << endl;
	cout << "----------------------------" << endl;

	int myVar3=10;
	int *myPtr3 = &myVar3;
	cout << "myVar3=" << myVar3 << " *myPtr3=" << *myPtr3 << " myPtr3=" << myPtr3 << endl;

	int myVar4;
	myVar4=10;
	int *myPtr4;
        myPtr4 = &myVar4;
	cout << "myVar4=" << myVar4 << " *myPtr4=" << *myPtr4 << " myPtr4=" << myPtr4 << endl;

	//int myVar5=10;
	//int *myPtr5;
        //*myPtr5 = &myVar5;

	int myVar6=10;
	int *myPtr6 = &myVar6;
	int *myPtr7 = myPtr6;

	cout << "myPtr6=" << myPtr6 << " *myPtr6=" << *myPtr6 << endl;
	cout << "myPtr7=" << myPtr7 << " *myPtr7=" << *myPtr7 << endl;

	return 0;
}
