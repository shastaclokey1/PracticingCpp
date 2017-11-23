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



vector<rAryHuffmanNode> createTree(string fileName, int radix, bool distribution);
void addEncoding(rAryHuffmanNode& n, vector<rAryHuffmanNode>& c, string code);
vector<int> readSymbols(string fileName);
vector<double> readProbabilities(string fileName);
void sortVector(vector<rAryHuffmanNode>& algorithmVector);
string encodeMessage(string wordToEncode, vector<rAryHuffmanNode> encodedTree);
string searchEncodedTree(char letter, vector<rAryHuffmanNode> encodedTree);

void swap(vector<rAryHuffmanNode>& target, int i, int j);


int main()
{
	char probOrSample;
	bool probabilityDistribution = false;
	cout << "Huffman encode using sample text or probability distribuaion(enter p for probability dist/sample text is default): ";
	cin >> probOrSample;
	string txtFile;
	if (probOrSample == 'p' || probOrSample == 'P')
	{
		cout << "Enter the name of the text file for your probability distribution(ex: butts.txt): ";
		cin >> txtFile;
		probabilityDistribution = true;
	}
	else
	{
		cout << "Enter the name of the text file you would like to use as your encoding sample text(ex: butts.txt): ";
		cin >> txtFile;
	}
	cout << endl << "Enter the positive integer radix which you would like your Huffman encoding to utilize: ";
	int radix;
	cin >> radix;
	cout << endl;

	vector<rAryHuffmanNode> tree = createTree(txtFile, radix, probabilityDistribution);
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

	bool keepEncodingWords = true;
	char yOrn;
	string stringToEncode, codeForString, garbage, inputTextFile, outputTextFile;
	int messageLength;
	while (keepEncodingWords)
	{
		
		/////////////////////////////encoding messages from keyboard input
		stringToEncode = "";
		garbage = "";
		getline(cin, garbage);
		cout << "Enter a message to encode with the previously generated optimal huffman code: ";
		getline(cin, stringToEncode);
		messageLength = stringToEncode.size();
		codeForString = encodeMessage(stringToEncode, encodedTree);
		cout << "Your encodded message is: " << codeForString << endl;
		cout << "Your compression ratio is: " << codeForString.size() << "/" << messageLength*8 << endl;
		////////////////////////////////encoding messages from file input
		cout << "Enter the name of the text file you would like to encode using the huffman encoding generated above(example butts.txt): ";
		cin >> inputTextFile;
		cout << "Enter the name of the text file you would like to write your encoded text to(example wubalubadubdub.txt): ";
		cin >> outputTextFile;
		string codeToAppend = "",tempString = "";
		ofstream outputFileStream;


		ifstream symbolReader;
		symbolReader.open(inputTextFile);
		char currentSymbol;
		if (symbolReader.fail())
		{
			cout << "Input file opening failed. \n";
			exit(1);
		}

		outputFileStream.open(outputTextFile.c_str(), fstream::app);

		//put encoding alphabet at the top of the file to write to 
		for (int i = 0; i < static_cast<int>(encodedTree.size()); i++)
		{
			outputFileStream.write("\n", string("\n").size());
			outputFileStream.write("Source symbol: ", string("Source symbol: ").size());
			tempString.push_back(encodedTree[i].getSource());
			outputFileStream.write(tempString.c_str(), tempString.size());
			tempString = "";
			outputFileStream.write(" Probability: ", string(" Probability: ").size());
			outputFileStream.write(to_string(encodedTree[i].getProb()).c_str(), to_string(encodedTree[i].getProb()).size());
			outputFileStream.write(" Encoding: ", string(" Encoding: ").size());
			outputFileStream.write(encodedTree[i].getEncoding().c_str(), encodedTree[i].getEncoding().size());
		}
		outputFileStream.write("\n", string("\n").size());
		outputFileStream.write("\n", string("\n").size());


		int sizeOfMessage = 0, sizeOfExtAsciiMessage = 0;
		while (!symbolReader.eof())
		{
			symbolReader.get(currentSymbol);
			tempString = "";
			codeToAppend = encodeMessage(tempString + currentSymbol, encodedTree);
			sizeOfMessage += codeToAppend.size();
			sizeOfExtAsciiMessage += 8;
			outputFileStream.write(codeToAppend.c_str(), codeToAppend.size());
			outputFileStream.flush();
		}
		outputFileStream.write("\n", string("\n").size());
		outputFileStream.write("\n", string("\n").size());
		outputFileStream.write("Compression Ratio: ", string("Compression Ratio: ").size());
		outputFileStream.write(to_string(sizeOfMessage).c_str(), to_string(sizeOfMessage).size());
		outputFileStream.write("/", string("/").size());
		outputFileStream.write(to_string(sizeOfExtAsciiMessage).c_str(), to_string(sizeOfExtAsciiMessage).size());
		outputFileStream.close();
		symbolReader.close();

		cout << "Encode another Message?(y/n): ";
		cin >> yOrn;
		if (yOrn == 'n' || yOrn == 'N')
			keepEncodingWords = false;
	}

	cout << "Thank you for using huffman encoding! Press enter to exit.";

	int gbg;

	cin >> gbg;
	
	return 0;
}


vector<rAryHuffmanNode> createTree(string fileName, int radix, bool distribution)
{
	vector<int> mainSymbolSet;
	vector<double> mainProbabilitySet;
	if (distribution == true)
	{
		ifstream symbolReader;
		symbolReader.open(fileName);
		char currentLetter,garbage;
		string garbageString;
		double currentProbability;
		if (symbolReader.fail())
		{
			cout << "Input file opening failed. \n";
			exit(1);
		}

		while (!symbolReader.eof())
		{
			symbolReader.get(currentLetter);
			symbolReader.get(garbage);
			mainSymbolSet.push_back(static_cast<int>(currentLetter));
			symbolReader >> currentProbability;
			if (!symbolReader)
			{
				cout << "Symbol reader failed to read probability. \n";
				exit(1);
			}
			mainProbabilitySet.push_back(currentProbability);
			getline(symbolReader, garbageString);
		}
		symbolReader.close();
	}
	else
	{
		mainSymbolSet = readSymbols(fileName);
		mainProbabilitySet = readProbabilities(fileName);
	}
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
	int minValInd;
	for (int i = 0; i < algorithmVector.size() - 1; i++)
	{
		minValInd = i;
		for (int j = i; j < algorithmVector.size(); j++)
			if (algorithmVector[j].getProb() < algorithmVector[minValInd].getProb())
				minValInd = j;
		if (minValInd != i)
			swap(algorithmVector, i, minValInd);
	}
	
}

string encodeMessage(string wordToEncode, vector<rAryHuffmanNode> encodedTree)
{
	string code = "";
	for (int i = 0; i < wordToEncode.length(); i++)
	{
		code.append(searchEncodedTree(wordToEncode[i], encodedTree));
	}
	return code;
}

string searchEncodedTree(char letter, vector<rAryHuffmanNode> encodedTree)
{
	string codeWord = "error";
	for (int i = 0; i < encodedTree.size(); i++)
	{
		if (letter == encodedTree[i].getSource())
			codeWord = encodedTree[i].getEncoding();
	}
	return codeWord;
}

/*This function swaps two elements in a vector
target -> Vector of interest
i, j -> indicies for elements in target to swap*/
void swap(vector<rAryHuffmanNode> &target, int i, int j)
{
	rAryHuffmanNode temp = target[i];
	target[i] = target[j];
	target[j] = temp;
}
