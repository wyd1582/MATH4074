
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "expint.hpp"
#include "tridiagSolver.hpp"

using namespace std;

void tridiagSolver(double *lowerD, double *diag, double *upperD, double *B, int nSize){

	double Xmult;
	int i;
	double *L, *D, *U;

	L = new double[nSize+1];
	D = new double[nSize+1];
	U = new double[nSize+1];

	for (i=1; i<=nSize; i++) {
		L[i] = lowerD[i];
		D[i] = diag[i];
		U[i] = upperD[i];
	}

	for (i=1; i<=nSize-1; i++) {
		Xmult = L[i+1] / D[i];
		D[i+1]  = D[i+1] - Xmult * U[i];
		B[i+1]  = B[i+1] - Xmult * B[i];
	}
	B[nSize] = B[nSize] / D[nSize];

	for (i=nSize-1; i>=1; i--)
		B[i] = (B[i] - U[i] * B[i+1]) / D[i];

	delete [] L;
	delete [] D;
	delete [] U;

}
