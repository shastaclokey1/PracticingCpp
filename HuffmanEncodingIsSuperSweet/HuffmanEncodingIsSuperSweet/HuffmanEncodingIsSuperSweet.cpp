// HuffmanEncodingIsSuperSweet.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include "rAryHuffmanNode.h"

using namespace std;



vector<rAryHuffmanNode> createTree(string fileName, int radix);
void addEncoding(rAryHuffmanNode& n, vector<rAryHuffmanNode>& c, string code);
vector<int> readSymbols(string fileName);
vector<double> readProbabilities(string fileName);
void sortVector(vector<rAryHuffmanNode>& algorithmVector);


int main()
{
	cout << "Enter the name of the text file you would like to Huffman encode(ex: butts.txt): ";
	string txtFile;
	cin >> txtFile;
	cout << endl << "Enter the positive integer radix which you would like your Huffman encoding to utilize: ";
	int radix;
	cin >> radix;
	cout << endl;

	vector<rAryHuffmanNode> tree = createTree(txtFile, radix); //TODO: create function to generate huffman tree from input text file
	vector<rAryHuffmanNode> encodedTree; 
	addEncoding(tree[0], encodedTree, "");
	double ACWL = 0;
	double entropy = 0;



	for (int i = 0; i < static_cast<int>(encodedTree.size()); i++)
	{
		ACWL = ACWL + (encodedTree[i].getEncoding().length()*encodedTree[i].getProb());
		entropy = entropy + (encodedTree[i].getProb()*(log(1 / encodedTree[i].getProb()) / log(radix)));
	}

	for (int i = 0; i < static_cast<int>(encodedTree.size()); i++)
	{
		cout << "Source symbol: " << encodedTree[i].getSource() << " Probability: " << encodedTree[i].getProb() << " Encoding: " << encodedTree[i].getEncoding() << endl;
	}

	cout << endl << endl;
	cout << "Average Code Word Length: " << ACWL << endl;
	cout << "Entropy: " << entropy << endl;

	while (true)
	{

	}
	
	return 0;
}


vector<rAryHuffmanNode> createTree(string fileName, int radix)
{
	vector<int> mainSymbolSet = readSymbols(fileName);
	vector<double> mainProbabilitySet = readProbabilities(fileName);
	vector<rAryHuffmanNode> algorithmVector;

	for (int i = 0; i < static_cast<int>(mainSymbolSet.size()); i++)
	{
		algorithmVector.push_back(rAryHuffmanNode(mainProbabilitySet[i], static_cast<char>(mainSymbolSet[i])));
	}
	
	sortVector(algorithmVector);


	for (int i = 0; i < static_cast<int>(algorithmVector.size()); i++)
	{
		cout << "Source symbol: " << algorithmVector[i].getSource() << " Probability: " << algorithmVector[i].getProb() << endl;
	}

	int r = radix;
	int n = static_cast<int>(algorithmVector.size());
	int firstNodeSize;
	int x = 1;
	int modCounter = 0;

	while (x < n)
	{
		modCounter++;
		x = 1 + ((r - 1)*modCounter);
	}
	x = x - (r - 1);
	cout << static_cast<int>(algorithmVector.size()) << endl;
	cout << x << endl;

	firstNodeSize = n - (x - 1);

	cout << firstNodeSize << endl << endl << endl << endl;

	vector<rAryHuffmanNode> node;
	double probSum = 0;

	for (int i = 0; i < firstNodeSize; i++)
	{
		node.push_back(algorithmVector[i]);
		probSum += algorithmVector[i].getProb();
	}

	for (int i = 0; i < firstNodeSize; i++)
		algorithmVector.erase(algorithmVector.begin());

	char empty = '\0';
	rAryHuffmanNode rAryHNode = rAryHuffmanNode(node, probSum, empty);
	algorithmVector.push_back(rAryHNode);

	sortVector(algorithmVector);

	for (int i = 0; i < static_cast<int>(algorithmVector.size()); i++)
	{
		cout << "Source symbol: " << algorithmVector[i].getSource() << " Probability: " << algorithmVector[i].getProb() << endl;
	}
	cout << endl << endl << endl;

	while (static_cast<int>(algorithmVector.size()) > 1)
	{
		node.clear();
		probSum = 0;

		for (int i = 0; i < r; i++)
		{
			node.push_back(algorithmVector[i]);
			probSum += algorithmVector[i].getProb();
		}

		if (static_cast<int>(algorithmVector.size()) >= r)
			for (int i = 0; i < r; i++)
				algorithmVector.erase(algorithmVector.begin());
		else
			for (int i = 0; i < static_cast<int>(algorithmVector.size()); i++)
				algorithmVector.erase(algorithmVector.begin());

		empty = '\0';
		rAryHNode = rAryHuffmanNode(node, probSum, empty);
		algorithmVector.push_back(rAryHNode);

		sortVector(algorithmVector);

		for (int i = 0; i < static_cast<int>(algorithmVector.size()); i++)
		{
			cout << "Source symbol: " << algorithmVector[i].getSource() << " Probability: " << algorithmVector[i].getProb() << endl;
		}
		cout << endl << endl << endl;


	}

	return algorithmVector;


}

