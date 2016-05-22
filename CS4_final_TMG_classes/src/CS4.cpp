#include "CS4.hpp"
#include "functions.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <algorithm>
#include <iterator>

	
	int Calibration::objcnt=0;
	dcmplx Calibration::i = dcmplx(0,1);
	//variables read from text file
	int Calibration::readTcnt;
	int Calibration::readKcnt;
	int Calibration::readPcnt;
	double* Calibration::readTarr;
	double* Calibration::readKarr;
	double* Calibration::readParr;
	bool Calibration::readflag = false;
	int Calibration::startcnt=0;

	//variables for Call Premium calculation
	double Calibration::S0 = 100.0;
  	double Calibration::r=0.005;  	
  	double Calibration::q=0.0125;    	
  	double Calibration::eta=0.10;
  	double Calibration::alpha=0.5;
  	int Calibration::n=12;
  	double Calibration::N = pow(2,n);  	  	
  	int Calibration::p=2;

  	//sigma, my theta ranges
  	int Calibration::step=2;
  	double* Calibration::sigarr;
  	double* Calibration::muarr;
  	double* Calibration::thetaarr;
  	
//constructor  	
Calibration::Calibration():Prem(new double[Calibration::readKcnt/Calibration::readTcnt]),
							  K(new double[Calibration::readKcnt/Calibration::readTcnt]),
							  init(vector<double>(3,0.0)),
							  	initguess(vector<double> (3,0.0)){
	objcnt++;
    for(int j=0;j<Calibration::readKcnt/Calibration::readTcnt;j++){
    	Prem[j] = Calibration::readParr[Calibration::startcnt+j];
    	K[j] = Calibration::readKarr[Calibration::startcnt+j];
    }
	T = readTarr[Calibration::startcnt/(Calibration::readKcnt/Calibration::readTcnt)];
    Calibration::startcnt+=Calibration::readKcnt/Calibration::readTcnt;//advance startcnt 	
}

//destructor
Calibration::~Calibration(){	
	if(objcnt==1 && Calibration::readflag){
		delete[] Calibration::readTarr;
		delete[] Calibration::readKarr;
		delete[] Calibration::readParr;
		delete[] Calibration::sigarr;
		delete[] Calibration::muarr;
		delete[] Calibration::thetaarr;
	}
	delete[] Prem;
	delete[] K;

	objcnt--;
}

double Calibration::CP_FFT(double Strike,double Time,double sig, double m, double th){  
  Beta = log(Strike);
  //double lambda = 2*PI/(N*eta); unused
  C = exp(-Calibration::r*Time);  
  v=0;
  dcmplx *X = (dcmplx *)calloc(Calibration::N,sizeof(dcmplx));  
  dcmplx CFunc,u,omega;

  for(int cnt=0;cnt<Calibration::N;cnt++)
    {
      v=cnt*Calibration::eta;
      u=v-Calibration::i*(Calibration::alpha+1.0);      
      omega = log(1.0-0.5*m*pow(sig,2)-th*m)/m;      
      CFunc=exp(Calibration::i*u*(log(Calibration::S0)+Time*(Calibration::r-Calibration::q+omega))) * pow((1.0-Calibration::i*u*th*m + 0.5*m*pow(sig*u,2)),-Time/m);
      X[cnt] = Calibration::eta*C*exp(-Calibration::i*Beta*v)*CFunc/((Calibration::alpha+Calibration::i*v)*(Calibration::alpha+Calibration::i*v+1.0));      
    }
  X[0]*=0.5;
  
  dcmplx *Y=FFT(X,N);  
  double CP= exp(-Calibration::alpha*Beta)*Y[0].real()/PI;
  free(X);
  free(Y);  
  return CP;
}

