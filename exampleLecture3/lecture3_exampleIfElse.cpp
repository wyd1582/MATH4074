
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
//#include <time.h>

// example on IF-ELSE and SPEED

using namespace std;

int main()
{

	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;

	int a1, i1;
	int nIter = 100000000;
	double u2;
	cout << "nIter: " << nIter << endl;

	u2 = (double (rand()) / (double (RAND_MAX+1.0)));
	cout << "RAND_MAX " << RAND_MAX << endl;

	gettimeofday(&startTime, NULL);

	for (i1=0; i1<nIter; i1++){

		u2 =(double (rand()) / (double (RAND_MAX+1.0)));

		if      ( (u2>= 0.0) && (u2 < 0.25))
			a1 = 0;
		else if ( (u2>=0.25) && (u2 < 0.50) )
			a1 = 1;
		else if ( (u2>=0.50) && (u2 < 0.75) )
			a1 = 2;
		else if ( (u2>=0.75) && (u2 < 1.00) )
			a1 = 3;
	}

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 
	cout << "loop (1) is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;

	gettimeofday(&startTime, NULL);

	for (i1=0; i1<nIter; i1++){

		u2 = (double (rand()) / (double (RAND_MAX+1.0)));

		if      ( u2 < 0.25)
			a1 = 0;
		else if ( u2 < 0.50 )
			a1 = 1;
		else if ( u2 < 0.75)
			a1 = 2;
		else
			a1 = 3;
	}

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 
	cout << "loop (2) is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;


	return 1;

}
