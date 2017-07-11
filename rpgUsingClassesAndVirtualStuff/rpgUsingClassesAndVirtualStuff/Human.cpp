#include "stdafx.h"
#include "Human.h"
#include <iostream>
using namespace std;

Human::Human() : Creature()
{
}

Human::Human(int strength, int hp) : Creature(strength, hp)
{
}

int Human::getDamage()
{
	int damage;
	damage = Creature::getDamage();
	cout << getSpecies() << " attacks for " << damage << " points!" << endl;
	
	return damage;
}

string Human::getSpecies()
{
	return "Human";
}
