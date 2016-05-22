#include "functions.h"
#include "simplex.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;
using namespace BT;

typedef complex<double> dcmplx;
#define PI  3.1415926535897932
dcmplx i(0,1);

	//variables read from text file
	int readTcnt;
	int readKcnt;
	int readPcnt;
	double* readTarr;
	double* readKarr;
	double* readParr;
	bool readflag;
	int startcnt;

	//variables for Call Premium calculation
	double S0 = 100.0;
  	double r=0.005;  	
  	double q=0.0125;    	
  	double eta=0.10;
  	double alpha=0.5;
  	int n=12;
  	double N = pow(2,n);  	  	
  	int p=2;

  	//sigma, mu, theta ranges
  	int step=10;
  	double* sigarr;
  	double* muarr;
  	double* thetaarr;
  	// double lambda = 2*PI/(N*eta); unused
  	double Beta;  
  	double C;  
  	double v;	

	double* Prem;
	double* K;
	double T;
	
	vector<double> init(3,0.0);  	
	vector<double> initguess(3,0.0);  	
	vector< vector<double> > results(3, vector<double>(3));

int readfromFile(string Fname);
double CP_FFT(double Strike,double Time,double sig, double m, double th);
double RMS(vector<double> x);
int fillVariable();
int calibrateVar();
double periodicLinearOptimizer(double lower, double upper, double x);

template<class Con>
void printcon(const Con& c){
  std::cout.precision(8);
  cout << "results are:";
  copy( c.begin(), c.end(), ostream_iterator<typename Con::value_type>(cout, "  ") );
  cout<<endl;
}


int main(int argc, char** argv){
	struct timespec etime,stime;
  	clock_gettime(CLOCK_MONOTONIC,&stime);

  	readfromFile(argv[1]);
  	Prem = new double[readKcnt/readTcnt];
  	K = new double[readKcnt/readTcnt];
  	T=0;
  	startcnt=0;

  	fillVariable();  	
  	calibrateVar();
  	results[0] = Simplex(RMS,initguess, 1e-8);
  	results[0][0]=periodicLinearOptimizer(sigarr[0],sigarr[step-1],results[0][0]);
  	results[0][1]=periodicLinearOptimizer(muarr[0],muarr[step-1],results[0][1]);
  	results[0][2]=periodicLinearOptimizer(thetaarr[0],thetaarr[step-1],results[0][2]);
  	cout<<"Results for T = "<<T<<" : "<<"sigma "<<results[0][0]<<" mu "<<results[0][1]<<" theta "<<results[0][2]<<endl;
  	cout<<"USING results to calculate premiums\n";
  	for(int i=0;i<readKcnt/readTcnt;i++)
  		cout<<"Strike "<<K[i]<<" Premium "<<CP_FFT(K[i],T,results[0][0],results[0][1],results[0][2])<<endl;


  	fillVariable();  	
  	calibrateVar();
  	results[1] = Simplex(RMS,initguess, 1e-8);
  	results[1][0]=periodicLinearOptimizer(sigarr[0],sigarr[step-1],results[1][0]);
  	results[1][1]=periodicLinearOptimizer(muarr[0],muarr[step-1],results[1][1]);
  	results[1][2]=periodicLinearOptimizer(thetaarr[0],thetaarr[step-1],results[1][2]);
  	cout<<"Results for T = "<<T<<" : "<<"sigma "<<results[1][0]<<" mu "<<results[1][1]<<" theta "<<results[1][2]<<endl;
  	cout<<"USING results to calculate premiums\n";
  	for(int i=0;i<readKcnt/readTcnt;i++)
  		cout<<"Strike "<<K[i]<<" Premium "<<CP_FFT(K[i],T,results[1][0],results[1][1],results[1][2])<<endl;

  	fillVariable();  	
  	calibrateVar();
  	results[2] = Simplex(RMS,initguess, 1e-8);
  	results[2][0]=periodicLinearOptimizer(sigarr[0],sigarr[step-1],results[2][0]);
  	results[2][1]=periodicLinearOptimizer(muarr[0],muarr[step-1],results[2][1]);
  	results[2][2]=periodicLinearOptimizer(thetaarr[0],thetaarr[step-1],results[2][2]);
  	cout<<"Results for T = "<<T<<" : "<<"sigma "<<results[2][0]<<" mu "<<results[2][1]<<" theta "<<results[2][2]<<endl;
  	cout<<"USING results to calculate premiums\n";
  	for(int i=0;i<readKcnt/readTcnt;i++)
  		cout<<"Strike "<<K[i]<<" Premium "<<CP_FFT(K[i],T,results[2][0],results[2][1],results[2][2])<<endl;

	delete[] readTarr;
	delete[] readKarr;
	delete[] readParr;
	delete[] sigarr;
	delete[] muarr;
	delete[] thetaarr;
	delete[] Prem;
	delete[] K;
	clock_gettime(CLOCK_MONOTONIC,&etime);
  	cout<<(etime.tv_sec-stime.tv_sec)*1000 +(etime.tv_nsec-stime.tv_nsec)/1000000<<" milliseconds\n";
	return 0;
}

