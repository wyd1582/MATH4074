#include "functions.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <complex>
#include <stdlib.h>

typedef complex<double> dcmplx;
#define PI  3.1415926535897932

//---------------------------------------------------------------
dcmplx* FFT_get_twiddle_factors(int N) {
  dcmplx* twiddles = (dcmplx*) malloc(sizeof(dcmplx) * N/2);
  int k;
  for (k = 0; k != N/2; ++k) {
    twiddles[k] = exp(dcmplx(0, -2.0*PI*k/N));
  }
  return twiddles;
}
