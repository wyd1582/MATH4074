#include <math.h>
#include <sys/time.h> 
#include "expint.hpp"
#include "tridiagSolver.hpp"

int main(){
	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;
	double   *L, *D, *U, *W, *x; //
    double   *Integral1,*Integral2,*Integral3,*Integral4; //variables for Right Hand Side
	double   aA, bB; //part1 and part2 of Lower and Upper diagonals
	double   ps0;
	//double   tau_j;	
	int      i, j, k, ir; //counters in for loops

	double   sig=0.2;
	double	 v = 0.17;
	double   theta = -0.15;
	double   T=0.5;
	double   S0=1800.0, K=1650.0; 
	double   rfr=0.005;
	double   div=0.0135;
	double   sMin = 1000.0, sMax = 2000.0;

	double   lp = sqrt((pow(theta, 2) / pow(sig, 4) + 2 / (pow(sig, 2)*v))) - theta / pow(sig, 2);//lambda p
	double   ln = sqrt((pow(theta, 2) / pow(sig, 4) + 2 / (pow(sig, 2)*v))) + theta / pow(sig, 2);//lambda n

	int      N=4000;
	int      M=1000;	
	
    double   Dx = (log(sMax)-log(sMin))/N;
	double   Dt = T/M;
    double   sigma_squared = 1 / (v*pow(lp, 2))*(1 - (1 + lp*Dx)*exp(-lp*Dx)) +
	                       1 / (v*pow(ln, 2))*(1 - (1 + ln*Dx)*exp(-ln*Dx));
    double   omega = (1 / v)*(expint(lp*Dx) - expint(Dx*(lp - 1)))+
	                (1 / v)*(expint(ln*Dx) - expint(Dx*(ln + 1)));	    

	L = new double[N];
	D = new double[N];
	U = new double[N];
	W = new double[N+1];
	x = new double[N+1];
    Integral1=new double[N+1];
    Integral2=new double[N+1];
    Integral3=new double[N+1];
    Integral4=new double[N+1];

	aA = sigma_squared * Dt/(2 * pow(Dx,2)); //first part of Bl or Bu
	bB = (rfr-div+omega-0.5*sigma_squared)*Dt/(2.0*Dx); //second part of Bl or Bu

	gettimeofday(&startTime, NULL); 

	// payoff
	for ( i = 0; i <= N; ++i){

		x[i] = log(sMin)+i*Dx;
        Integral1[i]=0.0; //set all values to zero
        Integral2[i]=0.0; //set all values to zero
        Integral3[i]=0.0; //set all values to zero
        Integral4[i]=0.0; //set all values to zero

		if(exp(x[i])<K)
			W[i] = K-exp(x[i]);
		else
			W[i] = 0.0;
	}

	//set up diagonals L,D,U
	for (i = 0; i <=N-1; ++i)
	{		
			L[i] = -(aA-bB);
			D[i] =  1 + rfr*Dt + 2*aA + Dt/v*(expint(Dx*lp*(N-i)));                                                                                                                                                                                                                                         U[i] = -(aA+bB);
            
			if (i==0)
				L[i] = 0.0;
				
			if(i==N-1)
				U[i] = 0.0;							
			
	}    
    
    //populate values for right hand side(4 Integral terms)
    for (i=1;i<=N-1;i++){
        for(k=1;k<=N-i-1;k++){
            Integral1[i]+=Dt/v*((W[i+k]-W[i]-k*(W[i+k+1]-W[i+k]))*(expint(k*lp*Dx)-expint((k+1)*lp*Dx)) + 
                                1/Dx*(W[i+k+1]-W[i+k])*(exp(-lp*k*Dx)-exp(-lp*(k+1)*Dx)));            
        }
        Integral2[i]=-Dt/v*expint((N-i)*lp*Dx)*W[i];
        Integral3[i]=Dt/v*((K-W[i])*expint(i*Dx*ln)-exp(x[i])*expint(i*Dx*(ln+1)));
        for(k=1;k<=i-1;k++){
            Integral4[i]+=Dt/v*(((W[i-k]-W[i])+k*(W[i-k-1]-W[i-k]))*(expint(k*lp*Dx)-expint((k+1)*lp*Dx))+
                                1/Dx*(W[i-k-1]-W[i-k])*(exp(-ln*k*Dx)-exp(-ln*(k+1)*Dx)));            
        }       
    }  
    
    //add W and right hand side
    for ( i = 0; i <= N; ++i){
        W[i]+=Integral1[i]+Integral2[i]+Integral3[i]+Integral4[i];
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
