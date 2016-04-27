#include "functions.h"
#include "simplex.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <complex>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>


typedef complex<double> dcmplx;
#define PI  3.1415926535897932
dcmplx i(0,1);
double* readT;
double* readK;
double* readP;
double T =0.25;
double K[] ={100,104,108,110,113};
double Prem[] = {7.4329,5.1797,3.2578,2.4397,1.4172};
int n=5;
int p=2;

using namespace std;
using namespace BT;

double readfromFile(string Fname);
double CP_FFT(double K,double T,double sigma,double mu,double theta);
double RMS(vector<double> x);

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

//read parameters from file
  	readfromFile(argv[1]);
//initialize  	
  	int step = 2;
  	double* sigArray = new double[step];  
  	sigArray[0]=0.05;sigArray[step-1]=0.5;

  	double* muArray = new double[step];  	
  	muArray[0]=0.05;muArray[step-1]=0.75;

  	double* thetaArray = new double[step];  	
  	thetaArray[0]=-0.9;thetaArray[step-1]=-0.05;

//fill arrays  
  for(int i=1;i<step-1;i++){
  	sigArray[i] =sigArray[0] + i*(sigArray[step-1] - sigArray[0])/(step-1);
  	muArray[i] = muArray[0] + i*(muArray[step-1] - muArray[0])/(step-1);
  	thetaArray[i] = thetaArray[0] + i*(thetaArray[step-1] - thetaArray[0])/(step-1);
  }

  vector<double> init(3,0.0);  
  vector<double> initguess(3,0.0);
  double largetemp=1000000;
  double result=0;

	for(int i=0;i<step;i++)
  		for(int j=0;j<step;j++)
  			for(int k=0;k<step;k++){
  				init[0] = sigArray[i];
  				init[1] = muArray[j];
  				init[2] = thetaArray[k];  				
  				result = RMS(init);
  				if(result<largetemp){
  					largetemp=result;  					
  					initguess[0] = sigArray[i];
  					initguess[1] = muArray[j];
  					initguess[2] = thetaArray[k];
  					
  				}
  			}
  cout<<"Initial guess "<<initguess[0]<<" "<<initguess[1]<<" "<<initguess[2]<<endl;  
  printcon( Simplex(RMS, initguess, 1e-8) );


  delete[] sigArray;	  
  delete[] muArray;
  delete[] thetaArray;  
  delete[] readT;
  delete[] readK;
  delete[] readP;
	
  clock_gettime(CLOCK_MONOTONIC,&etime);
  cout<<(etime.tv_sec-stime.tv_sec)*1000 +(etime.tv_nsec-stime.tv_nsec)/1000000<<" milliseconds"<<endl;  
  return 0;
}

//function that generates Call Premium for VG model using FFT
double CP_FFT(double K,double T,double sigma,double mu,double theta){
  double S0 = 100.0;  
  double r=0.005;
  double q=0.0125;  
  double eta=0.10;
  double alpha=0.5;
  int n=12;
  double N = pow(2,n);
  double Beta = log(K);
  //double lambda = 2*PI/(N*eta); unused
  double C= exp(-r*T);  
  double v=0;
  dcmplx *X = (dcmplx *)calloc(N,sizeof(dcmplx));  
  dcmplx CFunc,u,omega;

  for(int cnt=0;cnt<N;cnt++)
    {
      v=cnt*eta;
      u=v-i*(alpha+1.0);      
      omega = log(1.0-0.5*mu*pow(sigma,2)-theta*mu)/mu;      
      CFunc=exp(i*u*(log(S0)+T*(r-q+omega))) * pow((1.0-i*u*theta*mu + 0.5*mu*pow(sigma*u,2)),-T/mu);
      X[cnt] = eta*C*exp(-i*Beta*v)*CFunc/((alpha+i*v)*(alpha+i*v+1.0));      
    }
  X[0]*=0.5;
  
  dcmplx *Y=FFT(X,N);  
  double CP= exp(-alpha*Beta)*Y[0].real()/PI;
  free(X);
  free(Y);  
  return CP;
}

//Root Mean Square
double RMS(vector<double> x){    
  double result=0;
  for(int i=0;i<n;i++){  	
    result+=pow(abs(Prem[i] - CP_FFT(K[i],T,x[0],x[1],x[2])),p);
  }  
  return pow(result/n,(1.0/p));
}

//read parameters from file
double readfromFile(string Fname){
	ifstream file(Fname.c_str());
	string line,line1;
	stringstream convert;
	int T=0,K=0,P=0;	
	//double* readT;
	//double* readK;
	//double* readP;
	int startread,linecnt=0;
	startread = linecnt = 2;	

	if (file.is_open()){
		
		getline (file,line);
		stringstream ss(line);

		convert.clear();
		getline (ss,line1,' ');
		getline (ss,line1,' ');				
		T= atof(line1.c_str());	
		

		convert.clear();
		getline (ss,line1,' ');
		getline (ss,line1,' ');				
		K= atof(line1.c_str());			

		convert.clear();
		getline (ss,line1,' ');
		getline (ss,line1,' ');				
		P= atof(line1.c_str());			

		readT = new double[T];
		readK = new double[K];
		readP = new double[P];

		while ( getline (file,line) ){      					
      		if(linecnt>startread && linecnt<=T+startread){ 				      			      			
      			readT[linecnt-startread-1] = atof(line.c_str());	
      		}
      		else if(linecnt>T+startread+1 && linecnt<=T+K+startread+1){     			      			
      			readK[linecnt-startread-T-2] = atof(line.c_str());
  			}
  			else if(linecnt>T+K+startread+1 && linecnt<=T+K+P+startread+1){
				readP[linecnt-startread-T-K-2] = atof(line.c_str());
  			}
  			linecnt++;
    	}    
  	}
  	else cout << "Unable to open file"; 
  	file.close();  	
	return 0;
}