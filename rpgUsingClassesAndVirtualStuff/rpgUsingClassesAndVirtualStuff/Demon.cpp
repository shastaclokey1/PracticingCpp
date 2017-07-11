#include "stdafx.h"
#include "Demon.h"
#include <iostream>
using std::cout;
using std::endl;


Demon::Demon() : Creature()
{
}

Demon::Demon(int strength, int hp) : Creature(strength, hp)
{
}

int Demon::getDamage()
{
	int damage;
	damage = Creature::getDamage();

	if ((rand() % 100) < 5)
	{
		damage = damage + 50;
		cout << "Demon attack inflicts 50 additional hitpoints!" << endl;
	}

	return damage;
}

string Demon::getSpecies()
{
	return "Demon";
}

