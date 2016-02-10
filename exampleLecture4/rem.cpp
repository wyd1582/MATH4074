
#include "functions.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <stdio.h>

double rem(double x, double y)
{
    double r;
    int n;

    n = int(x/y);
    r = x - n*y;
	
    return(r);
}
