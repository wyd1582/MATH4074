#include "functions.h"
#include <sys/time.h> 
#include <math.h>
#include <iostream>

using namespace std;

int main(int argc,char** argv)
{
	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;

	gettimeofday(&startTime, NULL); 		

	double   sig=0.2;
	double	 v = 0.17;
	double   theta = -0.15;
	double   T=0.5;
	double   S0=1800.0, K=1650.0; 
	double   rfr=0.005;
	double   div=0.0135;

	long idum = -12761;	
	double z=0;
	double g=0;
	double payoff=0;
	int nSimulatedPath=500000,nTimeSteps=100;
	double h = T/nTimeSteps;
	double omega=log(1-theta*v-v*sig*sig*0.5)/v;
	double x=0;
	double *S=new double[nTimeSteps+1];
	S[0]=S0;

	for(int j=1;j<=nSimulatedPath;j++)
	{
		for (int i=1; i <= nTimeSteps; i++)
		{
			z=invNormal(ran2_mod(&idum));
			g=gamrand(h/v,v,&idum);
			x=theta*g+sig*z*sqrt(g);
			S[i]=exp(log(S[i-1])+h*(rfr-div)+omega*h+x);
			//S[i]=S[i-1]*exp(h*(rfr-div+omega)+x);
		}
		//exp(S[nTimeSteps])<K ? payoff+=K-exp(S[nTimeSteps]) : 0;
		(S[nTimeSteps] < K) ? payoff+=K-S[nTimeSteps] : 0;
	}

	delete[] S;
	cout<<exp(-rfr*T)*payoff/nSimulatedPath<<endl;

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 
	cout << "Time elapsed was: " << mtime << " (milliseconds)" << endl;
	
	return 0;
}
