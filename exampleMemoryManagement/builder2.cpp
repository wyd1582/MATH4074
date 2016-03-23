#include "structures.h"
#include "functions.h"

#include <iostream>
#include <iomanip>
#include <ios>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>


void builder2(int aSize1, int aSize2, int aSize3)
{
    int i, j;
	int i1, i2, i3;

	int ***frequencies;

	frequencies = new int**[aSize1+1];
	for (int i=0; i<=aSize1; i++){
		frequencies[i] = new int*[aSize2+1];
		for (int j=0; j<=aSize2; j++){
			frequencies[i][j] = new int [aSize3+1];
		}
	}

    for (i1=0; i1<=aSize1; i1++){
        for (i2=0; i2<=aSize2; i2++){
            for (i3=0; i3<=aSize3;i3++){
                    frequencies[i1][i2][i3] = 1.0; 
            }
        }
    }

	for (int i=0; i<=aSize1; i++){
		for (int j=0; j<=aSize2; j++){
			delete [] frequencies[i][j];
		}
		delete [] frequencies[i];
	}
	delete [] frequencies; 
}
