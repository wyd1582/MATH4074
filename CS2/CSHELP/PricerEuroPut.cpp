#include "stdafx.h"
#include "PricerEuroPut.h"
#include "functions.h"
#include <stdexcept>
#include <minmax.h>
#include <iostream>

using namespace std;




PricerEuroPut::PricerEuroPut(double theta, double sigma, double Y, double mu)
{
	this->mu = mu;
	this->Y = Y;
	this->vol = sigma;
	lambda_p = sqrt(pow(theta, 2) / pow(sigma, 4) + 2 / (pow(sigma, 2)*mu)) - theta / pow(sigma, 2);
	lambda_n = sqrt(pow(theta, 2) / pow(sigma, 4) + 2 / (pow(sigma, 2)*mu)) + theta / pow(sigma, 2);	
}


//Calculate the price of a put
double PricerEuroPut::calculate(double mat, double r, double q,  int nb_ite_s,  int nb_ite_t, double s, double strike, double smin, double smax)
{
	double Dx = (log(smax) - log(smin)) / nb_ite_s;
	double Dt = mat / nb_ite_t;
	double* L = new double[nb_ite_s];
	double* D = new double[nb_ite_s];
	double* U = new double[nb_ite_s];
	double* W = new double[nb_ite_s+1];
	double* W_prev = new double[nb_ite_s + 1]; //Used to be sure we don't mix old and new values of W
	double* X = new double[nb_ite_s+1];
	double ** calc_vec = fill_6vectors(nb_ite_s, Dx);
	int ir;
	double price_option = -1.0;
	double Bu = cBu(Dx, Dt, r, q);
	double Bl = cBl(Dx, Dt, r, q);
	double te = sigma2(Dx);
	double tee = w(Dx);
	

	// payoff
	for (int i = 0; i <= nb_ite_s; ++i) {
		X[i] = log(smin) + i*Dx;
		double test = exp(X[i]);
		if (exp(X[i]) < strike)
			W[i] = strike - exp(X[i]); 
		else
			W[i] = 0.0;
	}
	memcpy(W_prev, W, (nb_ite_s + 1)*sizeof(double));


	for (int j = nb_ite_t - 1; j >= 0; --j) {
		for (int k = 1; k <= nb_ite_s - 1; ++k) {
			if (k == 1) {//Boundary Condition
				L[k] = 0;          
				D[k] = -2 * Bl / (1 + Dx / 2) + 1 + r * Dt + Bl + Bu + (Dt / mu)*(calc_vec[2][k - 1] + calc_vec[2][nb_ite_s - k - 1]);
				U[k] = -Bu + (1-Dx/2)/(1+Dx/2)* Bl;
			}
			else if (k == nb_ite_s - 1) {//Boundary Condition
				L[k] = -Bl + (1 + Dx / 2) / (1 - Dx / 2)* Bu;
				D[k] = -2 * Bu / (1 - Dx / 2) + 1 + r * Dt + Bl + Bu + (Dt / mu)*(calc_vec[2][k - 1] + calc_vec[2][nb_ite_s - k - 1]);
				U[k] = 0;								  
			}
			else {
				L[k] = -Bl;
				D[k] = 1 + r * Dt + Bl + Bu + (Dt / mu) *(calc_vec[2][k - 1] + calc_vec[2][nb_ite_s - k - 1]);
				U[k] = -Bu;	
			}
			
			W[k] = W_prev[k] + (Dt / mu) * R(k, W_prev, nb_ite_s, calc_vec, Dx, strike, X);
		}

		tridiagSolver(L, D, U, W, nb_ite_s - 1);
		memcpy(W_prev, W, (nb_ite_s + 1)*sizeof(double));
	}

	for (int i = 0; i <= nb_ite_s - 1; ++i) {
		if (X[i]>log(s)) {
			ir = i;
			break;
		}
	}

	price_option = W[ir - 1] + ((W[ir] - W[ir - 1]) / Dx)*(log(s) - X[ir - 1]);

	delete[] L;
	delete[] D;
	delete[] U;
	delete[] X;
	delete[] W;
	delete[] W_prev;
	for (int i = 0; i < 6; i++) {
		delete[] calc_vec[i];
	}
	delete[] calc_vec;


	return price_option;
}

