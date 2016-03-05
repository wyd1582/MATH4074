#include <math.h>
#include "tridiagSolver.cpp"
#include "functions.h"

main(){

	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;

	double   *L, *D, *U, *W, *x;
	double   aA, bB;
	double   ps0;
	double   tau_j;
	double   Dx, Dt;
	int      i, j, k, ir;

	double   sig=0.2;
	double	 v = 0.17;
	double   theta = -0.15;
	double   T=0.5;
	double   S0=1800.0, K=1650.0; 
	double   rfr=0.005;
	double   div=0.0135;
	double   sMin = 1000.0, sMax = 2000.0;

	double   lp = pow((pow(theta, 2) / pow(sig, 4) + 2 / (pow(sig, 2)*v)), 0.5) - theta / pow(sig, 2);
	double   ln = pow((pow(theta, 2) / pow(sig, 4) + 2 / (pow(sig, 2)*v)), 0.5) + theta / pow(sig, 2);

	int      N=4000;
	int      M=1000;

	Dx = (log(sMax)-log(sMin))/N;
	Dt = T/M;

	L = new double[N];
	D = new double[N];
	U = new double[N];
	W = new double[N+1];
	x = new double[N+1];

	aA = sigma_squared(Dx,lp,ln,v) * Dt/(2 * pow(Dx,2)); //first part of Bl/Bu
	bB = (rfr-div+omega(Dx,lp,ln,v)-0.5*pow(sigma_squared(Dx, lp, ln, v),2))*Dt/(2.0*Dx); //second part of Bl/Bu

	gettimeofday(&startTime, NULL); 

	// payoff
	for ( i = 0; i <= N; ++i){

		x[i] = log(sMin)+i*Dx;

		if(exp(x[i])<K)
			W[i] = K-exp(x[i]);
		else
			W[i] = 0.0;
	}

	//set up diagonals L,D,U
	for (i = 0; i <=N-1; ++i)
	{		
			L[i] = -(aA-bB);
			D[i] =  1 + rfr*Dt + 2*aA + Dt/v*(expint(Dx*lp*(N-i)));
			U[i] = -(aA+bB);
			switch (i)
			{
			case 0:
				L[i] = 0;
				break;
			case N-1:
				U[i] = 0;			
				break;
			}
	}

	for (j = M-1; j >= 0; --j) {
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