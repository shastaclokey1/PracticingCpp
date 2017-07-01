// pointyPointersAttackTheStrings.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;

class pointersGalore
{
public:
	pointersGalore();  //default constructor
	pointersGalore(string setStingValue);  //constructor to set string
	pointersGalore(string *setNewPointer); //constructor to set pointer
	pointersGalore(const pointersGalore& coppiedObject);  //copy constructor
	~pointersGalore(); //destructor

	string getString() const;

	void concatinateAndPrint(const pointersGalore& secondOpperand);


private:
	string *stringPoint;
};


int main()
{
    
	pointersGalore p1("Hey there coffee mug, ");
	string bananas = "bananas are the shit";
	pointersGalore p2(bananas);
	string *pointyNipple = new string;
	*pointyNipple = "niplyniplyniplyniply";
	pointersGalore nip1(pointyNipple);
	pointersGalore copyOfNip1(nip1);

	cout << p1.getString() << endl;
	cout << p2.getString() << endl;
	cout << nip1.getString() << endl;
	cout << copyOfNip1.getString() << endl;

	p1.concatinateAndPrint(p2);


	while(true)
	{ }

	return 0;
	
}



pointersGalore::pointersGalore()
{
	stringPoint = new string("default");
}
pointersGalore::pointersGalore(string setStringValue)
{
	stringPoint = new string(setStringValue);
}
pointersGalore::pointersGalore(string *setNewPointer)
{
	stringPoint = new string(*setNewPointer);
}
pointersGalore::pointersGalore(const pointersGalore& coppiedObject)
{
	stringPoint = new string(*coppiedObject.stringPoint);
}
pointersGalore::~pointersGalore()
{
	delete stringPoint;
}

string pointersGalore::getString() const
{
	return *stringPoint;
}

void pointersGalore::concatinateAndPrint(const pointersGalore& secondOpperand)
{
	string *temp = new string(*stringPoint + *secondOpperand.stringPoint);
	cout << *temp << endl;
}
