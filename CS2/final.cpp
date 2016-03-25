#include <math.h>
#include <sys/time.h>
#include "expint.hpp"
#include "tridiagSolver.hpp"

int main(int argc,char **argv){
	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;
	double   *L, *D, *U, *W, *x;
	double   aA, bB;
	double   ps0;
	double   Dx, Dt;
	int      i, j,k, ir=0;  

	double   sig=0.2;
	double   T=0.5;
	double   S0=1800.0, K=1650.0; 
	double   rfr=0.005;
	double   div=0.0135;
	double 	 theta=-0.15;
	double 	 v=0.17;
	
	double   sMin = 1000.0, sMax = 2000.0;
	int      N=4000;
	int      M=1000;

	double 		g[6][N+1];

	Dx = (log(sMax)-log(sMin))/N;
	Dt = T/M;
	double lp = sqrt(pow(theta,2)/pow(sig,4)+2/(v*pow(sig,2)))-theta/pow(sig,2);
	double ln = sqrt(pow(theta,2)/pow(sig,4)+2/(v*pow(sig,2)))+theta/pow(sig,2);
	double sigma_squared = 1/v * ((1/pow(lp,2)*(1-exp(-lp*Dx)*(1+lp*Dx)))+(1/pow(ln,2)*(1-exp(-ln*Dx)*(1+ln*Dx))));
	double omega = 1/v *((expint(lp*Dx)-expint(Dx*(lp-1)))+(expint(ln*Dx)-expint(Dx*(ln-1))));

	L = new double[N];
	D = new double[N];
	U = new double[N];
	W = new double[N+1];
	x = new double[N+1];	
	double *w_adjusted = new double[N+1];

	aA = sigma_squared * Dt/(2 * pow(Dx,2)); //first part of Bl or Bu
	bB = (rfr-div+omega-0.5*sigma_squared)*Dt/(2.0*Dx); //second part of Bl or Bu

	gettimeofday(&startTime, NULL); 
	// populate payoff and 6 precalculated vectors

	for ( i = 0; i <= N; ++i){
		x[i] = log(sMin)+i*Dx;

		if(exp(x[i])<K)
			W[i] = K-exp(x[i]);
		else
			W[i] = 0.0;

		g[0][i]=exp(k*Dx*ln);
		g[1][i]=exp(k*Dx*lp);
		g[2][i]=expint(ln*k*Dx);
		g[3][i]=expint(lp*k*Dx);
		g[4][i]=expint((ln+1)*k*Dx);
		g[5][i]=expint((lp+1)*k*Dx);
	}

for (i = 1; i <=N-1; ++i){
		if (i==1){
			D[i] = 1 + 2.0*aA + rfr*Dt - (aA-bB)*       2.0/(1.0+Dx/2.0);
			U[i] = -(aA+bB)            + (aA-bB)*(1.0-Dx/2)/(1.0+Dx/2.0);
			
		}
		else if (i==N-1){
			L[i] = -(aA-bB)              + (aA+bB)*(1+Dx/2.0)/(1.0-Dx/2.0);
			D[i] = 1.0 + 2.0*aA + rfr*Dt - (aA+bB)*       2.0/(1.0-Dx/2.0);
			
		}
		else{
			L[i] = -(aA-bB);
			D[i] =  1 + 2.0*aA + rfr*Dt + Dt/v*(g[2][i]+g[3][N-i]);
			U[i] = -(aA+bB);
		}
	}


    for (j = M-1; j >= 0; --j) {
    	
    	for (i = 1; i <=N-1; ++i)
    	{
    		double rhs=0;
    		for (k = 1; k <= i-1; ++k)
    			{
    				rhs+=(W[i-k]-W[i]-k*(W[i-k-1]-W[i-k]))*(g[2][k]-g[4][k+1]);
    				rhs+=1/(ln*Dx)*(W[i-k-1]-W[i-k])*(g[0][k]-g[0][k+1]);
    			}
			for (k = 1; k <= N-i-1; ++k)
    			{
    				rhs+=(W[i+k]-W[i]-k*(W[i+k+1]-W[i+k]))*(g[3][k]-g[5][k+1]);
    				rhs+=1/(lp*Dx)*(W[i+k+1]-W[i+k])*(g[1][k]-g[1][k+1]);
    			}
			rhs+=K*g[2][i]-exp(x[i])*g[4][i];
			W[i]+=rhs;
    	}
		tridiagSolver(L, D, U, W, N-1);

	}

	//
	for(i = 0; i <= N-1; ++i){
		if(x[i]>log(S0)){
			ir=i;
			break;
		}
	}
	
	ps0 = W[ir-1] + ((W[ir]-W[ir-1])/Dx)*(log(S0)-x[ir-1]);

	cout << "Stock Price " << S0  << endl;
	cout << "Put Value   " << ps0 << "\n" << endl;

	delete [] L;
	delete [] D;
	delete [] U;
	delete [] W;
	delete [] x;

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 
	cout << "Time elapsed was: " << mtime << " (milliseconds)" << endl;

	return 0;
}

