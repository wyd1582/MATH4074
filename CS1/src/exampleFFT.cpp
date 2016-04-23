#include "functions.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <complex>
#include <stdlib.h>

typedef complex<double> dcmplx;
#define PI  3.1415926535897932

using namespace std;

    //declare input variables
    double S0 = 1800;// spot price
    float T = 0.5;// Maturity in years
    double sigma = 0.3; //volatility
    double r = 0.005; //risk free rate
    double q = .0175;//continuous dividend rate
    double K = 2100;//strike price
    
    //FFT specific variables
    double eta = 0.25;
    double alpha = 1.5;
    double n = 12;
    double N = pow(2,n);
    double Beta = log(K);
    double lambda = 2*PI/(N * eta);
    double v=0;
    double C = exp(-r * T);    
    
    dcmplx *X = (dcmplx*)calloc(N,sizeof(dcmplx)); //input into FFT
    double *Callprice = (double*)calloc(N,sizeof(double));
    dcmplx i(0,1);//imaginary value i
    
    dcmplx characFunc(dcmplx u){
        //return exp(i*u*(log(S0)+(r-q-0.5*pow(sigma,2))*T)-0.5*T*pow(sigma*u,2) );
        return exp(i*u*(log(S0)+T*(r-q-0.5*pow(sigma,2)))-0.5*T*pow(sigma*u,2));
    }
    

int main(int, char**) {
    
    //populate X vector
    for(int cnt=0;cnt<N;cnt++){
        v = cnt * eta;
        X[cnt] = (eta * C)/((alpha + i*v)*(alpha + i*v + 1.0))*exp(-i*Beta*v)*characFunc(v-i*(alpha + 1.0));	

    }
    X[0]*=0.5; //for first element only
    
    // FFT
    dcmplx *Y = FFT(X, N);//output from FFT
    
    //populate Callprice vector
    for(int cnt=0;cnt<N;cnt++){
        Callprice[cnt] = exp(-alpha*(Beta+lambda*cnt))*Y[cnt].real()/PI;        
    }
    
    cout<<Callprice[0];
    free(X);
    free(Y);
    free(Callprice);
	

	return 0;
}

