#pragma once
#ifndef CREATURE_H
#define CREATURE_H

#include <string>
using std::string;


class Creature
{
public:
	Creature(); //initialize to human, 10 strength, 10 hitpoints
	Creature(int newStrength, int newHit); //initialize creature to new strength and new hitpoints

	int getStrength();
	int getHitpoints();

	void setStrength(int strengthToSet);
	void setHitpoints(int hitToSet);

	virtual int getDamage(); //returns damage this creature inflicts in one round of combat

	virtual string getSpecies();


private:
	int strength; // How much damage can we inflict
	int hitpoints; // How much damage can we sustain
};

#endif  //CREATURE_H