int readfromFile(string Fname){
	ifstream file(Fname.c_str());
	string line,line1;
	stringstream convert;	
	
	int startread,linecnt=0;
	startread = linecnt = 2;	

	if (file.is_open()){
		
		getline (file,line);
		stringstream ss(line);

		convert.clear();
		getline (ss,line1,' ');
		getline (ss,line1,' ');				
		readTcnt= atof(line1.c_str());

    	convert.clear();
    	getline (ss,line1,' ');
    	getline (ss,line1,' ');       
    	readKcnt= atof(line1.c_str());     

    	//convert.clear();
    	getline (ss,line1,' ');
    	getline (ss,line1,' ');

    	readTarr = new double[readTcnt];
    	readKarr = new double[readKcnt];
    	readParr = new double[readKcnt];           
    	sigarr   = new double[step];
    	muarr    = new double[step];
    	thetaarr = new double[step];

    while ( getline (file,line) ){                
      if(linecnt>startread && linecnt<=readTcnt+startread){                                            
        readTarr[linecnt-startread-1] = atof(line.c_str());  
      }
      else if(linecnt>readTcnt+startread+1 && linecnt<=readTcnt+readKcnt+startread+1){                                   
        readKarr[linecnt-startread-readTcnt-2] = atof(line.c_str());
      }
      else if(linecnt>readTcnt+readKcnt+startread+2 && linecnt<=readTcnt+readKcnt+readKcnt+startread+2){                      
        readParr[linecnt-startread-readTcnt-readKcnt-3] = atof(line.c_str());
      }
      linecnt++;
    }    
    readflag = true;

//initialize        
    sigarr[0]=0.05;	sigarr[step-1]=0.5;    
    muarr[0]=0.05;		muarr[step-1]=0.75;    
    thetaarr[0]=-0.9;	thetaarr[step-1]=-0.05;

//fill arrays  
  	for(int j=1;j<step-1;j++){
    	sigarr[j] 		= sigarr[0] + j*(sigarr[step-1] - sigarr[0])/(step-1);
    	muarr[j] 		= muarr[0] + j*(muarr[step-1] - muarr[0])/(step-1);
    	thetaarr[j] 	= thetaarr[0] + j*(thetaarr[step-1] - thetaarr[0])/(step-1);
  	}

  	}
  	else cout << "Unable to open file"; 
  	file.close();  	
  	return 0;
}

double CP_FFT(double Strike,double Time,double sig, double m, double th){  
  Beta = log(Strike);
  //double lambda = 2*PI/(N*eta); unused
  C = exp(-r*Time);  
  v=0;
  dcmplx *X = (dcmplx *)calloc(N,sizeof(dcmplx));  
  dcmplx CFunc,u,omega;

  for(int cnt=0;cnt<N;cnt++)
    {
      v=cnt*eta;
      u=v-i*(alpha+1.0);      
      omega = log(1.0-0.5*m*pow(sig,2)-th*m)/m;      
      CFunc=exp(i*u*(log(S0)+Time*(r-q+omega))) * pow((1.0-i*u*th*m + 0.5*m*pow(sig*u,2)),-Time/m);
      X[cnt] = eta*C*exp(-i*Beta*v)*CFunc/((alpha+i*v)*(alpha+i*v+1.0));      
    }
  X[0]*=0.5;
  
  dcmplx *Y=FFT(X,N);  
  double CP= exp(-alpha*Beta)*Y[0].real()/PI;
  free(X);
  free(Y);  
  return CP;
}

double RMS(vector<double> x){    
  double result=0;
  for(int j=0;j<readKcnt/readTcnt;j++){   
    result+=pow(abs(Prem[j] - CP_FFT(K[j],T,x[0],x[1],x[2])),p);
  }  
  return pow(result/(readKcnt/readTcnt),(1.0/p));
}

int fillVariable(){

	for(int j=0;j<readKcnt/readTcnt;j++){
    	Prem[j] = readParr[startcnt+j];
    	K[j] = readKarr[startcnt+j];
    }
	T = readTarr[startcnt/(readKcnt/readTcnt)];
    startcnt+=readKcnt/readTcnt;//advance startcnt 	

	return 0;
}

int calibrateVar(){
	double largetemp=1000000;
  	double result=0;

	for(int i=0;i<step;i++)
      for(int j=0;j<step;j++)
        for(int k=0;k<step;k++){
          init[0] = sigarr[i];
          init[1] = muarr[j];
          init[2] = thetaarr[k];          
          result = RMS(init);
          if(result<largetemp){
            largetemp=result;           
            initguess[0] = sigarr[i];
            initguess[1] = muarr[j];
            initguess[2] = thetaarr[k];            
          }
        }
    cout<<"Initial guess "<<initguess[0]<<" "<<initguess[1]<<" "<<initguess[2]<<endl;
    //printcon( Simplex(RMS,initguess, 1e-8) );    
    
    return 0;
}

double periodicLinearOptimizer(double lower, double upper, double x){
	double range = upper-lower;
	int n = int((x-lower)/range);

	if(x>=lower && x<=upper)
		return x;
	else
		return (n%2==0) ? x-n*range : upper+n*range-(x-lower);
}