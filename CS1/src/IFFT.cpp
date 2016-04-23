#include "functions.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <complex>
#include <stdlib.h>

typedef complex<double> dcmplx;
#define PI  3.1415926535897932

//---------------------------------------------------------------
dcmplx* IFFT(dcmplx* x, int N) 
{
  dcmplx* out = (dcmplx*) malloc(sizeof(dcmplx) * N);
  dcmplx* scratch = (dcmplx*) malloc(sizeof(dcmplx) * N);
  dcmplx* twiddles = FFT_get_twiddle_factors(N);
  
  FFT_calculate(x, N, 1, out, scratch, twiddles);
  
  free(twiddles);
  free(scratch);

  // Calculate IFFT via reciprocity property of DFT. 
  int N2 = N/2;
  double tmp0, tmp1;
  out[0]   = dcmplx(real(out[0])/N, imag(out[0])/N);
  out[N2]  = dcmplx(real(out[N2])/N, imag(out[N2])/N);

  for(int i=1; i<N2; i++) {
    tmp0 = real(out[i])/N;      
    tmp1 = imag(out[i])/N;
    out[i] = dcmplx(real(out[N-i])/N, imag(out[N-i])/N);
    out[N-i] = dcmplx(tmp0, tmp1);
  }
  return out;
}
