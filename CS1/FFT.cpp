#include "functions.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <complex>
#include <stdlib.h>

typedef complex<double> dcmplx;
#define PI  3.1415926535897932

//---------------------------------------------------------------
// N must be a power of 2 
//---------------------------------------------------------------
dcmplx* FFT(dcmplx* x, int N) 
{
  dcmplx* out = (dcmplx*) malloc(sizeof(dcmplx) * N);
  dcmplx* scratch = (dcmplx*) malloc(sizeof(dcmplx) * N);
  dcmplx* twiddles = FFT_get_twiddle_factors(N);
  
  FFT_calculate(x, N, 1, out, scratch, twiddles);
  
  free(twiddles);
  free(scratch);
  return out;
}

