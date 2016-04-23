/*
Copyright (C) 2010 Botao Jia

This file is an testing of the implementation of the 
downhill simplex optimization algorithm using C++.
One function object Rosenbrock and two function rosenbrock, polynomial_fun are used.

You can redistribute it and/or modify it at will.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <math.h>
#include "simplex.h"
using namespace std;

template<class Con>
void printcon(const Con& c){
	std::cout.precision(8);
	cout << "results are:";
	copy( c.begin(), c.end(), ostream_iterator<typename Con::value_type>(cout, "  ") );
	cout<<endl;
}

double paraboloid2_fun(vector<double> x){
	/* Paraboloid centered on (30,-60), with scale factors (3.0, 5.0) and minimum 10 */
	return 3.0*pow((x[0]-30.0), 2.0) + 5.0*pow((x[1]+60.0), 2.0) + 10.0;
}

double paraboloid4_fun(vector<double> x){
	return 3.0*pow((x[0]-30.0), 4.0) + 2.0*pow((x[1]+60.0), 4.0) + 10.0;
}

int main(){

	//initial guessing value for the objective function
	vector<double> init;
	init.push_back(34.3);
	init.push_back(-60.0);

	//initial trial simplex
	//double a0[] = {-1.5, -1};
	//double a1[] = {-2, -2};
	//double a2[] = { 2.5, 1.5};

	double a0[] = {-2.5, -0.5};
	double a1[] = {-3, -2};
	double a2[] = { 3.5, 1.5};
	vector<vector<double> > simplex;
	simplex.push_back( vector<double>(a0, a0+2) );
	simplex.push_back( vector<double>(a1, a1+2) );
	simplex.push_back( vector<double>(a2, a2+2) );

	//optimizating ...
	//printcon is a function printing container values

	using BT::Simplex;

	cout <<"Paraboloid function achieves minimum at:"<<endl;
	printcon( Simplex(paraboloid2_fun, init, 1e-5, simplex) );
	cout << endl;

	cout <<"Paraboloid function achieves minimum at:"<<endl;
	printcon( Simplex(paraboloid4_fun, init, 1e-1) );
	cout << endl;


}
