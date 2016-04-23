#include "functions.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <complex>
#include <stdlib.h>

typedef complex<double> dcmplx;
#define PI  3.1415926535897932
dcmplx i(0,1);

using namespace std;

int main(int, char**){

  double S0 = 1800.0;
  double K=1650.0;
  double T = 0.5;  
  double r=0.005;
  double q=0.0135;  

  double sigma = 0.20;
  double theta = -0.15;
  double mu    = 0.17;

  double eta=0.10;
  double alpha=10;
  int n=12;
  double N = pow(2,n);
  double Beta = log(K);
  double lambda = 2*PI/(N*eta);
  double C= exp(-r*T);  
  double v=0;

  dcmplx *X = (dcmplx *)calloc(N,sizeof(dcmplx));
  // dcmplx *Y = (dcmplx *)calloc(N,sizeof(dcmplx));
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
  printf("%g\n",exp(-alpha*Beta)*Y[0].real()/PI);
  free(X);
  free(Y);	
	return 0;
}

