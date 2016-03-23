
//#include "stdafx.h"

#include "structures.h"
#include "functions.h"

#include <iostream>
#include <iomanip>
#include <ios>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>


void builder1(arraysClass &arrays, int aSize1, int aSize2, int aSize3)
{

    int i1, i2, i3;
    for (i1=0; i1<=aSize1; i1++){
        for (i2=0; i2<=aSize2; i2++){
            for (i3=0; i3<=aSize3;i3++){
                    arrays.frequencies[i1][i2][i3] = 1.0; 
            }
        }
    }
}
