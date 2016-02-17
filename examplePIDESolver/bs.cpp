
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

	double   T=0.25;
	double   S0=1950.0, K=1975.0; 
	double   rfr=0.05;
	double   div=0.025;
	double   sMin = 100.0, sMax = 4100.0;

	int      N=4000;
	int      M=1000;

	Dx = (log(sMax)-log(sMin))/N;
	Dt = T/M;

	L = new double[N];
	D = new double[N];
	U = new double[N];
	W = new double[N+1];
	x = new double[N+1];

	aA = sig*sig*Dt/(2.0*Dx*Dx);
	bB = (rfr-div-0.5*sig*sig)*Dt/(2.0*Dx);

	gettimeofday(&startTime, NULL); 

	// payoff
	for ( i = 0; i <= N; ++i){

		x[i] = log(sMin)+i*Dx;

		if(exp(x[i])<K)
			W[i] = K-exp(x[i]);
		else
			W[i] = 0.0;
	}

	for (i = 1; i <=N-1; ++i){
		if (i==1){
			//L[i] = 0;
			D[i] = 1 + 2.0*aA + rfr*Dt - (aA-bB)*       2.0/(1.0+Dx/2.0);
			U[i] = -(aA+bB)            + (aA-bB)*(1.0-Dx/2)/(1.0+Dx/2.0);
			// Boundary condition
			//W[1] = W[1]+(aA-bB)*(K-exp(x[0]));
			//W[1] = W[1]+(aA-bB)*(K*exp(-rfr*tau_j)-exp(x[0])*exp(-div*tau_j));

		}
		else if (i==N-1){
			L[i] = -(aA-bB)              + (aA+bB)*(1+Dx/2.0)/(1.0-Dx/2.0);
			D[i] = 1.0 + 2.0*aA + rfr*Dt - (aA+bB)*       2.0/(1.0-Dx/2.0);
			//U[i] = 0;
			// Boundary condition
			//W[N-1] = W[N-1]+0.0;
		}
		else{
			L[i] = -(aA-bB);
			D[i] =  1 + 2.0*aA + rfr*Dt;
			U[i] = -(aA+bB);
		}
	}

	for (j = M-1; j >= 0; --j) {

		//cout << j << endl;

		// A w_{k+1} = w_{k}
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