void addEncoding(rAryHuffmanNode& n, vector<rAryHuffmanNode>& c, string code)
{
	int counter = 0;
	n.setEncoding(code);
	if (n.getSource() != '\0')
		c.push_back(n);
	else
	{
		while (counter < static_cast<int>(n.getSubnodes().size()))
		{
			string temp = code + to_string(counter);
			addEncoding(n.getSubnodes()[counter], c, temp);
			counter++;
		}
	}
}

vector<int> readSymbols(string fileName)
{
	vector<int> SymbolSet;

	int asciiArray[10000] = { 0 };
	char singleLetter;

	ifstream symbolReader;
	symbolReader.open(fileName);
	if (symbolReader.fail())
	{
		cout << "Input file opening failed. \n";
		exit(1);
	}

	while (!symbolReader.eof())
	{
		symbolReader.get(singleLetter);
		asciiArray[static_cast<int>(singleLetter)]++;
	}

	for (int i = 0; i < 732; i++)
	{
		if (asciiArray[i] != 0)
			SymbolSet.push_back(i);
	}

	return SymbolSet;
}

vector<double> readProbabilities(string fileName)
{
	vector<double> ProbabilitySet;

	int asciiArray[10000] = { 0 };
	char singleLetter;
	double totalSymbols = 0;

	ifstream symbolReader;
	symbolReader.open(fileName);
	if (symbolReader.fail())
	{
		cout << "Input file opening failed. \n";
		exit(1);
	}

	while (!symbolReader.eof())
	{
		symbolReader.get(singleLetter);
		asciiArray[static_cast<int>(singleLetter)]++;
	}

	for (int i = 0; i < 732; i++)
	{
		if (asciiArray[i] != 0)
			ProbabilitySet.push_back(asciiArray[i]);
	}

	for (int i = 0; i < static_cast<int>(ProbabilitySet.size()); i++)
	{
		totalSymbols += ProbabilitySet[i];
	}
	for (int i = 0; i < static_cast<int>(ProbabilitySet.size()); i++)
	{
		ProbabilitySet[i] = ProbabilitySet[i] / totalSymbols;
	}
	symbolReader.close();

	return ProbabilitySet;
}

void sortVector(vector<rAryHuffmanNode>& algorithmVector)
{
	bool sorted = false;
	rAryHuffmanNode temp;
	while (sorted = false)
	{
		sorted = true;
		for (int j = 1; j < static_cast<int>(algorithmVector.size()) - 1; j++)
		{
			if (algorithmVector[j - 1].getProb() > algorithmVector[j].getProb())
			{
				//time to swap
				temp = algorithmVector[j - 1];
				algorithmVector[j - 1] = algorithmVector[j];
				algorithmVector[j] = temp;
				sorted = false;
			}
		}
	}
}