
#include <stdio.h>
#include <iostream>
#include <string.h> 
#include <string>

// Simple example on Arrays & strings.
// To be continued

// 

using namespace std;

int main()
{
	char myCharArray1[30]; // Does not need to get fully exhausted
	char myCharArray2[] = {'H','i','\0'};
	char myCharArray3[] = "Hi";

	cout << myCharArray1[0] << myCharArray1[1] << myCharArray1[2] << myCharArray1[3] << endl;
	cout << myCharArray2[0] << myCharArray2[1] << myCharArray2[2] << myCharArray2[3] << endl;
	cout << myCharArray3[0] << myCharArray3[1] << myCharArray3[2] << myCharArray3[3] << endl;

	//myCharArray1[] = "Hello";
	//myCharArray2[] = {'H', 'e', 'l', 'l', 'o', '\0'};

	char myCharArray4[] = "Crude Oil";
	string myString1 = myCharArray4; // here we are converting C-string to string
	cout << "myString1 = " << myString1 << endl; // printing as a library string
	cout << "myString1.c_str() = " << myString1.c_str() << endl; // printing as a C-string

	if (myCharArray4 == "Crude Oil"){
		cout << "they are equal(0)" << endl;
	}
	else{
		cout << "they are NOT equal(0)" << endl;
	}
	
	//if (myCharArray4.c_str() == "Crude Oil"){
	//	cout << "they are equal(1)" << endl;
	//}
	//else{
	//	cout << "they are NOT equal(1)" << endl;
	//}


	if (myString1 == "Crude Oil"){
		cout << "they are equal(2)" << endl;
	}
	else{
		cout << "they are NOT equal(2)" << endl;
	}


	if (strcmp(myString1.c_str(), "Crude Oil") == 0){
		cout << "they are equal(3)" << endl;
	}
	else{
		cout << "they are NOT equal(3)" << endl;
	}


	string myString2, myString3, myString4;

	myString2 = "Buy " + myString1;
	myString2 = myString2 + " and Soybeans";
	cout << "myString2=" << myString2 << endl;

	//myString3 = "Buy " + myCharArray4;
	//cout << "myString3=" << myString3 << endl;

	myString4 = "Buy";
	//strcat(myString4, myString1.c_str());
	cout << "myString4=" << myString4.c_str() << endl;

	char myCharArray5[100];
	//myCharArray5[0] = ' ';
	strcat(myCharArray5, "Buy ");
	strcat(myCharArray5, myString1.c_str());
	//strcat(myCharArray5, myString1);
	strcat(myCharArray5, " and Soybeans");
	cout << "myCharArray5=" << myCharArray5 << endl;

	//======================================
	// Using cin to get user input (strings)
	//--------------------------------------
	char question1[] = "What is your name?";
	string question2 = "Where do you live?";

	char answer1[100];
	string answer2;

	cout << question1 << endl;
	cin >> answer1;

	cout << question2 << endl;
	cin >> answer2;

	cout << "Hi, " << answer1; 
	cout << " from " << answer2;
	cout << endl;

	return 0;

}
