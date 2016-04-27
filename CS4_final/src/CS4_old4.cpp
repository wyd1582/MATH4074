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

using namespace std;
using namespace BT;

int readTcnt;
int readKcnt;
int readPcnt;
double* sigArray;
double* muArray;
double* thetaArray;
double* readTarr;
double* readKarr;
double* readParr;
double* Prem;
double* K;
double T;
int n=0;
int p=2;
int step=0;
vector<double> init(3,0.0);  
vector<double> initguess(3,0.0);

int readfromFile(string Fname,int &Tcnt,int &Kcnt,double* &readT,double* &readK,double* &readP);
int CP_FFT(double K,double T,double sigma,double mu,double theta);
int RMS(vector<double> x);
int getinitialguess(int startKP,int startT);

template<class Con>
void printcon(const Con& c){
  std::cout.precision(8);
  cout << "results are:";
  copy( c.begin(), c.end(), ostream_iterator<typename Con::value_type>(cout, "  ") );
  cout<<endl;
}



int main(int argc, char** argv){

 	readfromFile(argv[1],readTcnt,readKcnt,readTarr,readKarr,readParr);
  readPcnt = readKcnt; // readPcnt and readKcnt will have the same value
  n=readKcnt/readTcnt;

  //initialize    
    step = 2;
    sigArray = new double[step];  
    sigArray[0]=0.05;sigArray[step-1]=0.5;

    muArray = new double[step];   
    muArray[0]=0.05;muArray[step-1]=0.75;

    thetaArray = new double[step];    
    thetaArray[0]=-0.9;thetaArray[step-1]=-0.05;

//fill arrays  
  for(int i=1;i<step-1;i++){
    sigArray[i] =sigArray[0] + i*(sigArray[step-1] - sigArray[0])/(step-1);
    muArray[i] = muArray[0] + i*(muArray[step-1] - muArray[0])/(step-1);
    thetaArray[i] = thetaArray[0] + i*(thetaArray[step-1] - thetaArray[0])/(step-1);
  }

  getinitialguess(0,0);

  delete[] readTarr;
  delete[] readKarr;
  delete[] readParr;
  delete[] sigArray;
  delete[] muArray;
  delete[] thetaArray;
  delete[] Prem;
  delete[] K;
  return 0;
}

//read parameters from file
int readfromFile(string Fname,int &Tcnt,int &Kcnt,double* &readT,double* &readK,double* &readP){
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
		Tcnt= atof(line1.c_str());

    convert.clear();
    getline (ss,line1,' ');
    getline (ss,line1,' ');       
    Kcnt= atof(line1.c_str());     

    //convert.clear();
    getline (ss,line1,' ');
    getline (ss,line1,' ');

    readT = new double[Tcnt];
    readK = new double[Kcnt];
    readP = new double[Kcnt];           

    while ( getline (file,line) ){                
      if(linecnt>startread && linecnt<=Tcnt+startread){                                            
        readT[linecnt-startread-1] = atof(line.c_str());  
      }
      else if(linecnt>Tcnt+startread+1 && linecnt<=Tcnt+Kcnt+startread+1){                                   
        readK[linecnt-startread-Tcnt-2] = atof(line.c_str());
      }
      else if(linecnt>Tcnt+Kcnt+startread+2 && linecnt<=Tcnt+Kcnt+Kcnt+startread+2){                      
        readP[linecnt-startread-Tcnt-Kcnt-3] = atof(line.c_str());
      }
      linecnt++;
    }        
  }
  else cout << "Unable to open file"; 
  file.close();  	
	return 0;
}

//function that generates Call Premium for VG model using FFT
int CP_FFT(double K,double T,double sigma,double mu,double theta){
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

int getinitialguess(int startKP,int startT){
  double largetemp=1000000;
  double result=0;

  T = readTarr[startT];
  for(int i=0;i<n;i++){
    Prem[i] = readParr[startKP];
    K[i] = readKarr[startKP];
    startKP++;
  }

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
  return 0;
}