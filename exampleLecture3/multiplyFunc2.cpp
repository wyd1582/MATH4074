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

void multiplyFunc2(const double & factor, double & width, double & height)
{

	width  = factor*width;
	height = factor*height;

	cout << "inside multiplyFunc2: " << width << " " << height << endl;

	//factor  = 4.0; // Cannot do, declared constant
}
