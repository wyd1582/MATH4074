

#include <iostream>
using namespace std;

#ifndef __class_arraysClass
#define __class_arraysClass

class arraysClass{

    public:

        int aSize1;
        int aSize2;
		int aSize3;

        int ***frequencies;

        arraysClass(int x1, int x2, int x3){

            aSize1 = x1;
            aSize2 = x2;
			aSize3 = x3;

			cout << "Constructor: aSize1&aSize2 " << aSize1 << " " << aSize2 << endl;

            frequencies = new int**[aSize1+1];
            for (int i=0; i<=aSize1; i++){
                frequencies[i] = new int*[aSize2+1];
                for (int j=0; j<=aSize2; j++){
                    frequencies[i][j] = new int [aSize3+1];
                }
            }
        };

        ~arraysClass(){

			cout << "Destructor: aSize1&aSize2 " << aSize1 << " " << aSize2 << endl;

            for (int i=0; i<=aSize1; i++){
                for (int j=0; j<=aSize2; j++){
                    delete [] frequencies[i][j];
                }
                delete [] frequencies[i];
            }
            delete [] frequencies;
        };                                             
};

#endif
