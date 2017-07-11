#include "stdafx.h"
#include "Elf.h"
#include <iostream>
using std::cout;
using std::endl;


Elf::Elf() : Creature()
{
}

Elf::Elf(int strength, int hp) : Creature(strength, hp)
{
}

int Elf::getDamage()
{
	int damage;
	damage = Creature::getDamage();
	if ((rand() % 100) < 10)
	{
		cout << "Magical attack inflicts " << damage << " additional damage points!" << endl;
		damage = damage * 2;
	}
	cout << getSpecies() << " attacks for " << damage << " points!" << endl;
	return damage;
	
}

string Elf::getSpecies()
{
	return "Elf";
}
