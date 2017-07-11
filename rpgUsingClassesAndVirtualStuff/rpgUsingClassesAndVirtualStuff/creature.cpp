#include "stdafx.h"
#include "creature.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

Creature::Creature()
{
	strength = 10;
	hitpoints = 10;
}

Creature::Creature(int newStrength, int newHit)
{
	strength = newStrength;
	hitpoints = newHit;
}

int Creature::getStrength()
{
	return strength;
}

int Creature::getHitpoints()
{
	return hitpoints;
}

void Creature::setStrength(int strengthToSet)
{
	strength = strengthToSet;
}

void Creature::setHitpoints(int hitToSet)
{
	hitpoints = hitToSet;
}

int Creature::getDamage()
{
	int damage;
	//creatures inflict damage as a random number up to their strength
	damage = (rand() % strength) + 1;
	return damage;
}

string Creature::getSpecies()
{
	return "Creature";
}