//friend function definition
double Calibration::RMS(vector<double> x){    
  double result=0;
  for(int j=0;j<Calibration::readKcnt/Calibration::readTcnt;j++){   
    result+=pow(abs(Prem[j] - CP_FFT(K[j],T,x[0],x[1],x[2])),Calibration::p);
  }  
  return pow(result/(Calibration::readKcnt/Calibration::readTcnt),(1.0/Calibration::p));
}

int Calibration::calibrateVar(){
	double largetemp=1000000;
  	double result=0;

	for(int i=0;i<Calibration::step;i++)
      for(int j=0;j<Calibration::step;j++)
        for(int k=0;k<Calibration::step;k++){
          init[0] = Calibration::sigarr[i];
          init[1] = Calibration::muarr[j];
          init[2] = Calibration::thetaarr[k];          
          result = RMS(init);
          if(result<largetemp){
            largetemp=result;           
            initguess[0] = Calibration::sigarr[i];
            initguess[1] = Calibration::muarr[j];
            initguess[2] = Calibration::thetaarr[k];            
          }
        }
    cout<<"Initial guess "<<initguess[0]<<" "<<initguess[1]<<" "<<initguess[2]<<endl;  
    //printcon( Simplex(RMS,initguess, 1e-8) );    
    //Simplex(RMS,initguess, 1e-8);
    return 0;
}

//friend function definition
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
		Calibration::readTcnt= atof(line1.c_str());

    	convert.clear();
    	getline (ss,line1,' ');
    	getline (ss,line1,' ');       
    	Calibration::readKcnt= atof(line1.c_str());     

    	//convert.clear();
    	getline (ss,line1,' ');
    	getline (ss,line1,' ');

    	Calibration::readTarr = new double[Calibration::readTcnt];
    	Calibration::readKarr = new double[Calibration::readKcnt];
    	Calibration::readParr = new double[Calibration::readKcnt];           
    	Calibration::sigarr   = new double[Calibration::step];
    	Calibration::muarr    = new double[Calibration::step];
    	Calibration::thetaarr = new double[Calibration::step];

    while ( getline (file,line) ){                
      if(linecnt>startread && linecnt<=Calibration::readTcnt+startread){                                            
        Calibration::readTarr[linecnt-startread-1] = atof(line.c_str());  
      }
      else if(linecnt>Calibration::readTcnt+startread+1 && linecnt<=Calibration::readTcnt+Calibration::readKcnt+startread+1){                                   
        Calibration::readKarr[linecnt-startread-Calibration::readTcnt-2] = atof(line.c_str());
      }
      else if(linecnt>Calibration::readTcnt+Calibration::readKcnt+startread+2 && linecnt<=Calibration::readTcnt+Calibration::readKcnt+Calibration::readKcnt+startread+2){                      
        Calibration::readParr[linecnt-startread-Calibration::readTcnt-Calibration::readKcnt-3] = atof(line.c_str());
      }
      linecnt++;
    }    
    Calibration::readflag = true;

//initialize        
    Calibration::sigarr[0]=0.05;	Calibration::sigarr[Calibration::step-1]=0.5;    
    Calibration::muarr[0]=0.05;		Calibration::muarr[Calibration::step-1]=0.75;    
    Calibration::thetaarr[0]=-0.9;	Calibration::thetaarr[Calibration::step-1]=-0.05;

//fill arrays  
  	for(int j=1;j<Calibration::step-1;j++){
    	Calibration::sigarr[j] 		= Calibration::sigarr[0] + j*(Calibration::sigarr[Calibration::step-1] - Calibration::sigarr[0])/(Calibration::step-1);
    	Calibration::muarr[j] 		= Calibration::muarr[0] + j*(Calibration::muarr[Calibration::step-1] - Calibration::muarr[0])/(Calibration::step-1);
    	Calibration::thetaarr[j] 	= Calibration::thetaarr[0] + j*(Calibration::thetaarr[Calibration::step-1] - Calibration::thetaarr[0])/(Calibration::step-1);
  	}

  	}
  	else cout << "Unable to open file"; 
  	file.close();  	
  	return 0;
}