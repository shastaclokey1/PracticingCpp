#include "stdafx.h"
#include "creature.h"

Creature::Creature()
{
	type = 0;
	strength = 10;
	hitpoints = 10;
}

Creature::Creature(int newType, int newStrength, int newHit)
{
	type = newType;
	strength = newStrength;
	hitpoints = newHit;
}

int Creature::getType()
{
	return type;
}

int Creature::getStrength()
{
	return strength;
}

int Creature::getHitpoints()
{
	return hitpoints;
}

void Creature::setType(int typeToSet)
{
	type = typeToSet;
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
	cout << getSpecies() << "attacks for " << damage << " points!" << endl;

	//demons can inflicd damage of 50 with a 5% chance
	if ((type == 2) || (type == 1))
	{
		if ((rand() % 100) < 5)
		{
			damage = damage + 50;
			cout << "Demon attack inflicts 50 additional hitpoints!" << endl;
		}
	}

	//elves can double magical damage with a 10% chance
	if (type == 3)
	{
		if ((rand() % 100) < 10)
		{
			cout << "Magical attack inflicts " << damage << " additional damage points!" << endl;
			damage = damage * 2;
		}
	}

	if (type = 2)
	{
		int damage2 = (rand() % strength) + 1;
		cout << "Balrog speed attack inflicts " << damage2 << " additional damage points!" << endl;
		damage = damage + damage2;
	}

	return damage;
}

string Creature::getSpecies()
{
	switch (type)
	{
		case 0: return "Human";
		case 1: return "Cyberdemon";
		case 2: return "Balrog";
		case 3: return "Elf";
	}
}


