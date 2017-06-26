// randomSentenceGeneratorUsingVectors.cpp : Defines the entry point for the console application.
//
/*allows user to specify how many words their nonsence sentence will be, then asks them to enter that many words. program randomly orders these words in a list*/
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;





class nonsencePhrase
{
public:
	nonsencePhrase();

	void askForPhrase();
	//postcondition: phraseContainer is now full of random silly words

	void scrambleWords();
	//precondition: phraseContainer has been filled with words
	//postCondition: the words in phraseContainer have been jumbled up

	void displayFunnyPhrase();
	//precondition: phraseContainer has been filled with silliness
	//postCondition: the words in phraseContainer are printed to the console

	void addPhraseToParagraph();
	//precondition: phrasecontainer is filled
	//postcondition: phrasecontainer is coppied and added into paragraphContainer

	void displayParagraph();
	//precondition: paragraphContainer has some phrases in it
	//postcondition: all the phrases are printed to the screen

	void reset();
	//postcondition: phraseContainer is cleared and will have size 0



private:
	vector<string> phraseContainer;
	vector<vector<string>> paragraphContainer;


};

nonsencePhrase::nonsencePhrase()
{/*intentionally empty*/
}

void nonsencePhrase::askForPhrase()
{
	int numberOfRandomWords;
	string userRandomWord;
	cout << "How many words do you want in your randomized phrase?: ";
	cin >> numberOfRandomWords;
	cout << endl;
	for (int i = 0; i < numberOfRandomWords; i++)
	{
		cout << "Please enter random word number " << i + 1 << ": ";
		cin >> userRandomWord;
		phraseContainer.push_back(userRandomWord);
		cout << endl;
	}

}

void nonsencePhrase::scrambleWords()
{
	int randomIndex1;
	int randomIndex2;
	string temp;
	for (int i = 0; i < (10 * phraseContainer.size()); i++)
	{
		randomIndex1 = rand() % phraseContainer.size();
		randomIndex2 = rand() % phraseContainer.size();
		temp = phraseContainer[randomIndex1];
		phraseContainer[randomIndex1] = phraseContainer[randomIndex2];
		phraseContainer[randomIndex2] = temp;
	}
}

void nonsencePhrase::displayFunnyPhrase()
{
	for (int i = 0; i < phraseContainer.size(); i++)
	{
		cout << phraseContainer[i] << " ";
	}
	cout << endl << endl;
}

void nonsencePhrase::reset()
{
	phraseContainer.clear();
}

void nonsencePhrase::addPhraseToParagraph()
{
	paragraphContainer.push_back(phraseContainer);
}

void nonsencePhrase::displayParagraph()
{
	for (int i = 0; i < paragraphContainer.size(); i++)
	{
		for (int j = 0; j < paragraphContainer[i].size(); j++)
		{
			cout << paragraphContainer[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}


int main()
{
	nonsencePhrase wubalubadubdub = nonsencePhrase();
	char yOrN;

	while (true)
	{
		wubalubadubdub.reset();
		wubalubadubdub.askForPhrase();
		wubalubadubdub.scrambleWords();
		wubalubadubdub.displayFunnyPhrase();
		wubalubadubdub.addPhraseToParagraph();

		cout << "Make another sentence??(y/n): ";
		cin >> yOrN;
		if (yOrN == 'n' || yOrN == 'N')
			break;
	}
		cout << "For your ammusement, here are all of your beautiful creations." << endl;
		wubalubadubdub.displayParagraph();
		cout << "Type wooooo to exit: ";
		cin >> yOrN;

	return 0;
}