#include "StdAfx.h"
#include "HashTree.h"

int HashTreeNode::primeNum[10] = {2,3,5,7,11,13,17,19,23,29};

HashTree::HashTree(void)
{
	root = new HashTreeNode();
	root->isOccupy = false;
	root->level=0;
}

HashTree::~HashTree(void)
{
}

void HashTree::add(int data){
	
	HashTreeNode *currentPtr = root;
	while(currentPtr->isOccupy == true){
		if(currentPtr->data == data)return;
		if(currentPtr->level>9){
			cout<<"Too many data,HashTree overflow!"<<endl;
			return;
		}
		int direction = data%(HashTreeNode::primeNum[currentPtr->level]);
		currentPtr = currentPtr->vect_children[direction];
	}

	currentPtr->data = data;
	currentPtr->isOccupy = true;
	for(int i=0;i<HashTreeNode::primeNum[currentPtr->level];i++){
		HashTreeNode *insertNodePtr = new HashTreeNode();
		insertNodePtr->isOccupy = false;
		insertNodePtr->level = currentPtr->level+1;
		currentPtr->vect_children.push_back(insertNodePtr);
	}



}

bool HashTree::remove(int data){
	HashTreeNode *currentPtr = root;
	while(currentPtr!=NULL){
		if(currentPtr->isOccupy == true && currentPtr->data == data){
			currentPtr->data = 0;
			currentPtr->isOccupy = false;
			return true;
		}
		if(currentPtr->vect_children.size()==0)return false;
		int direction = data%(HashTreeNode::primeNum[currentPtr->level]);
		currentPtr = currentPtr->vect_children[direction];
	}
	return false;
}
HashTreeNode* HashTree::find(int data){
	HashTreeNode *currentPtr = root;
	while(currentPtr!=NULL){
		if(currentPtr->isOccupy == true && currentPtr->data == data){
			return currentPtr;
		}
		if(currentPtr->vect_children.size()==0)return NULL;
		int direction = data%(HashTreeNode::primeNum[currentPtr->level]);
		currentPtr = currentPtr->vect_children[direction];
	}
	return NULL;
}