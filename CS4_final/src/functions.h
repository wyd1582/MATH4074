#include <stdio.h>
#include <math.h>
#include <iostream>
#include <complex>
#include <stdlib.h>

using namespace std;

typedef complex<double> dcmplx;
#define PI  3.1415926535897932

dcmplx* FFT(dcmplx*, int);
dcmplx* IFFT(dcmplx*, int);
void FFT_calculate(dcmplx*, int, int, dcmplx*, dcmplx*, dcmplx*);
dcmplx* FFT_get_twiddle_factors(int);
