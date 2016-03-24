#ifndef PRICER_EURO_PUT_H
#define PRICER_EURO_PUT_H

#include "stdafx.h"
#include <math.h>


class PricerEuroPut 
{
public:
	
	PricerEuroPut(double theta, double sigma, double Y, double mu);
	double PricerEuroPut::calculate(double mat, double r, double q, int nb_ite_s, int nb_ite_t, double s, double strike, double smin, double smax);
	virtual ~PricerEuroPut();


private:
	double lambda_n;
	double lambda_p;
	double mu;
	double Y = 0.0; //Set at 0 for our pricer --> could extend the functionnality
	double vol;
	double Bu;
	double Bl;

	double g1(double);
	double g2(double);
	double sigma2(double);
	double w(double);
	double ** fill_6vectors(int nb_ite_s, double delta_x);
	double cBl(double Dx, double Dt, double r, double q);
	double cBu(double Dx, double Dt, double r, double q);
	double R(int i, double * W, int nb_ite_s, double ** calc_vec, double Dx, double strike, double* X);


};

#endif
