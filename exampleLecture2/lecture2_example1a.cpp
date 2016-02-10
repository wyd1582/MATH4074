//#include "stdafx.h"

//#include "functions.h"

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

// using getline
// mixing integers/doubles with string

// To get an entire line from cin, there exists a function called
// getline, that takes the stream (cin) as first argument and the string 
// variable as the second argument

int main()
{

	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;


	double i1, i2;

	cout << "i1=" << i1 << endl;
	cout << "i2=" << i2 << endl;

	gettimeofday(&startTime, NULL); 

	cout << "Enter a number: ";
	//cin >> i1;
	cout << " You entered: " << i1 << endl;

	cout << "Enter another number: ";
	//cin >> i2;
	cout << " You entered this time: " << i2 << endl;

	string myString;
	cout << "What market are you trading? ";

	getline(cin, myString);
	cout << myString << endl;

	cout << "What other market will you be trading? ";
	getline(cin, myString);
	cout << myString << endl;

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec;
	mtime = seconds*1000 + useconds/1000.0; 

	cout << "running is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;


	return 1;

}
