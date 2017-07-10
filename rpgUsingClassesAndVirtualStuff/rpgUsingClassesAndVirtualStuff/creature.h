#pragma once


#include <string>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;


class Creature
{
public:
	Creature(); //initialize to human, 10 strength, 10 hitpoints
	Creature(int newType, int newStrength, int newHit); //initialize creature to new type, strength, hitpoints

	int getType();
	int getStrength();
	int getHitpoints();

	void setType(int typeToSet);
	void setStrength(int strengthToSet);
	void setHitpoints(int hitToSet);

	int getDamage(); //returns damage this creature inflicts in one round of combat


private:
	int type; // 0 human, 1 cyberdemon, 2 balrog, 3 elf
	int strength; // How much damage can we inflict
	int hitpoints; // How much damage can we sustain
	string getSpecies(); //returns type of species
};