
//#include "stdafx.h"

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

// Parsing Command Line Arguments in C++
// main function can have two parameters argc and argv. 
// argc is an integer parameter and it is the number of arguments passed to the program
// 
//  for(int i = 0; i < argc; i++)
//	{
//		argv[i] is the argument at index i
//	}

using namespace std;

int main(int argc, char*argv[])
{

	/*
	argv[1] = market (generic name)
	argv[2] = price 
	argv[3] = Hour
	argv[4] = Min
	*/

	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;

	gettimeofday(&startTime, NULL); 

	int HM[2];
	string market = argv[1];
	double price = atof(argv[2]);
	HM[0] = atoi(argv[3]);
	HM[1] = atoi(argv[4]);

	cout << market << " price level was " << price << " at " << HM[0] << ":" << HM[1] << endl;

	// some non-sense operations ...

	int nIter = 400000000;
	int iI;
	double pi = 3.145;
	double u2, u1;

	cout << "nIter: " << nIter << endl;

	for (iI=1; iI<nIter; iI++){

		u2 = (int)iI;
		u1 = exp(sqrt(log(u2/pi)));

		if ((iI%10000000) == 0){
			cout << market << " -- index " << iI << endl;
		}

	}


	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = seconds/60.0 + useconds/(1000000.0*60.0);

	cout << market << " ends time elapsed was: " << mtime << " (minutes)" << endl;

	return 1;

}
