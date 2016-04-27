#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>
using namespace std;


int main(int argc,char** argv){
	ifstream file("Parameters.txt");
	string line,line1;
	stringstream convert;
	int T=0,K=0,P=0;	
	double* readT;
	double* readK;
	double* readP;
	int startread,linecnt=0;
	startread = linecnt = 2;

	double temp=0;

	if (file.is_open()){
		
		getline (file,line);
		stringstream ss(line);

		convert.clear();
		getline (ss,line1,' ');
		getline (ss,line1,' ');				
		T= atof(line1.c_str());	
		

		convert.clear();
		getline (ss,line1,' ');
		getline (ss,line1,' ');				
		K= atof(line1.c_str());			

		convert.clear();
		getline (ss,line1,' ');
		getline (ss,line1,' ');				
		P= atof(line1.c_str());			

		readT = new double[T];
		readK = new double[K];
		readP = new double[P];

		while ( getline (file,line) ){      					
      		if(linecnt>startread && linecnt<=T+startread){ 				      			      			
      			readT[linecnt-startread-1] = atof(line.c_str());	
      		}
      		else if(linecnt>T+startread+1 && linecnt<=T+K+startread+1){     			      			
      			readK[linecnt-startread-T-2] = atof(line.c_str());
  			}
  			else if(linecnt>T+K+startread+1 && linecnt<=T+K+P+startread+1){
				readP[linecnt-startread-T-K-2] = atof(line.c_str());
  			}
  			linecnt++;
    	}    
  	}
  	else cout << "Unable to open file"; 
  	file.close();  	

  	delete[] readT;
  	delete[] readK;
  	delete[] readP;
	
	return 0;
}

