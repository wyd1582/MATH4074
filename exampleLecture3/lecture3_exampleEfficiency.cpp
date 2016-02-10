#include "functions.h"

// simple example on EFFICIENT IF-ELSE and SPEED

int main()
{

	struct timeval startTime, endTime; 
	long seconds, useconds; 
	double mtime;

	int i1, a1;
	double a2, q1;
	double u2;
	int nIter= 10000000;
	cout << "nIter: " << nIter << endl;

	gettimeofday(&startTime, NULL); 
	for (i1=1; i1<nIter; i1++){
		q1 = double (i1);
		a2 = cosineFunc(q1);
		if (a2 < -0.5){
			a1 = 1;
		}
		else if (a2 < 0.0){
			a1 = 2;
		}
		else if (a2 < 0.5){
			a1 = 3;
		}
		else{
			a1 = 4;
		}
	}
	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 
	cout << "Efficient for loop is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;


	gettimeofday(&startTime, NULL);
	for (i1=0; i1<nIter; i1++){

		q1 = double (i1);

		if (cosineFunc(q1) < -0.5){
			a1 = 1;
		}
		else if (cosineFunc(q1) < 0.0){
			a1 = 2;
		}
		else if (cosineFunc(q1) < 0.5){
			a1 = 3;
		}
		else if (cosineFunc(q1) <= 1.0){
			a1 = 4;
		}
	}
	gettimeofday(&endTime, NULL); 
	seconds = endTime.tv_sec - startTime.tv_sec; 
	useconds = endTime.tv_usec - startTime.tv_usec; 
	mtime = ((seconds) * 1000 + useconds/1000.0); 
	cout << "Inefficient for loop is done. Time elapsed was: " << mtime << " (milliseconds)" << endl;

	return 1;

}
