// Index Manipulation.cpp : This program gives the option premium for a DOP, by discretizing the PIDE that models the value process
//

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "expint.hpp"
#include "tridiagSolver.hpp"
#include <time.h>
#include<stdlib.h>

using namespace std;

int main()
{   // Initializing the model parameters
	double spot_price = 1800;
	double strike = 1650;
	double lower_barrier = 1000;
	double upper_barrier = 2000;
	double riskfree_rate = 0.5;
	double div_rate = 1.35;
	double T = 0.5;
	double sigma = 0.20;
	double gamma = 0.17;
	double theta = -0.15;
	int n_spatial_intervals = 4000;
	int n_time_intervals = 1000;
	//to compute the running time
	clock_t startTime, endTime;

	// computing the value of lambda_p and lambda_n which are the parameters for the function k(y)

	double lambda_p, lambda_n;
	lambda_p = sqrt((pow(theta, 2) / (pow(sigma, 4))) + (2 / ((pow(sigma, 2)*gamma)))) - (theta / pow(sigma, 2));
	lambda_n = sqrt((pow(theta, 2) / (pow(sigma, 4))) + (2 / ((pow(sigma, 2)*gamma)))) + (theta / pow(sigma, 2));
	cout << "lambda_p " << lambda_p << endl;
	cout << "lambda_n " << lambda_n << endl;

	//creating the grid for w assuming n_intervals. 
	// Indexing convention followed.
	//w[0] and w[n_spatial_intervals] contain boundary conditions which are given to be 0
	//w[1] to w[n_spatial_intervals -1] contain the interior points over which we compute the prices using the discretized PIDE

	double *w, *x;
	w = new double[n_spatial_intervals + 1];
	x = new double[n_spatial_intervals + 1];
	double x_lowerBound = log(lower_barrier);
	double x_upperBound = log(upper_barrier);
	double t_lowerBound = 0;
	double t_upperBound = T;
	double delta_x = (x_upperBound - x_lowerBound) / n_spatial_intervals;
	//double delta_t = (t_upperBound - t_lowerBound) / n_time_intervals;
	double delta_t = T / n_time_intervals;
	x[1] = x_lowerBound;
	x[n_spatial_intervals] = x_upperBound;

	//Initialising the array of discretized x, this is used to calculate the boundary conditions at tau =0
	for (int index = 2; index < n_spatial_intervals; index++)
	{
		x[index] = log(lower_barrier) + index*delta_x;
	}

	// Evaluating the integral integral(y^2*k(y)) in the interval [-delta_x, delta_x]
	double sigmaSquared = ((1 - ((1 + (lambda_p*delta_x))*exp(-1 * lambda_p*delta_x))) / (gamma*pow(lambda_p, 2))) + ((1 - ((1 + (lambda_n*delta_x))*exp(-1 * lambda_n*delta_x))) / (gamma*pow(lambda_n, 2)));
							
	//Evaluating the integral integal((1-exp(y))*k(y)) in the interval [-inf, -delta_x] U [delta_x, inf]
	double omega = ((expint(lambda_p*delta_x) - expint((lambda_p - 1)*delta_x)) / gamma) + ((expint(lambda_n*delta_x) - expint((lambda_n + 1)*delta_x)) / gamma);
	cout << "sigmaSquared " << sigmaSquared << endl;
	cout << "omega " << omega << endl;

	//Evaluating B_l and B_u
	double B_l = ((sigmaSquared*delta_t) / (2 * pow(delta_x, 2))) - ((riskfree_rate - div_rate + omega - (0.5*sigmaSquared))*(delta_t / (2 * delta_x)));
	double B_u = ((sigmaSquared*delta_t) / (2 * pow(delta_x, 2))) + ((riskfree_rate - div_rate + omega - (0.5*sigmaSquared))*(delta_t / (2 * delta_x)));
	cout << "B_l " << B_l << endl;
	cout << "B_u " << B_u << endl;

	// Set up Boundary conditions for w, w[0] and  w[n] are the boundary conditions and 1 to n_interval-1 are the interior points

	for (int index = 0; index <= n_spatial_intervals; index++)
	{
		//x[index] = log(lower_barrier) + index*delta_x;
		//if (index == 0 || index == n_spatial_intervals)
		//w[index] = 0;
		{
			double payoff;
			if (index == 0) //|| (index == n_spatial_intervals))
				w[1] = w[1] + (strike - exp(x[0]));
			else
				payoff = strike - exp(x[index]);
			if (payoff > 0)
				w[index] = payoff;
			else
				w[index] = 0;
		}
	}

	//Preinitializing the vectors expLambda_n, expLambda_p,expintLambda_n, expintLambda_p for the computation of the integral adjustment
	double *expLambda_n, *expLambda_p, *expintLambda_n, *expintLambda_p;
	expLambda_n = new double[n_spatial_intervals];
	expLambda_p = new double[n_spatial_intervals];
	expintLambda_n = new double[n_spatial_intervals];
	expintLambda_p = new double[n_spatial_intervals];
	for (int k = 1; k <= n_spatial_intervals - 1; k++)
	{
		expLambda_n[k] = exp(-k*delta_x*lambda_n);
		expLambda_p[k] = exp(-k*delta_x*lambda_p);
		expintLambda_n[k] = expint(k*lambda_n*delta_x);
		expintLambda_p[k] = expint(k*lambda_p*delta_x);
	}
	//declare the upper, lower and diagonal arrays and initialize them all to zero
	double *upperDiagonal, *lowerDiagonal, *diagonal;
	upperDiagonal = new double[n_spatial_intervals];
	lowerDiagonal = new double[n_spatial_intervals];
	diagonal = new double[n_spatial_intervals];
	//Set up the coefficient matrix
	//The lower diagonal coefficient multiplies with w[2] to w[n-1]
	for (int index = 2; index <= n_spatial_intervals - 1; index++)
		lowerDiagonal[index] = -B_l;
	//The upper diagonal coefficient multiplies with w[1] to w[n-2]
	for (int index = 1; index <= n_spatial_intervals - 2; index++)
		upperDiagonal[index] = -B_u;
	//The diagonal coefficients multiply with w[1] to w[n-1]
	for (int index = 1; index <= n_spatial_intervals - 1; index++)
		diagonal[index] = 1 + (riskfree_rate*delta_t) + B_l + B_u + (delta_t / gamma)*(expint(index*lambda_n*delta_x) + expint((n_spatial_intervals - index)*lambda_p*delta_x));

	// Calculating the value of w at times tau = 1,2,3 and so on till T
	startTime = clock();
	for (int t = 1; t <= n_time_intervals; t++)
	{ //Declaring a new array of the integral adjusted values of w at the interior points.
		double *w_adjusted;
		w_adjusted = new double[n_spatial_intervals];
		// We have to populate the terms of w_adjusted, this is indexed from 1 to n-1 because we only need the interior points
		for (int index = 1; index <= (n_spatial_intervals - 1); index++)
		{
			double term1, term2, term3, term4;
			term1 = 0;
			term2 = 0;
			term3 = 0;
			term4 = 0;
			for (int k = 1; k <= index - 1; k++)
			{
				term1 = term1 + (w[index - k] - w[index] - k*(w[index - k - 1] - w[index - k]))*(expintLambda_n[k] - expintLambda_n[k + 1]);
				term2 = term2 + ((w[index - k - 1] - w[index - k]) / (lambda_n*delta_x))*(expLambda_n[k] - expLambda_n[k + 1]);
			}
			for (int k = 1; k <= n_spatial_intervals - index - 1; k++)
			{
				term3 = term3 + (w[index + k] - w[index] - k*(w[index + k + 1] - w[index + k]))*(expintLambda_p[k] - expintLambda_p[k + 1]);
				term4 = term4 + ((w[index + k + 1] - w[index + k]) / (lambda_p*delta_x))*(expLambda_p[k] - expLambda_p[k + 1]);
			}
			w_adjusted[index] = w[index] + (delta_t / gamma)*(term1 + term2 + term3 + term4);

		}

		tridiagSolver(lowerDiagonal, diagonal, upperDiagonal, w_adjusted, n_spatial_intervals - 1);
		for (int index = 0; index <= n_spatial_intervals; index++)
		{ //By the boundary conditions
			if (index == 0) //|| index == n_spatial_intervals)
				w[1] = w[1] + (strike - exp(x[0]));
			else
				//At the interior points
				w[index] = w_adjusted[index];
		}

	}

		endTime = clock();
		ofstream outputfile;

		//outputfile.open("NAMEFILE.txt");

		//for (int i = 1; i <= n_spatial_intervals; i++)
		//{
			//outputfile << w[i] << " ";
		//}
		int ir;
		for (int index = 0; index <= n_spatial_intervals - 1; ++index) {
			//int ir;
			if (x[index] > log(spot_price)) {
				ir = index;
				break;
			}
		}
	
	outputfile << endl;
	outputfile << endl;
	outputfile.close();
	double position;
	position = w[ir - 1] + ((w[ir] - w[ir - 1]) / delta_x)*(log(spot_price) - x[ir - 1]);
	//position = (int)(((log(spot_price) - log(lower_barrier)) / delta_x) + 1);
	//double price = w[position];
	cout << "The price of the option at a spot of " << spot_price << " is = " << position << endl;
	cout << "The time taken in seconds is " << ((float)(endTime - startTime)) / CLOCKS_PER_SEC;
	getchar();
	return 0;
}
