#pragma once
#ifndef BALROG_H
#define BALROG_H

#include "Demon.h"
#include <string>
using std::string;

class Balrog : public Demon
{
public:
	Balrog();
	Balrog(int strength, int hp);

	int getDamage();
	string getSpecies();
};

#endif //BALROG_H