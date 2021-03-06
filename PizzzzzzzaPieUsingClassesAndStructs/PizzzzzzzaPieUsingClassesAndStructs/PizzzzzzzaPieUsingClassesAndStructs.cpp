// PizzzzzzzaPieUsingClassesAndStructs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;


enum typesOfPizza { Dish, Tossed, Pan };
enum pizzaToppings { peperoni, sausage, canadianBacon, onions, mushrooms };
enum possiblePizzaSizes { small, medium, large, xlarge };

class pizza
{
public:
	pizza();

	//accessor and mutator functions
	typesOfPizza getTypeOfPizza();
	void setTypeOfPizza(typesOfPizza typeToSet);

	int getNumberOfToppings();
	void setNumberOfToppings(int numToppingsToSet);

	void getToppingsOnPizza(pizzaToppings getToppingsOnPizza[], int numberOfToppings);
	void setToppingsOnPizza(pizzaToppings setToppingsOnPizza[], int numberOfToppings);

	possiblePizzaSizes getPizzaSize();
	void setPizzaSize(possiblePizzaSizes size);
	
	//the real meaty functions
	void printOrderDescription();
	//preconditions: all variables have been set by user(all choices have been filled out for pizza)
	//postconditions: all qualities of pizza order are printed to the console

private:
	typesOfPizza pizzaType;
	int numberOfToppings;
	static const int MAX_NUM_TOPPINGS = 5;
	pizzaToppings toppingsOnPizza[MAX_NUM_TOPPINGS];
	possiblePizzaSizes pizzaSize;
	const string typesOfPizzeLookUp[3] = { "Dish", "Tossed", "Pan" };
	const string pizzaToppingsLookUp[5] = { "peperoni", "sausage", "canadianBacon", "onions", "mushrooms" };
	const string possiblePizzaSizesLookUp[4] = { "small", "meduim", "large", "xlarge" };
	
	double computePrice();
	//preconditions: all variables have been set by user(all choices have been filled out for pizza)
	//postcondition: takes into account number of toppings and size so to output the correct price
};

pizza::pizza()
{}

typesOfPizza pizza::getTypeOfPizza()
{
	return pizzaType;
}

void pizza::setTypeOfPizza(typesOfPizza typeToSet)
{
	pizzaType = typeToSet;
	return; 
}

int pizza::getNumberOfToppings()
{
	return numberOfToppings;
}

void pizza::setNumberOfToppings(int numToppingsToSet)
{
	numberOfToppings = numToppingsToSet;
	return;
}

void pizza::getToppingsOnPizza(pizzaToppings getToppingsOnPizza[], int numberOfToppings)
{
	for (int i = 0; i < numberOfToppings; i++)
	{
		getToppingsOnPizza[i] = toppingsOnPizza[i];
	}

	return;
}

void pizza::setToppingsOnPizza(pizzaToppings setToppingsOnPizza[], int numberOfToppings)
{
	for (int i = 0; i < numberOfToppings; i++)
	{
		toppingsOnPizza[i] = setToppingsOnPizza[i];
	}
}

possiblePizzaSizes pizza::getPizzaSize()
{
	return pizzaSize;
}

void pizza::setPizzaSize(possiblePizzaSizes pizzaSizeToSet)
{
	pizzaSize = pizzaSizeToSet;
}

void pizza::printOrderDescription()
{
	cout << "Your Pizza order: \n";
	cout << typesOfPizzeLookUp[pizzaType] << endl << numberOfToppings << " toppings" << endl;
	cout << "Toppings on pizza: ";
	for (int i = 0; i < numberOfToppings; i++)
	{
		cout << pizzaToppingsLookUp[toppingsOnPizza[i]] << ", ";
	}
	cout << endl;
	cout << possiblePizzaSizesLookUp[pizzaSize];
	cout << endl;
	cout << "Your order total: $" << computePrice() <<  endl;
	return;
}

