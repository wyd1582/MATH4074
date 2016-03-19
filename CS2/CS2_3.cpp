#include <math.h>
#include <sys/time.h>
#include "expint.hpp"
#include "tridiagSolver.hpp"

int main(int argc,char **argv){
	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;
	double   *L, *D, *U, *W,*Wadj, *x;
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
	Wadj = new double[N+1];
	x = new double[N+1];	

	aA = sigma_squared * Dt/(2 * pow(Dx,2)); //first part of Bl or Bu
	bB = (rfr-div+omega-0.5*sigma_squared)*Dt/(2.0*Dx); //second part of Bl or Bu

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
			L[i] = -(aA-bB);
			//D[i] =  1 + rfr*Dt + 2*aA + Dt/v*(expint(Dx*lp*(N-i)));
            //D[i] =  1 + rfr*Dt + 2*aA;
            D[i] =  1 + rfr*Dt + 2*aA + Dt/v*(expint(Dx*lp*(N-i))+expint(i*Dx*ln));
            U[i] = -(aA+bB);
            if(i==1){
                L[i]=0;
            }
            if(i==N-1){
                U[i]=0;
            }		
	}
	double *expln, *explp, *expintln, *expintlp;
	expln = new double[N];
	explp = new double[N];
	expintln = new double[N];
	expintlp = new double[N];
	for (int k = 1; k <= N - 1; k++)
	{
		expln[k] = exp(-k*Dx*ln);
		explp[k] = exp(-k*Dx*lp);
		expintln[k] = expint(k*ln*Dx);
		expintlp[k] = expint(k*lp*Dx);
	}

	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 
	cout << "Time elapsed was: " << mtime << " (milliseconds)" << endl;

    for (j = M-1; j >= 0; --j) {    	
    //populate values for right hand side(4 Integral terms)
    	for (i=1;i<=N-1;i++){
    		double Integral1 = 0;
			double Integral2 = 0;
			double Integral3 = 0;
			double Integral4 = 0;
        	for(k=1;k<=N-i-1;k++){
            	Integral1+=Dt/v*((W[i+k]-W[i]-k*(W[i+k+1]-W[i+k]))*(expintlp[k]-expintlp[k+1]) + 
                	                1/Dx*(W[i+k+1]-W[i+k])*(exp(-lp*k*Dx)-exp(-lp*(k+1)*Dx)));            
        	}
        	Integral2=-Dt/v*expintlp[k]*W[i];
        	Integral3=Dt/v*((K-W[i])*expintln[k]-exp(x[i])*expintln[k+1]);
        	for(k=1;k<=i-1;k++){
            	Integral4+=Dt/v*(((W[i-k]-W[i])+k*(W[i-k-1]-W[i-k]))*(explp[k]-explp[k+1])+
                	                1/Dx*(W[i-k-1]-W[i-k])*(exp(-ln*k*Dx)-exp(-ln*(k+1)*Dx)));            
        	}
        	Wadj[i]=W[i]+Integral1+Integral2+Integral3+Integral4;             
    	}
    	gettimeofday(&endTime, NULL); 
		seconds = endTime.tv_sec - startTime.tv_sec; 
		useconds = endTime.tv_usec - startTime.tv_usec; 
		mtime = ((seconds) * 1000 + useconds/1000.0); 
		cout << "Time elapsed was: " << mtime << " (milliseconds)" << endl;

    	tridiagSolver(L, D, U, Wadj, N-1);    	
    				
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

