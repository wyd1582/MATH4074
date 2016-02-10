#include "functions.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <complex>
#include <stdlib.h>

typedef complex<double> dcmplx;
#define PI  3.1415926535897932

int main(int, char**) {

	dcmplx input[8];
	input[0] = dcmplx(3.6, 2.6);
	input[1] = dcmplx(2.9, 6.3);
	input[2] = dcmplx(5.6, 4.0);
	input[3] = dcmplx(4.8, 9.1);
	input[4] = dcmplx(3.3, 0.4);
	input[5] = dcmplx(5.9, 4.8);
	input[6] = dcmplx(5.0, 2.6);
	input[7] = dcmplx(4.3, 4.1);

	// FFT
	dcmplx *output = FFT(input, 8);
	printf ("Input\n");
	for (int i=0; i<8; ++i) {
		printf ("%f, %f\n", input[i].real(), input[i].imag());
	}
	cout << " " << endl;
	printf ("FFT\n");
	for (int i=0; i<8; ++i) {
		printf ("%f, %f\n", output[i].real(), output[i].imag());
	}
	cout << " " << endl;

	// inverse FFT
	dcmplx *ioutput = IFFT(output, 8);
	printf ("Inverse FFT\n");
	for (int i=0; i<8; ++i) {
		printf ("%f, %f\n", ioutput[i].real(), ioutput[i].imag());
	}

	free(output);
	free(ioutput);

	return 0;
}

