#include "stdafx.h"
#include "CyberDemon.h"
#include <iostream>
using std::cout;
using std::endl;

CyberDemon::CyberDemon() : Demon()
{
}

CyberDemon::CyberDemon(int strength, int hp) : Demon(strength, hp)
{
}

int CyberDemon::getDamage()
{
	int damage;
	damage = Demon::getDamage();
	cout << getSpecies() << " attacks for " << damage << " points!" << endl;
	return damage;
}

string CyberDemon::getSpecies()
{
	return "CyberDemon";
}


