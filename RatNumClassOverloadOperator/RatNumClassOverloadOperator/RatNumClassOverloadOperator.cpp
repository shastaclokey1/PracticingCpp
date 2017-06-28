// RatNumClassOverloadOperator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;



class RationalNumber
{
public:
	RationalNumber(int constructNumerator, int constructDenominator);
	RationalNumber(int constructNumerator);
	RationalNumber();

	int getNumerator() const;
	int getDenominator() const;

	void setNumerator(int numToSet);
	void setDenominator(int denomToSet);

	void normalize();

	



private:
	int numerator;
	int denominator;
};

const RationalNumber operator +(const RationalNumber& rat1, const RationalNumber& rat2);
const RationalNumber operator -(const RationalNumber& rat1, const RationalNumber& rat2);
const RationalNumber operator -(const RationalNumber& rat);
const RationalNumber operator *(const RationalNumber& rat1, const RationalNumber& rat2);
const RationalNumber operator /(const RationalNumber& rat1, const RationalNumber& rat2);
ostream& operator <<(ostream& outputStream, const RationalNumber& rat);
istream& operator >>(istream& inputStream, RationalNumber& rat);
const bool operator ==(const RationalNumber& rat1, const RationalNumber& rat2);
const bool operator >(const RationalNumber& rat1, const RationalNumber& rat2);
const bool operator <(const RationalNumber& rat1, const RationalNumber& rat2);
const bool operator >=(const RationalNumber& rat1, const RationalNumber& rat2);
const bool operator <=(const RationalNumber& rat1, const RationalNumber& rat2);


int main()
{
	RationalNumber cool(6/3);
	RationalNumber alsoCool = RationalNumber(1);

	RationalNumber added = cool + alsoCool;
	RationalNumber multiplied = cool * alsoCool;
	RationalNumber divided = cool / alsoCool;
	RationalNumber subtracted = cool - alsoCool;

	//cout << subtracted.getNumerator() << " " << subtracted.getDenominator();

	//cout << added << subtracted;

	if (cool > alsoCool)
		cout << "wooo! they're equal \n";



	cin >> cool;

	cool.normalize();

	cout << cool;

	cool = -cool;

	cout << endl;
	cout << cool;


	while(true)
	{ }

	return 0;
}


RationalNumber::RationalNumber(int constructNumerator, int constructDenominator): numerator(constructNumerator), denominator(constructDenominator)
{
	if (constructDenominator == 0)
	{
		cout << "Nice try xlax. No dividing by 0! Denominator assigned to 1";
		denominator = 1;
	}
}
RationalNumber::RationalNumber(int constructNumerator): numerator(constructNumerator), denominator(1)
{/*no extra error checking needed*/}
RationalNumber::RationalNumber(): numerator(0), denominator(1)
{/*no extra error checking needed*/}

int RationalNumber::getNumerator() const
{
	return numerator;
}
int RationalNumber::getDenominator() const
{
	return denominator;
}
void RationalNumber::setNumerator(int numToSet)
{
	numerator = numToSet;
}
void RationalNumber::setDenominator(int denomToSet)
{
	if (denomToSet == 0)
	{
		cout << "Nice try xlax. No dividing by 0! Denominator assigned to 1";
		denominator = 1;
	}
	else
		denominator = denomToSet;
}

void RationalNumber::normalize()
{
	int gcd, n, d;
	n = abs(numerator);
	d = abs(denominator);
	while (d != 0)
	{
		int r = n % d;
		n = d;
		d = r;
	}
	gcd = n;

	numerator = numerator / gcd;
	denominator = denominator / gcd;

	if (denominator < 0)
	{
		numerator = numerator * (-1);
		denominator = denominator * (-1);
	}

}

const RationalNumber operator +(const RationalNumber& rat1, const RationalNumber& rat2)
{
	int totNum = (rat1.getNumerator() * rat2.getDenominator()) + (rat2.getNumerator() * rat1.getDenominator());
	int totDenom = rat1.getDenominator() * rat2.getDenominator();
	RationalNumber temp(totNum, totDenom);
	return temp;
}
const RationalNumber operator -(const RationalNumber& rat1, const RationalNumber& rat2)
{
	int totNum = (rat1.getNumerator() * rat2.getDenominator()) - (rat2.getNumerator() * rat1.getDenominator());
	int totDenom = rat1.getDenominator() * rat2.getDenominator();
	RationalNumber temp(totNum, totDenom);
	return temp;
}
const RationalNumber operator -(const RationalNumber& rat)
{
	RationalNumber temp(-rat.getNumerator(), rat.getDenominator());
	return temp;
}
const RationalNumber operator *(const RationalNumber& rat1, const RationalNumber& rat2)
{
	int totNum = rat1.getNumerator() * rat2.getNumerator();
	int totDenom = rat1.getDenominator() * rat2.getDenominator();
	RationalNumber temp(totNum, totDenom);
	return temp;
}
const RationalNumber operator /(const RationalNumber& rat1, const RationalNumber& rat2)
{
	int totNum = rat1.getNumerator() * rat2.getDenominator();
	int totDenom = rat1.getDenominator() * rat2.getNumerator();
	RationalNumber temp(totNum, totDenom);
	return temp;
}
ostream& operator <<(ostream& outputStream, const RationalNumber& rat)
{
	outputStream << rat.getNumerator() << "/" << rat.getDenominator();
	return outputStream;
}
istream& operator >>(istream& inputStream, RationalNumber& rat)
{
	int num;
	inputStream >> num;
	char division;
	inputStream >> division;
	if (division != '/')
	{
		cout << "You forgot to divide using /";
		exit(1);
	}
	int denom;
	inputStream >> denom;
	
	rat.setNumerator(num);
	rat.setDenominator(denom);

	return inputStream;

}
const bool operator ==(const RationalNumber& rat1, const RationalNumber& rat2)
{
	return (rat1.getNumerator() * rat2.getDenominator()) == (rat1.getDenominator() * rat2.getNumerator());
}
const bool operator >(const RationalNumber& rat1, const RationalNumber& rat2)
{
	return (rat1.getNumerator() * rat2.getDenominator()) > (rat1.getDenominator() * rat2.getNumerator());
}
const bool operator <(const RationalNumber& rat1, const RationalNumber& rat2)
{
	return (rat1.getNumerator() * rat2.getDenominator()) < (rat1.getDenominator() * rat2.getNumerator());
}
const bool operator >=(const RationalNumber& rat1, const RationalNumber& rat2)
{
	return (rat1.getNumerator() * rat2.getDenominator()) > (rat1.getDenominator() * rat2.getNumerator()) || (rat1.getNumerator() * rat2.getDenominator()) == (rat1.getDenominator() * rat2.getNumerator());
}
const bool operator <=(const RationalNumber& rat1, const RationalNumber& rat2)
{
	return (rat1.getNumerator() * rat2.getDenominator()) < (rat1.getDenominator() * rat2.getNumerator()) || (rat1.getNumerator() * rat2.getDenominator()) == (rat1.getDenominator() * rat2.getNumerator());
}
