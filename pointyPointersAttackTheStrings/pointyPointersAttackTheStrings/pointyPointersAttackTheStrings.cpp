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
	pointersGalore(const pointersGalore &coppiedObject);  //copy constructor
	~pointersGalore(); //destructor

	string getString() const;

	// its a personal style choice but i prefere to use the "address of" operator attached to the variable name and not
	// the type name like so: const pointersGalore &secondOpperand
	void concatinateAndPrint(const pointersGalore& secondOpperand);


private:
	string *stringPoint;
};


pointersGalore globalPtr("I will stick around after main exits, kind of..");

int main()
{
	/*
	FYI a deconstructor is almost never explicitly called. The reason people implement deconstructors is to
	be able to remove an object when its scope is no longer needed. Every instantiation of your pointersGalore
	objects are local to main(), so when main() exits the run time handler will automatically destroy each object
	since its scope has been reached.

	I have created a globally defined pointersGalore that would require a deconstructor to be called because its scope
	is defined outside of main, hence once main exits globalPtr will still exist unless you have specified its
	deconstruction.
	*/
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

	cout << globalPtr.getString() << endl;

	// use a deconstructor properly, if you comment out the call to the deconstructor you will
	// see that globalPtr remains defined in the following try / catch block
	globalPtr.~pointersGalore();

	try
	{
		// look now its gone..
		cout << globalPtr.getString() << endl;
	}
	catch (std::exception e)
	{
		cout << "global pointer is null!";
	}


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
pointersGalore::pointersGalore(const pointersGalore &coppiedObject)
{
	/*
	So here you are meaning to employ a type of argument passing called "pass by reference". Pass by reference
	is a super great way to pass objects around and use them because it is very safe, very cheap (in memory size), and
	very easy to employ. I highly recommend using pass by reference whenever you can. However, you are doing some crazy
	weird stuff with dereferencing the private field of the coppiedObject when you simply need to use the public accessor
	method you already defined. For more information on pass by reference refer to the following documentation. 

	Pass by ref: http://www.learncpp.com/cpp-tutorial/73-passing-arguments-by-reference/
	*/
	stringPoint = new string(coppiedObject.getString());
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
	/*
	As stated in the comment block in your coppiedObject constructor there is really no nead to coerce
	the compiler into allowing you to dereference the private field of your 'secondOpperand' object. Although
	technically this is allowable it is not good code practice and it is confusing. The following code will do the same
	thing without violating the security level of the object being operated on and it increases readability.

	string *temp = new string(*stringPoint + secondOpperand.getString()); 
	*/
	string *temp = new string(*stringPoint + *secondOpperand.stringPoint);
	cout << *temp << endl;
}