PricerEuroPut::~PricerEuroPut()
{
}

double PricerEuroPut::g1(double x)
{
	if (Y != 0.0) {
		throw invalid_argument("Pricer not implement if Y != 0");
	}

	if (Y == 0.0) {
		return exp(-x);
	}
}

double PricerEuroPut::g2(double x)
{
	if (Y != 0.0) {
		throw invalid_argument("Pricer not implement if Y != 0");
	}

	if (Y == 0.0) {
		return expint(x);
	}
}



//return a matrix [6][ite_x] with the precalculated vectors
double ** PricerEuroPut::fill_6vectors(int nb_ite_s, double delta_x)
{
	double** res = new double*[6];
	double* v1 = new double[nb_ite_s]; res[0] = v1;
	double* v2 = new double[nb_ite_s]; res[1] = v2;
	double* v3 = new double[nb_ite_s]; res[2] = v3;
	double* v4 = new double[nb_ite_s]; res[3] = v4;
	double* v5 = new double[nb_ite_s]; res[4] = v5;
	double* v6 = new double[nb_ite_s]; res[5] = v6;

	for (int k = 1; k <= nb_ite_s; k++) {
		res[0][k - 1] = g1(k * lambda_n * delta_x);
		res[1][k - 1] = g1(k * lambda_p * delta_x);
		res[2][k - 1] = g2(k * lambda_n * delta_x);
		res[3][k - 1] = g2(k * lambda_p * delta_x);
		res[4][k - 1] = g2(k * (lambda_n+1) * delta_x);
		res[5][k - 1] = g2(k * (lambda_p-1) * delta_x);
	}

	return res;

}

inline double PricerEuroPut::sigma2(double x)
{
	return (1 / mu)* pow(lambda_p, Y - 2)* (-pow(lambda_p*x, 1 - Y)*exp(-lambda_p*x) + (1 - Y)*(g1(0.0) - g1(lambda_p*x)))
		 + (1 / mu)* pow(lambda_n, Y - 2)* (-pow(lambda_n*x, 1 - Y)*exp(-lambda_n*x) + (1 - Y)*(g1(0.0) - g1(lambda_n*x)));
}

inline double PricerEuroPut::w(double x)
{
	return (g2(lambda_p*x)  - g2((lambda_p - 1)*x)  + g2(lambda_n*x)  - g2((lambda_n + 1)*x))/mu;
}

inline double PricerEuroPut::cBl(double Dx, double Dt, double r, double q)
{
	return sigma2(Dx)*Dt / (2 * pow(Dx, 2)) - (r - q + w(Dx) - sigma2(Dx) / 2) * Dt / (2 * Dx);
}

inline double PricerEuroPut::cBu(double Dx, double Dt, double r, double q)
{
	return sigma2(Dx)*Dt / (2 * pow(Dx, 2)) + (r - q + w(Dx) - sigma2(Dx) / 2) * Dt / (2 * Dx);
}

double PricerEuroPut::R(int i, double * W, int nb_ite_s, double ** calc_vec, double Dx, double strike, double* X) {
	double res = 0.0;

	for (int k = 1; k <= i - 1; k++) {
		res += (W[i - k] - W[i] - k * (W[i - k - 1] - W[i - k]))*(calc_vec[2][k-1]-calc_vec[2][k]);
		res += (W[i-k-1]-W[i-k])/(lambda_n*Dx)*(calc_vec[0][k - 1] - calc_vec[0][k]);
	}
	for (int k = 1; k <= nb_ite_s-i-1; k++) {
		res += (W[i + k] - W[i] - k * (W[i + k + 1] - W[i + k]))*(calc_vec[3][k - 1] - calc_vec[3][k]);
		res += (W[i +k + 1] - W[i + k]) / (lambda_p *Dx)*(calc_vec[1][k - 1] - calc_vec[1][k]);
	}

	res += strike * calc_vec[2][i - 1] - exp(X[i])*calc_vec[4][i - 1];
	return res;
}




