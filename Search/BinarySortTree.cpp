#include "StdAfx.h"
#include "BinarySortTree.h"


BinarySortTree::BinarySortTree(void)
{
	root = NULL;
}


BinarySortTree::~BinarySortTree(void)
{

}

BinarySortTreeNode* BinarySortTree::find(int data){
	BinarySortTreeNode *resPtr = NULL;
	BinarySortTreeNode *currentPtr = root;
	while(currentPtr != NULL){
		if(data == currentPtr->data){resPtr = currentPtr;break;}
		else if(data > currentPtr->data)currentPtr = currentPtr->rightchild;
		else currentPtr = currentPtr->leftchild;
	}
	return resPtr;
}

bool BinarySortTree::add(int data){
	if(root == NULL){root = new BinarySortTreeNode();root->data=data;return true;}
	if(find(data) != NULL)return false;
	BinarySortTreeNode *currentPtr = root;
	if(root == NULL){root = new BinarySortTreeNode();root->data = data;return true;}
	BinarySortTreeNode *fatherPtr = NULL;
	int direction = -1;
	while(currentPtr != NULL){
		fatherPtr = currentPtr;
		if(data > currentPtr->data){currentPtr = currentPtr->rightchild;direction = 1;}
		else {currentPtr = currentPtr->leftchild;direction = 0;}
	}
	currentPtr = new BinarySortTreeNode();
	currentPtr->data = data;
	if(direction == 0)fatherPtr->leftchild = currentPtr;
	else if(direction == 1)fatherPtr->rightchild = currentPtr;
	return true;
}

bool BinarySortTree::remove(int data){
	if(find(data) == NULL)return false;
	BinarySortTreeNode *remove_fatherPos = NULL;
	BinarySortTreeNode *removePos = root;
	int direction = -1;
	while(removePos != NULL){
		if(data == removePos->data)break;
		remove_fatherPos = removePos;
		if(data > removePos->data){direction = 1;removePos = removePos->rightchild;}
		else{direction = 0;removePos = removePos->leftchild;}
	}

	if(removePos->rightchild == NULL){
		if(direction == 0)remove_fatherPos->leftchild = removePos->leftchild;
		else if(direction == 1)remove_fatherPos->rightchild = removePos->leftchild;
		delete removePos;
	}
	else if(removePos->leftchild == NULL){
		if(direction == 0)remove_fatherPos->leftchild = removePos->rightchild;
		else if(direction == 1)remove_fatherPos->rightchild = removePos->rightchild;
		delete removePos;
	}
	//左右子都不空
	else{
		//找右子树最左节点
		BinarySortTreeNode *replacePtr = removePos->rightchild;
		BinarySortTreeNode *replaceFatherPtr = removePos;
		while(replacePtr->leftchild!=NULL){
			replaceFatherPtr = replacePtr;
			replacePtr = replacePtr->leftchild;
		}

		if(direction == 0)remove_fatherPos->leftchild = replacePtr;
		else if(direction == 1)remove_fatherPos->rightchild = replacePtr;
		delete removePos;

		if(replaceFatherPtr != removePos)replaceFatherPtr->leftchild=replacePtr->rightchild;
		return true;
	}
}