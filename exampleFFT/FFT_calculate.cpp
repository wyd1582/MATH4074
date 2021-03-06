#include "functions.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <complex>
#include <stdlib.h>

typedef complex<double> dcmplx;
#define PI  3.1415926535897932

void FFT_calculate(dcmplx* x, int N, int skip, dcmplx* X, dcmplx* D, dcmplx* twiddles) {
  printf("START FFT_calculate\n");
  printf("PARAMS %p %d %d %p %p %p\n",x, N, skip, X, D, twiddles); 
  dcmplx * E = D + N/2;
  int k;

  if (N == 1) {
    X[0] = x[0];
    return;
  }

  // use X as a scratch buffer
  printf("START FIRST INNER FFT_calculate\n");
  printf("PARAMS %p %d %d %p %p %p\n",x, N/2, skip*2, E, X, twiddles);  
  FFT_calculate(x, N/2, skip*2, E, X, twiddles);

  printf("START SECOND INNER FFT_calculate\n");
  printf("PARAMS %p %d %d %p %p %p\n",x + skip, N/2, skip*2, D, X, twiddles);
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