double pizza::computePrice()
{
	if (pizzaSize == possiblePizzaSizes::small)
	{
		return (10.0 + (2.0 * numberOfToppings));
	}
	else if (pizzaSize == possiblePizzaSizes::medium)
	{
		return (14.0 + (2.0 * numberOfToppings));
	}
	else if (pizzaSize == possiblePizzaSizes::large)
	{
		return (17.0 + (2.0 * numberOfToppings));
	}
	else if (pizzaSize == possiblePizzaSizes::xlarge)
	{
		return (20.0 + (2.0 * numberOfToppings));
	}
	else
	{
		cout << "Error with pizzaSize!!!";
		exit(1);
	}
}

////////////////////////////////////////////////// class above, test below /////////////////////////////////////////////////////////////////////////////////////

void askForOrder(pizza &tgt);
//precondition: customer is hungry for pizza and has money
//postcondition: lets the user choose the kind of pizza they want and creates an object for that pizza

int main()
{
	bool keepOrdering = true;
	char keepOrderingAnswer;
	pizza pizzaBeingOrdered = pizza();

	while (keepOrdering == true)
	{
		askForOrder(pizzaBeingOrdered);
		pizzaBeingOrdered.printOrderDescription();
		cout << "Care for another Pizza? (y/n): ";
		cin >> keepOrderingAnswer;
		if (keepOrderingAnswer == 'n' || keepOrderingAnswer == 'N')
			keepOrdering = false;
	}

	return 0;
}

void askForOrder(pizza &tgt)
{
	char pizzaType;
	cout << "Please enter the first letter of the type of pizza you would like (Dish, Tossed, or Pan): ";
	cin >> pizzaType;
	cout << endl;
	if (pizzaType == 'D' || pizzaType == 'd')
		tgt.setTypeOfPizza(Dish);
	else if (pizzaType == 'T' || pizzaType == 't')
		tgt.setTypeOfPizza(Tossed);
	else if (pizzaType == 'P' || 'p')
		tgt.setTypeOfPizza(Pan);
	else
	{
		cout << "Smooth move xlax. You fucked up buying pizza";
		exit(1);
	}


	int numToppings;
	cout << "Please enter the number of toppings you would like on your pizza(max of 5| $2 per topping): ";
	cin >> numToppings;
	cout << endl;
	if (numToppings > 5)
	{
		cout << "Nice Try Fatty";
		exit(1);
	}
	tgt.setNumberOfToppings(numToppings);


	pizzaToppings toppings[30];
	char toppingName;
	for (int i = 0; i < numToppings; i++)
	{
		cout << "Enter the first letter of your choice for topping number " << (i + 1) << " (peperoni, sausage, canadianBacon, onions, mushrooms): ";
		cin >> toppingName;
		cout << endl;
		if (toppingName == 'p' || toppingName == 'P')
			toppings[i] = pizzaToppings::peperoni;
		else if (toppingName == 's' || toppingName == 'S')
			toppings[i] = pizzaToppings::sausage;
		else if (toppingName == 'c' || toppingName == 'C')
			toppings[i] = pizzaToppings::canadianBacon;
		else if (toppingName == 'o' || toppingName == 'O')
			toppings[i] = pizzaToppings::onions;
		else if (toppingName == 'm' || toppingName == 'M')
			toppings[i] = pizzaToppings::mushrooms;
		else
		{
			cout << "Not A valid pizza topping. Exiting.";
			exit(1);
		}

	}
	tgt.setToppingsOnPizza(toppings, numToppings);


	possiblePizzaSizes size;
	char sizeAnswer;
	cout << "What size pizza would you like? (s $10, m $14, l $17, x $20): ";
	cin >> sizeAnswer;
	cout << endl;
	if (sizeAnswer == 's' || sizeAnswer == 'S')
		size = possiblePizzaSizes::small;
	else if (sizeAnswer == 'm' || sizeAnswer == 'M')
		size = possiblePizzaSizes::medium;
	else if (sizeAnswer == 'l' || sizeAnswer == 'L')
		size = possiblePizzaSizes::large;
	else if (sizeAnswer == 'x' || sizeAnswer == 'X')
		size = possiblePizzaSizes::xlarge;
	else
	{
		cout << "Not A valid pizza size. Exiting.";
		exit(1);
	}
	tgt.setPizzaSize(size);

}
