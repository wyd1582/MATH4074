#include "functions.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <complex>
#include <stdlib.h>

typedef complex<double> dcmplx;
#define PI  3.1415926535897932

void FFT_calculate(dcmplx* x, int N, int skip, dcmplx* X, dcmplx* D, dcmplx* twiddles) {
  dcmplx * E = D + N/2;
  int k;

  if (N == 1) {
    X[0] = x[0];
    return;
  }

  // use X as a scratch buffer 
  FFT_calculate(x, N/2, skip*2, E, X, twiddles);
  FFT_calculate(x + skip, N/2, skip*2, D, X, twiddles);

  for(k = 0; k < N/2; k++) {
    // Multiply entries of D by the twiddle factors e^(-2*pi*i/N * k) 
    D[k] = twiddles[k*skip] * D[k]; 
  }

  for(k = 0; k < N/2; k++) {
    X[k]       = E[k] + D[k];
    X[k + N/2] = E[k] - D[k];
  }
}
