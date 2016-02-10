#include "functions.h"

// very simple example on Template

template <class T>
T sum(T a1, T a2)
{
	T result;
	result = a1+a2;
	return result;
}

template <class T, class U>
bool are_equal(T a1, U b1)
{
	return (a1==b1);
}

int main()
{

	int i1(5), i2(1), i3;
	i3 = sum<int>(i1,i2);
	//
	double a1(2.0), a2(0.6), a3;
	a3 = sum<double>(a1,a2);

	cout << "i3=" << i3 << " a3=" << a3 << endl;

	// Think of myZero
	if (are_equal(10,10.01)){
		cout << " The two numbers are equal" << endl;
	}
	else{
		cout << " The two numbers are NOT equal" << endl;
	}

	return 1;

}
