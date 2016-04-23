#include <iostream>
#include "readAttributes.h"

using namespace std;

#ifndef __struct_contractStruct
#define __struct_contractStruct

struct contractStruct {

	string market;
	string currencyName;

	double transactionCost;
	double currencyValue;

	int precisionSize;

	double spread;
	double ticksize;
	double scalingFactor;
	double onePointValue;
	double marginRequirement;
};

#endif
