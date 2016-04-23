#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <complex>
#include <stdlib.h>
#include <vector>

typedef complex<double> dcmplx;
#define PI  3.1415926535897932
dcmplx i(0,1);

using namespace std;

double CP_FFT(double K,double T,double sigma,double mu,double theta);
double RMS(vector<double> x);

int main(int argc, char** argv){
  
  struct timespec etime,stime;
  clock_gettime(CLOCK_MONOTONIC,&stime);
  int N=10;
  double sigmaMIN=0.11,sigmaMAX=0.13;
  double muMIN=0.1,muMAX=0.3;
  double thetaMIN=-0.15,thetaMAX=-0.13;
  double *s = new double[N+1];
  double *m = new double[N+1];
  double *t = new double[N+1];
  for(int i=0;i<=N;i++){
    s[i]=sigmaMIN + i*(sigmaMAX-sigmaMIN)/N;
    m[i]=muMIN + i*(muMAX-muMIN)/N;
    t[i]=thetaMIN + i*(thetaMAX-thetaMIN)/N;        
  }
  vector<double> init(3,0.0);
  vector<double> tempvec(3,0.0);

  /*init.push_back(0.05);
  init.push_back(0.05);
  init.push_back(-0.9);*/

  
  double temp=1000000,RMStemp=0;
  
  for(int i=0;i<=N;i++)
    for(int j=0;j<=N;j++)
      for(int k=0;k<=N;k++){
        init[0]=s[i];
        init[1]=m[j];
        init[2]=t[k];
        //cout<<init[0]<<" "<<init[1]<<" "<<init[2]<<" ";        
        RMStemp=RMS(init);
        //cout<<RMStemp<<endl;
        if(RMStemp<temp){
          temp=RMStemp;
          tempvec[0]=s[i];
          tempvec[1]=m[j];
          tempvec[2]=t[k];          
        }
      }   
  
  delete [] s;
  delete [] m;
  delete [] t;
  cout<<tempvec[0]<<" "<<tempvec[1]<<" "<<tempvec[2]<<" "<<endl;
  clock_gettime(CLOCK_MONOTONIC,&etime);
  cout<<(etime.tv_sec-stime.tv_sec)*1000 +(etime.tv_nsec-stime.tv_nsec)/1000000<<endl;  
	return 0;
}

double CP_FFT(double K,double T,double sigma,double mu,double theta){
  double S0 = 100.0;
  //double K=1650.0;
  //double T = 0.5;  
  double r=0.10;
  double q=0.0;  

  //double sigma = 0.20;
  //double theta = -0.15;
  //double mu    = 0.17;

  double eta=0.10;
  double alpha=0.5;
  int n=12;
  double N = pow(2,n);
  double Beta = log(K);
  double lambda = 2*PI/(N*eta);
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
  //printf("%g\n",exp(-alpha*Beta)*Y[0].real()/PI);  
  double CP= exp(-alpha*Beta)*Y[0].real()/PI;
  free(X);
  free(Y);  
  return CP;
}

double RMS(vector<double> x){
  //double T =0.25;
  //double K[] ={95,92,88,85,81};
  //double Prem[] = {5.8351,4.9432,3.9327,3.2925,2.5747};
  double T =1.0/12.0;
  double K[] ={90,90,90,90,90};
  double Prem[] = {10.8288,10.8288,10.8288,10.8288,10.8288};
  int n=5;
  double result;

  for(int i=0;i<n;i++){    
    result+=pow(abs(Prem[i] - CP_FFT(K[i],T,x[0],x[1],x[2])),2);
  }
  return sqrt(result/n);
}