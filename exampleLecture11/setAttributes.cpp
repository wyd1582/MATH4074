//#include "stdafx.h"

#include "structures.h"
#include "functions.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void setAttributes(contractStruct &myContract, readAttributes &readAttribute)
{

    string market = myContract.market;

	string fieldMarketOutput;
	string dummy;

	readAttribute.getMarketField(market, "transactionCost", fieldMarketOutput);
    myContract.transactionCost = atof(fieldMarketOutput.c_str());

	readAttribute.getMarketField(market, "currencyValue", fieldMarketOutput);
    myContract.currencyValue = atof(fieldMarketOutput.c_str());

	readAttribute.getMarketField(market, "marginRequirement", fieldMarketOutput);
    myContract.marginRequirement = atof(fieldMarketOutput.c_str());

	//readAttribute.getMarketField(market, "currencyName", fieldMarketOutput);
    //strcpy(dummy.c_str(), fieldMarketOutput.c_str());
	//myContract.currencyName = dummy;
	//myContract.currencyName = fieldMarketOutput;

	readAttribute.getMarketField(market, "onePointValue", fieldMarketOutput);
    myContract.onePointValue  = atof(fieldMarketOutput.c_str());

	readAttribute.getMarketField(market, "spread", fieldMarketOutput);
    myContract.spread = atof(fieldMarketOutput.c_str());

	readAttribute.getMarketField(market, "ticksize", fieldMarketOutput);
	myContract.ticksize = atof(fieldMarketOutput.c_str());

	readAttribute.getMarketField(market, "precisionSize", fieldMarketOutput);
	myContract.precisionSize = atoi(fieldMarketOutput.c_str());
    
}
