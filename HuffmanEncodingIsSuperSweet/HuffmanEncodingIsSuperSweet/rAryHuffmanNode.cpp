#include "stdafx.h"
#include "rAryHuffmanNode.h"

rAryHuffmanNode::rAryHuffmanNode(const vector<rAryHuffmanNode>& n, double p, char s)
{
	subnodes = n;
	prob = p;
	source = s;
}

rAryHuffmanNode::rAryHuffmanNode(double p, char s)
{
	subnodes = {};
	prob = p;
	source = s;
}

void rAryHuffmanNode::setSubnodes(const vector<rAryHuffmanNode>& n)
{
	subnodes = n;
}

void rAryHuffmanNode::setProb(double p)
{
	prob = p;
}

void rAryHuffmanNode::setSource(char s)
{
	source = s;
}

void rAryHuffmanNode::setEncoding(const string & c)
{
	encoding = c;
}

void rAryHuffmanNode::setLenth(int l)
{
	leng = l;
}

vector<rAryHuffmanNode> rAryHuffmanNode::getSubnodes()
{
	return subnodes;
}

string rAryHuffmanNode::getEncoding()
{
	return encoding;
}

int rAryHuffmanNode::getLength()
{
	return leng;
}

char rAryHuffmanNode::getSource()
{
	return source;
}

double rAryHuffmanNode::getProb()
{
	return prob;
}

bool rAryHuffmanNode::isLeaf()
{
	if (subnodes.size() == 0)
		return true;
	else
		return false;
}








