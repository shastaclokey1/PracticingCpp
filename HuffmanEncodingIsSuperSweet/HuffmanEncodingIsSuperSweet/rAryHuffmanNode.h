#pragma once
#ifndef RARY_HUFFMAN_NODE_H 
#define RARY_HUFFMAN_NODE_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class rAryHuffmanNode
{
public:
	rAryHuffmanNode(const vector<rAryHuffmanNode>& n, double p, char s); //constructor to initialize node
	rAryHuffmanNode(double p, char s); //constructor to initialize node
	rAryHuffmanNode() { subnodes = {};/*intentionally empty constructor*/ }
	
	void setSubnodes(const vector<rAryHuffmanNode>& n);
	void setProb(double p);
	void setSource(char s);
	void setEncoding(const string& c);
	void setLenth(int l);

	vector<rAryHuffmanNode> getSubnodes();
	string getEncoding();
	int getLength();
	char getSource(); //gets the source symbol of the node(only use for leaves)
	double getProb();
	
	bool isLeaf(); //check to see if node is at the bottom of the tree


private: 
	vector<rAryHuffmanNode> subnodes;
	char source;
	double prob;
	string encoding;
	int leng; //TODO: rename when we find out what this length is refering to
};


#endif 
