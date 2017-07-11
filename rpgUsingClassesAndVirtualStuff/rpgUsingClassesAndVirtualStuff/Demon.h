#pragma once
#ifndef DEMON_H
#define DEMON_H

#include "creature.h"
#include <string>
using std::string;

class Demon : public Creature
{
public:
	Demon();
	Demon(int strength, int hp);

	int getDamage();
	string getSpecies();
};


#endif //DEMON_H