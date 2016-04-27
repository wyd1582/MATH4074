#ifndef CALIBRATION
#define CALIBRATION

#include <string>
#include <limits>
#include <algorithm>
#include <functional>
#include <vector>
#include "functions.h"

typedef complex<double> dcmplx;
#define PI  3.1415926535897932

using namespace std;

class Calibration{
private:
	static int objcnt;	
	//static dcmplx i(0,1);
	static dcmplx i;
	//variables read from text file
	static int readTcnt;
	static int readKcnt;
	static int readPcnt;
	static double* readTarr;
	static double* readKarr;
	static double* readParr;
	static bool readflag;
	static int startcnt;

	//variables for Call Premium calculation
	static double S0;  
  	static double r;
  	static double q;  
  	static double eta;
  	static double alpha;
  	static int n;
  	static double N;
  	static int p;

  	//sigma, mu, theta ranges
  	static int step;
  	static double* sigarr;
  	static double* muarr;
  	static double* thetaarr;
  	//static double lambda = 2*PI/(N*eta); unused
  	double Beta;  
  	double C;  
  	double v;
	
	//double T;
	//double sigma;
	//double mu;
	//double theta;

	//input parameters to RMS function
	/*static double* Prem;
	static double* K;
	static double T;*/
	double* Prem;
	double* K;
	double T;
	
	vector<double> init;  	
	vector<double> initguess;
	

public:	
	Calibration();
	~Calibration();	
	double RMS(vector<double> x);
	double CP_FFT(double Strike,double Time,double sig, double m, double th);			
	int calibrateVar();
	friend int readfromFile(string Fname);

};	

#endif
