// figuringOutStaticClasses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "sampleStaticClass.h"
using std::cout;
using std::endl;

int main()
{
	vector<unsigned char> data;
	for (unsigned char i = 0; i < 8; i++)
		data.push_back(i);
	
	randomness::setRandVectorVar(data);
	vector<unsigned char> filteredData = randomness::getRandVectorVar();
	for (int i = 0; i < (int)filteredData.size(); i++)
		cout << filteredData[i] << ", ";
	cout << endl;

	while (true)
	{ }
	
	return 0;
}

