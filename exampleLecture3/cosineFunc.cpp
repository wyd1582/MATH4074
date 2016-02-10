#include "functions.h"

#include <stdio.h> 
#include <unistd.h> 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Cosine using Taylor Expansion
double cosineFunc(double x1)
{
    double term1(1.0);
	double sum1(1.0);
    int p(0);
    while (fabs(term1/sum1) > 0.00000001)
    {
        p++;
        term1 = -term1*x1*x1/((2*p-1)*(2*p));
        sum1 += term1;
    }
    return sum1;
}
