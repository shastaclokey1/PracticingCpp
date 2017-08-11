#pragma once

#ifndef RANDOMNESS_H
#define RANDOMNESS_H

#include <vector>
using std::vector;

static class randomness
{
public:
	static void setRandVectorVar(vector<unsigned char> setDataToThis);
	static vector<unsigned char> getRandVectorVar();

private:
	static int randIntVar;
	static bool randBoolVar;
	static short randShortVar;
	static vector<unsigned char> randVectorVar;

};




#endif //RANDOMNESS_H