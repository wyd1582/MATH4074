#include <iostream>

using namespace std;

#ifndef __struct_marketAttributes
#define __struct_marketAttributes

struct marketAttributes{

	string market;
	string symbolName;
	string exchangeName;

};

#endif

#ifndef __struct_dataAttributes
#define __struct_dataAttributes

struct dataAttributes{

	marketAttributes myMarket;
	int date;
	double dateTimeExchange;
	double dateTimeLocal;
	int min;
	int hour;
	double price;
	int volume;

};

#endif
