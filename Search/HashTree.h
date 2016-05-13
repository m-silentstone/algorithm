#pragma once
#include <vector>
#include <iostream>
using namespace std;

class HashTreeNode{
public:
	int data;
	int level;
	bool isOccupy;
	vector<HashTreeNode *> vect_children;
	static int primeNum[10];
};

class HashTree
{
private:
	HashTreeNode *root;
public:
	void add(int data);
	bool remove(int data);
	HashTreeNode* find(int data);

	HashTree(void);
	~HashTree(void);
};

