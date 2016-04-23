//#include "stdafx.h"

#include "structures.h"
#include "readAttributes.h"
#include "functions.h"

#include <sys/time.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main(int argc, char*argv[])
{

	int iField;
	string market;
	market = "JPY";

	contractStruct myContract;
	myContract.market = market;

	readAttributes readAttribute("//mnt//nas//shared//progQuantCompFinance//lecture10//exampleReadAttributes//contractAttributes2.csv");
	int nFields = readAttribute.getNFields();
	//int nAttributes = readAttribute.getNAttributes();

	string *marketFields = new string[nFields];
	readAttribute.getMarketAllFields(market, marketFields);

	cout << " Attributes: ";
	for (iField = 0; iField < readAttribute.getNFields(); iField++){
		cout << marketFields[iField] << " ";
	}
	cout << endl;
	cout << " " << endl;

	cout << "calling setAttributes ..." << endl;
	cout << " " << endl;


	setAttributes(myContract, readAttribute);

	cout << "transaction cost: " << myContract.transactionCost << endl;
	cout << "currency value: " << myContract.currencyValue << endl;
	cout << "margin requirement: " << myContract.marginRequirement << endl;
	//cout << "currency name: " << myContract.currencyName << endl;
	cout << "one point value: " << myContract.onePointValue << endl;
	cout << "spread: " << myContract.spread << endl;
	cout << "tick size: " << myContract.ticksize << endl;
	cout << "precision size: " << myContract.precisionSize << endl;

	cout << "Done -- retrieved and set attributes for " << market  << endl;
	delete [] marketFields;

	return 0;

} // END
