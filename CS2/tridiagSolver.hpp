#ifndef TRI_HPP
#define TRI_HPP


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


using namespace std;

void tridiagSolver(double *lowerD, double *diag, double *upperD, double *B, int nSize);

#endif
