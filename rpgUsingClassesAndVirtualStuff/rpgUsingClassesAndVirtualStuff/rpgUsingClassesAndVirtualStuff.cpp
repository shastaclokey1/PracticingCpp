// rpgUsingClassesAndVirtualStuff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Human.h"
#include "Elf.h"
#include "CyberDemon.h"
#include "Balrog.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

void battleArena(Creature *creature1, Creature *creature2);

int main()
{
	Human knight(25, 25);
	Elf leodra(20, 20);
	CyberDemon borg(60, 60);
	Balrog destroyer(40, 40);

	cout << "Your " << knight.getSpecies() << " has " << knight.getHitpoints() << " hitpoints and " << knight.getStrength() << " strength." << endl;
	cout << "Your " << leodra.getSpecies() << " has " << leodra.getHitpoints() << " hitpoints and " << leodra.getStrength() << " strength." << endl;
	cout << "Your " << borg.getSpecies() << " has " << borg.getHitpoints() << " hitpoints and " << borg.getStrength() << " strength." << endl;
	cout << "Your " << destroyer.getSpecies() << " has " << destroyer.getHitpoints() << " hitpoints and " << destroyer.getStrength() << " strength." << endl;

	cout << endl << endl;

	char keepPlaying;
	while (true)
	{
		cout << "Roll for battle?(y/n): ";
		cin >> keepPlaying;
		if (keepPlaying == 'y' || keepPlaying == 'Y')
			break;
		else
			exit(1);
		/*knight.getDamage();
		leodra.getDamage();
		borg.getDamage();
		destroyer.getDamage();*/
	}

	Human *knightPtr = &knight;
	Elf *leodraPtr = &leodra;
	CyberDemon *borgPtr = &borg;
	Balrog *destroyerPtr = &destroyer;

	battleArena(knightPtr, leodraPtr);
	battleArena(borgPtr, destroyerPtr);
	while(true)
	{ }
	
	
	
	return 0;
}


void battleArena(Creature *creature1, Creature *creature2)
{
	int c1Health, c2Health, c1Damage, c2Damage;
	cout << "In the left corner we have creature1, a " << creature1->getSpecies() << " with " << creature1->getStrength() << " strength and " << creature1->getHitpoints() << " health!" << endl;
	cout << "And in the right corner we have creature2, a " << creature2->getSpecies() << " with " << creature2->getStrength() << " strength and " << creature2->getHitpoints() << " health!" << endl;
	cout << "Let the battle commence!!" << endl << endl;
	while (true)
	{
		c1Damage = creature1->getDamage();
		c2Damage = creature2->getDamage();
		c1Health = creature1->getHitpoints() - c2Damage;
		c2Health = creature2->getHitpoints() - c1Damage;
		if (c1Health <= 0 && c2Health <= 0)
		{
			cout << "Ladies and Gentlemen we have a tie!" << endl;
			break;
		}
		if (c1Health <= 0)
		{
			cout << "Creature 2(" << creature2->getSpecies() << ") is victorious!" << endl;
			break;
		}
		if (c2Health <= 0)
		{
			cout << "Creature 1(" << creature1->getSpecies() << ") is victorious!" << endl;
			break;
		}
		creature1->setHitpoints(c1Health);
		creature2->setHitpoints(c2Health);
	}
	cout << endl << endl;
}
