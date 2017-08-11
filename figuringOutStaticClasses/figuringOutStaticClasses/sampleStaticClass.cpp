#include "stdafx.h"
#include "sampleStaticClass.h"

void randomness::setRandVectorVar(vector<unsigned char> setDataToThis)
{
	randVectorVar = setDataToThis;
}

vector<unsigned char> randomness::getRandVectorVar()
{
	return randVectorVar;
}
