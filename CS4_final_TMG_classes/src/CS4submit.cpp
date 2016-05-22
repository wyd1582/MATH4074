#include "CS4.hpp"
#include <iostream>
#include <limits>
#include <algorithm>
#include <functional>
#include <vector>
#include "simplex.h"

using namespace std;

int readfromFile(string Fname);
	
int main(int argc, char **argv){
	struct timespec etime,stime;
  	clock_gettime(CLOCK_MONOTONIC,&stime);

	readfromFile(argv[1]);
	Calibration C1;
	C1.calibrateVar();
	//Simplex(RMS,initguess, 1e-8);	
	Calibration C2;
	C2.calibrateVar();
	Calibration C3;
	C3.calibrateVar();	

	//cout<<C1.CP_FFT(90.0,1.0/12.0,0.12,0.2,-0.14);
	clock_gettime(CLOCK_MONOTONIC,&etime);
  	cout<<(etime.tv_sec-stime.tv_sec)*1000 +(etime.tv_nsec-stime.tv_nsec)/1000000<<" milliseconds\n";

	return 0;
}