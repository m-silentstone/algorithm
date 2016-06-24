#pragma once
#include <math.h>
#include <assert.h>
const int M = 6;
class BTreeNode{
public:
	BTreeNode *parent;
	int dataSize;
	int dataArr[M];
	BTreeNode *ptrArr[M+1];
	BTreeNode(){
		parent = nullptr;
		dataSize = 0;
		for (int i = 0; i < M+1; ++i)ptrArr[i] = nullptr;
	}
};

class BTree
{
private:
	BTreeNode *root;
	void clear(BTreeNode *_root);
	BTreeNode* insertToNode(BTreeNode *_root, int data, BTreeNode* child1, BTreeNode* child2);
	void removeFromNode(BTreeNode* _root, int data);
public:
	BTree();
	~BTree();
	bool search(int data);
	bool insert(int data);
	bool remove(int data);

};

