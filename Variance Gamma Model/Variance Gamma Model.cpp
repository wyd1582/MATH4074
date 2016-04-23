// This program uses S&P500 call prices (as proxied by the ETF SPY)
// to obtain parameter estimates for the Variance Gamma Model of Madan, Carr, and Chang (1998)
// By Fabrice Douglas Rouah, FRouah.com and Volopta.com


//#include "stdafx.h"
#include <complex>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "VGFiles.h"
#include "RMSE.h"
#include "NelderMead.h"

// Objective function
double RMSE(vector<double>,RMSEinputs);

// Main program
int main() {

	// Name the classes
	CNelderMead NM;
	CVGFiles VG;

	// Open the SPY returns for historical volatility estimate for Black Scholes
	ifstream inReturns;
	inReturns.open("SPY_Returns.txt");
	vector<double> Ret(0, 0.0);				// SPY return
	double n1;
	int j=0;
	while (!inReturns.eof()) {
		inReturns >> n1;
		Ret.push_back(n1);
	j++ ;
	}
	inReturns.close();
	double vol = NM.stdev(Ret)*sqrt(252.0);

	// Open the option prices for SPY for Variance Gamma estimation
	ifstream inPrices;
	inPrices.open("SPY_Calls.txt");
	vector<double> K(0, 0.0);				// Strike
	vector<double> MPrice(0, 0.0);			// Market Price
	double m1, m2;
	int i=0;
	while (!inPrices.eof()) {
		inPrices >> m1 >> m2 ;
		K.push_back(m1);
		MPrice.push_back(m2);
	i++ ;
	}
	int n = K.size();

	// Pass the inputted data the RMSEinputs structure
	RMSEinputs rmsein;
	rmsein.K = K;
	rmsein.MPrice = MPrice;

	// Hard code the additional inputs
	rmsein.S = 90.692;				// Spot Price
	rmsein.T = 0.194387;			// Maturity in Years
	rmsein.r = 0.0179;				// Interest Rate
	double q = 0.0;					// Dividend Yield

	// Settings for Nelder Mead Algorithm
	NMsettings nmset;
  	nmset.N = 3;						// Number of Variance Gamma parameters
	nmset.MaxIters = 2000;				// Maximum number of iterations
	nmset.tolerance = 1.0e-12;			// Tolerance on best and worst function values
	nmset.RMSEinp = rmsein;				// Settings for the RMSE function

	// Starting parameter values
	double alpha = 0.0005;
	double sigma = 0.3771;
	double v     = 0.1995;

	// VG parameter starting values (vertices) in vector form
	int N = nmset.N;
	double a = -0.1;
	double b =  0.1;
	vector<vector<double> > start(N, vector<double>(N+1));
	start[0][0] = alpha+VG.U(a,b);	start[0][1] = alpha+VG.U(a,b);	start[0][2] = alpha+VG.U(a,b);	start[0][3] = alpha+VG.U(a,b);	    // alpha
	start[1][0] = sigma+VG.U(a,b);	start[1][1] = sigma+VG.U(a,b);	start[1][2] = sigma+VG.U(a,b);	start[1][3] = sigma+VG.U(a,b);		// gamma
	start[2][0] = v+VG.U(a,b);		start[2][1] = v+VG.U(a,b);		start[2][2] = v+VG.U(a,b);		start[2][3] = v+VG.U(a,b);		// v

	// Run Nelder Mead minimization to obtain parameter estimates
	CRMSE crm;
	vector<double> B = NM.NelderMeadFunction(RMSE,nmset,start);

	// Output and format the results
	cout << "----------------------------------------" << endl;
	cout << "OPTION DESCRIPTION      " << endl;
	cout << "----------------------------------------" << endl;
	cout << "Asset spot price      = " << rmsein.S   << endl;
	cout << "Time to maturity      = " << rmsein.T   << " years" << endl;
	cout << "Yearly risk free rate = " << rmsein.r   << " or " << rmsein.r*100   << "%" << endl;
	cout << "Yearly historical vol = " << vol        << " or " << vol*100 << "%" << endl;
	cout << "----------------------------------------" << endl;
	cout << "NELDER MEAD MINIMIZATION RESULTS" << endl;
	cout << "----------------------------------------" << endl;
	cout << "Value of Objective Function = " << B[N] << endl;
	cout << "Number of Iterations = " << B[N+1] << endl;
	cout << "----------------------------------------" << endl;
	cout << "VARIANCE GAMMA PARAMETER ESTIMATES" << endl;
	cout << "----------------------------------------" << endl;
	cout << "alpha  = " << B[0] << endl;
	cout << "sigma  = " << B[1] << endl;
	cout << "v      = " << B[2] << endl;
	cout << "----------------------------------------" << endl;
	vector<double> VC(n);
	vector<double> BSC(n);
	cout << "STRIKE   MARKET PRICE   VG-PRICE  BS-PRICE" << endl;
	cout << "----------------------------------------" << endl;
	for (int i=0; i<=n-1; i++) {
		VC[i]  = VG.VGCall(B[0],B[1],B[2],rmsein.S,rmsein.K[i],rmsein.r,rmsein.T);
		BSC[i] = VG.BSCall(rmsein.S,rmsein.K[i],rmsein.r,q,vol,rmsein.T);
		cout << K[i]      << "      " 
			 << MPrice[i] << "      " 
			 << VC[i]     << "      "
			 << BSC[i]    << endl;
	}
	cout << "----------------------------------------" << endl;

}

// RMSE objective function
double RMSE(vector<double> B,RMSEinputs rmsein) {
	CVGFiles VG;
	int N = rmsein.K.size();
	vector<double> VGPrice(N,0.0);
	double Sum = 0.0;
	// Penalty for negative parameter values
	if ( (B[1]<0.0) || (B[2]<0.0) )
		return 1.0e100;
    else {
		// Create the loss function
		for (int i=0; i<=N-1; i++)	{
			VGPrice[i] =  VG.VGCall(B[0],B[1],B[2],rmsein.S,rmsein.K[i],rmsein.r,rmsein.T);
			// Sum +=  pow( (rmsein.MPrice[i] - VGPrice[i])/rmsein.MPrice[i], 2.0);
			// Sum +=  pow((log(rmsein.MPrice[i]) - log(VGPrice[i])), 2.0);
			Sum +=  pow(rmsein.MPrice[i] - VGPrice[i], 2.0);
		}
	return Sum;
	}
}
