#include "stdafx.h"
#include "Balrog.h"
#include <iostream>
using std::cout;
using std::endl;

Balrog::Balrog() : Demon()
{
}

Balrog::Balrog(int strength, int hp) : Demon(strength, hp)
{
}

int Balrog::getDamage()
{
	int damage;
	damage = Demon::getDamage();
	cout << getSpecies() << " attacks for " << damage << " points!" << endl;
	//balrogs attack twice because they are fast
	int damage2 = Demon::getDamage();
	cout << "Balrog speed attack inflicts " << damage2 << " additional damage points!" << endl;
	damage = damage + damage2;
	return damage;
}

string Balrog::getSpecies()
{
	return "Balrog";
}


