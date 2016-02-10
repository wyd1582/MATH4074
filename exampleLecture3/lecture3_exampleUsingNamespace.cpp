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

// simple example on using namespace

using namespace std;

namespace firstInt
{
	int x1 = 5;
	int x2 = 10;
}

namespace secondDouble
{
	double x1 = 3.1416;
	double x2 = 2.7183;
}


int main()
{
	using firstInt::x1;
	using secondDouble::x2;

	
	cout << "--------------------" << endl;
	cout << "x1=" << x1 << endl;
	cout << "x2=" << x2 << endl;

	cout << "  " << endl;

	cout << "firstInt::x2    =" << firstInt::x2 << endl;
	cout << "secondDouble::x1=" << secondDouble::x1 << endl;

	return 0;

}
