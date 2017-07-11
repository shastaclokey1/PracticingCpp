#pragma once
#ifndef CYBERDEMON_H
#define CYBERDEMON_H

#include "Demon.h"
#include <string>
using std::string;

class CyberDemon : public Demon
{
public:
	CyberDemon();
	CyberDemon(int strength, int hp);

	int getDamage();
	string getSpecies();
};


#endif //CYBERDEMON_H