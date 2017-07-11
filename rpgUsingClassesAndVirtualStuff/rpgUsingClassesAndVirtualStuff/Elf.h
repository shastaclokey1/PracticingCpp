#pragma once
#ifndef ELF_H
#define ELF_H

#include "creature.h"
#include <string>
using std::string;

class Elf : public Creature
{
public:
	Elf();
	Elf(int strength, int hp);

	int getDamage();
	string getSpecies();
};


#endif //ELF_H