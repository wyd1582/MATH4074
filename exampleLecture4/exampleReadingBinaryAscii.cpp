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

// simple example on comparing reading a binay file vs. an ascii file

//-------------------------------
// Comparing ASCII vs BINARY
//--------------------------------

int main(int argc, char*argv[])
{
	int i1;

	int nRows = 20000000;


	double dummy;


	// time measurement in milliseconds
	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;

	//==========================
	//      BINARY FORMAT 
	//==========================

	gettimeofday(&startTime, NULL); 


	string input1 = "output1.bin"; 
	ifstream input1File; 
	remove(input1.c_str()); 
	input1File.open(input1.c_str(), ios::in | ios::binary);

	for (i1=1; i1<=nRows; i1++){
		input1File.read( (char *)(&dummy), sizeof(double));
	}
	input1File.close();


	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000.0 + useconds/1000.0); 

	cout << "Reading the BINARY file is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;
	//------------------------------------------------------------------------------------------------------


	//=========================
	//       ASCII FORMAT
	//=========================
	gettimeofday(&startTime, NULL); 


	FILE *input2;
    input2 = fopen("output1.dat", "r");

	for (i1=1; i1<=nRows; i1++){
		fscanf(input2, "%lf \n", &dummy);
	}
    fclose(input2);

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 


	cout << "Reading the ASCII file is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;
	//----------------------------------------------------------------------------------------------------


	return 0;
}


