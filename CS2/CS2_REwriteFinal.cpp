#include <math.h>
#include <sys/time.h>
#include <time.h>
#include "expint.hpp"
#include "tridiagSolver.hpp"

int main(int argc,char **argv){

	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;	
	double   *L, *D, *U, *W,*Wadj, *x;
	double   aA, bB;
	double   ps0;
	double   tau_j;	
	double 	 rhs=0;
	int      i, j, k, ir;

	double   sig=0.2;
	double   T=0.5;
	double   S0=1800.0, K=1650.0; 
	double   rfr=0.005;
	double   div=0.0135;
	double   sMin = 100.0, sMax = 4100.0;
	double   mu=0.17,theta=-0.15;

	int      N=4000;
	int      M=1000;

	double   Dx = (log(sMax)-log(sMin))/N;
	double   Dt = T/M;
	double   lp = sqrt((pow(theta, 2) / pow(sig, 4) + 2 / (pow(sig, 2)*mu))) - theta / pow(sig, 2);//lambda p
	double   ln = sqrt((pow(theta, 2) / pow(sig, 4) + 2 / (pow(sig, 2)*mu))) + theta / pow(sig, 2);//lambda n

	L = new double[N];
	D = new double[N];
	U = new double[N];
	W = new double[N+1];
	Wadj = new double[N+1];
	x = new double[N+1];
	double** g = new double*[6];
	for (int i = 0; i < 6; ++i)
	{
		g[i]= new double[N+1];
	}

	double   sig2_Dx = 1/(mu*lp*lp) *(1-exp(-lp*Dx)*(1+lp*Dx))+1/(mu*ln*ln) *(1-exp(-ln*Dx)*(1+ln*Dx));	
	double   omega_Dx = 1/mu*(expint(lp*Dx)-expint(Dx*(lp-1)))+1/mu*(expint(ln*Dx)-expint(Dx*(ln+1)));	
	aA = sig2_Dx*Dt/(2.0*Dx*Dx);
	bB = (rfr-div+ omega_Dx-0.5*sig2_Dx)*Dt/(2.0*Dx);

	gettimeofday(&startTime, NULL); 

	// payoff
	for ( i = 0; i <= N; ++i){

		x[i] = log(sMin)+i*Dx;

		if(exp(x[i])<K)
			Wadj[i]=W[i] = K-exp(x[i]);
		else
			Wadj[i]=W[i] = 0.0;
		if (i>=1)
		{
			g[0][i] = exp(-i*ln*Dx);
			g[1][i] = exp(-i*lp*Dx);
			g[2][i] = expint(i*ln*Dx);
			g[3][i] = expint(i*lp*Dx);
			g[4][i] = expint(i*(ln+1)*Dx);
			g[5][i] = expint(i*(lp-1)*Dx);
		}		

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
			D[i] =  1 + 2.0*aA + rfr*Dt + Dt/mu*(g[2][i]-g[3][N-i]);
			U[i] = -(aA+bB);
		}
	}


	for (j = M-1; j >= 0; --j) {
		
		for (int i = 1; i < N; ++i)
		{
			rhs=0;
			for (int k = 1; k <= i-1; ++k)
			{
				rhs+=(W[i-k]-W[i]-k*(W[i-k-1]-W[i-k]))*(g[2][k]-g[2][k+1])+(W[i-k-1]-W[i-k])/(ln*Dx)*(g[0][k]-g[0][k+1]);
			}
			for (int k = 1; k <= N-i-1; ++k)
			{
				rhs+=(W[i+k]-W[i]-k*(W[i+k+1]-W[i+k]))*(g[3][k]-g[3][k+1])+(W[i+k+1]-W[i+k])/(lp*Dx)*(g[1][k]-g[1][k+1]);
			}
			rhs+=K*g[2][i]-exp(x[i])*g[4][i];
			Wadj[i]=W[i]+Dt/mu*rhs;
		}

		tridiagSolver(L, D, U, Wadj, N-1);
		for (int i = 0; i <=N; ++i)
		{
			W[i]=Wadj[i];
		}

	}

	//
	for(i = 0; i <= N-1; ++i){
		if(x[i]>log(S0)){
			ir=i;
			break;
		}
	}

	ps0 = Wadj[ir-1] + ((Wadj[ir]-Wadj[ir-1])/Dx)*(log(S0)-x[ir-1]);


	cout << "Stock Price " << S0  << endl;
	cout << "Put Value   " << ps0 << "\n" << endl;

	delete [] L;
	delete [] D;
	delete [] U;
	delete [] W;
	delete [] x;	
	for (int i = 0; i < 6; ++i)
	{
		delete [] g[i];
	}
	delete [] g;

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 
	cout << "Time elapsed was: " << mtime << " (milliseconds)" << endl;
	return 0;
}
