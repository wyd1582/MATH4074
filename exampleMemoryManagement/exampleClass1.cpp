//#include "stdafx.h"

#include "structures.h"
#include "functions.h"

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

int main()
{

	int aSize1 = 10;  //10;
	int aSize2 = 20;  //20;
	int aSize3 = 30;  //30;
	int nRows = 1000000;
	int i1;

	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;

	gettimeofday(&startTime, NULL);
	arraysClass arrays(aSize1, aSize2, aSize3);

	for (i1=1; i1<nRows; i1++){
		if ((i1%100000) == 0)
			cout << "i1= " << i1 << endl;
		builder1(arrays, aSize1, aSize2, aSize3);  
	}

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000.0 + useconds/1000.0); 
	cout << "Part 1 is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;

	gettimeofday(&startTime, NULL);
	for (i1=1; i1<nRows; i1++){
		if ((i1%100000) == 0)
			cout << "i1= " << i1 << endl;
		builder2(aSize1, aSize2, aSize3);  
	}

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000.0 + useconds/1000.0); 
	cout << "Part 2 is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;

}
