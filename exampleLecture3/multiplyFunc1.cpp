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

void multiplyFunc1(const double & factor, double width, double height)
{
	width  = factor*width;
	height = factor*height;
	
	cout << "inside multiplyFunc1: " << width << " " << height << endl;
}
