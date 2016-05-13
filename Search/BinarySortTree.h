#pragma once

class BinarySortTreeNode{
public:
	int data;
	BinarySortTreeNode *leftchild;
	BinarySortTreeNode *rightchild;
	BinarySortTreeNode(){data=0;leftchild=NULL;rightchild=NULL;}
};

class BinarySortTree
{
private:
	BinarySortTreeNode *root;
public:
	BinarySortTree(void);
	~BinarySortTree(void);
	BinarySortTreeNode* find(int data);
	bool add(int data);
	bool remove(int data);

};

