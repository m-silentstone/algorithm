#pragma once
#include <queue>
using namespace std;

class ClueBinaryTreeNode{
public:
	int data;
	ClueBinaryTreeNode *leftchild;
	ClueBinaryTreeNode *rightchild;
	//tag=1:ÏßË÷    tag=0:¶ù×Ó
	int ltag;
	int rtag;
	ClueBinaryTreeNode(){data=0;leftchild=nullptr;rightchild=nullptr;ltag=1;rtag=1;}
	ClueBinaryTreeNode(int _data){ data = _data; leftchild = nullptr; rightchild = nullptr; ltag = 1; rtag = 1; }
	
};

class BinaryTreeNode{
public:
	int data;
	BinaryTreeNode *leftchild;
	BinaryTreeNode *rightchild;
	BinaryTreeNode(){ data = 0; leftchild = nullptr; rightchild = nullptr;}
	BinaryTreeNode(int _data){ data = _data; leftchild = nullptr; rightchild = nullptr;}

};

class ClueBinaryTree
{
private:
	ClueBinaryTreeNode *root;
	void clueDeal(ClueBinaryTreeNode *curr, ClueBinaryTreeNode *&pre);
	void clear(ClueBinaryTreeNode *_root);
public:
	ClueBinaryTree(void){root = NULL;}
	~ClueBinaryTree(void);
	ClueBinaryTreeNode *getRoot(){return root;}

	//true:copy successfully  false:copy failed
	bool copyFromBinaryTree(BinaryTreeNode *btRoot);
	ClueBinaryTreeNode *first(ClueBinaryTreeNode *current);
	ClueBinaryTreeNode *last(ClueBinaryTreeNode *current);
	ClueBinaryTreeNode *next(ClueBinaryTreeNode *current);
	ClueBinaryTreeNode *prev(ClueBinaryTreeNode *current);
	void inorder(void (*visit)(ClueBinaryTreeNode *p));
	void preorder(void (*visit)(ClueBinaryTreeNode *p));
	void postorder(void (*visit)(ClueBinaryTreeNode *p));
	ClueBinaryTreeNode *findparent(ClueBinaryTreeNode *current);

	void insertRight(ClueBinaryTreeNode *father,int data);
	void insertLeft(ClueBinaryTreeNode *father,int data);
	void insertRoot(int data);
	void removeNode(ClueBinaryTreeNode *removePtr);
	void clear();
};

