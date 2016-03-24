// ConsoleApplication5.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "functions.h"
#include "PricerEuroPut.h"

using namespace std;
int main()
{
	clock_t begin = clock();
	//Parameters to create a pricer
	double vol = 0.2;
	double Y = 0;
	double theta = -0.15;
	double mu = 0.17;

	//Parameters specific to our option
	double smin = 100;
	double smax = 4100;
	double r = 0.005;
	double q = 0.0135;
	double T = 0.5;
	double Spot = 1800;
	double Strike = 1650;
	double Ite_time = 400;
	double Ite_price = 1600;

	//Takes approximately 11seconds
	PricerEuroPut* pricer = new PricerEuroPut(theta, vol, Y, mu);
	cout << "Spot: " << Spot << endl;
	cout << "Strike: " << Strike << endl;
	cout << "Put Price: " << pricer->calculate(T,r,q,Ite_price,Ite_time,Spot,Strike,smin,smax) <<endl;
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "time elasped is: " << elapsed_secs << "s" << endl;
	int pause;
	cin >> pause;
    return 0;
}

