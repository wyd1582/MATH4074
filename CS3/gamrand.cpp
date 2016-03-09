#include <stdio.h>
#include <stdlib.h>
#include <math.h>       /* pow */
#include <iostream>

#include "functions.h"

// Gamma(alpha, beta) generator
// using Marsaglia and Tsang method (Algorithm 4.33)

double gamrand(double alpha, double beta, long *idum) {

	// alpha:    shape parameter
	// beta:     scale parameter
	// 1.0/beta: rate parameter

	double randU, randZ, randG;
	double tmp1;
	double uTemp;

	// Case 1: alpha >= 1
	if (alpha >= 1) {

		// Step 1: set c & d
		double d = alpha - 1.0 / 3.0; 
		double c = 1.0 / sqrt(9.0 * d);	
		
		bool flag = true;
		while (flag) {

			// Step 2: generate randZ & randU independently			
			uTemp = ran2_mod(idum);
			randZ = invNormal(uTemp);

			randU = ran2_mod(idum);
			// Step 3: if randZ & randU satisfy certain conditions
			//         return randG
			//
			if (randZ > (-1.0 / c)) {
				tmp1 = (1.0 + c*randZ)*(1.0 + c*randZ)*(1.0 + c*randZ);
				flag = (log(randU) >= (0.5*randZ*randZ + d - d*tmp1 + d*log(tmp1)));
			}			
		}
		randG = d*tmp1*beta;

	}

	// Case 2: 0 < alpha < 1

	else {

		tmp1 = gamrand(alpha + 1, beta, idum);
		randU = ran2_mod(idum);		
		randG = tmp1*pow(randU, (1.0 / alpha)); 

	}	

	return randG;
}
