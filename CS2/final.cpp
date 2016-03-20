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
	double *Integral1 = new double[N+1];
	double *Integral2 = new double[N+1];
	double *Integral3 = new double[N+1];
	double *Integral4 = new double[N+1];
	double *w_adjusted = new double[N+1];

	aA = sigma_squared * Dt/(2 * pow(Dx,2)); //first part of Bl or Bu
	bB = (rfr-div+omega-0.5*sigma_squared)*Dt/(2.0*Dx); //second part of Bl or Bu

	gettimeofday(&startTime, NULL); 
	// payoff
	for ( i = 0; i <= N; ++i){
        Integral1[i]=0.0; //set all values to zero
        Integral2[i]=0.0; //set all values to zero
        Integral3[i]=0.0; //set all values to zero
        Integral4[i]=0.0; //set all values to zero

		x[i] = log(sMin)+i*Dx;

		if(exp(x[i])<K)
			W[i] = K-exp(x[i]);
		else
			W[i] = 0.0;
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
			D[i] =  1 + 2.0*aA + rfr*Dt;
			U[i] = -(aA+bB);
		}
	}
    for (j = M-1; j >= 0; --j) {
        
    //populate values for right hand side(4 Integral terms)
    for (i=1;i<=N-1;i++){

			double term1, term2, term3, term4;
			term1 = 0;
			term2 = 0;
			term3 = 0;
			term4 = 0;
			for (int k = 1; k <= i - 1; k++)
			{
				term1 +=(W[i - k] - W[i] - k*(W[i - k - 1] - W[i - k]))*(expint(k*lp*Dx) - expint((k+1)*lp*Dx));
				term2 +((W[i - k - 1] - W[i - k]) / (ln*Dx))*(exp(-k*Dx*ln) - exp(-Dx*ln*(k+1)));
			}
			for (int k = 1; k <= N - i - 1; k++)
			{
				term3 +=(W[i + k] - W[i] - k*(W[i + k + 1] - W[i + k]))*(expint(k*lp*Dx) - expint((k+1)*lp*Dx));
				term4 +=((W[i + k + 1] - W[i + k]) / (lp*Dx))*(exp(-k*Dx*ln) - exp(-Dx*ln*(k+1)));
			}
		       w_adjusted[i] = W[i] + (Dt / v)*(term1 + term2 + term3 + term4);
    }
	tridiagSolver(L, D, U, w_adjusted, N-1);
 	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 
	cout << "Time elapsed was: " << mtime << " (milliseconds)" << endl;

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
	delete [] Integral1;
	delete [] Integral2;
	delete [] Integral3;
	delete [] Integral4;

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 
	cout << "Time elapsed was: " << mtime << " (milliseconds)" << endl;

	return 0;
}
