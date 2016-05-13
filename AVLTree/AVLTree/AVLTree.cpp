// AVLTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "BST.h"
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

template<class T>
void outputV(vector<T> &vect){
	for (int i = 0; i < vect.size(); ++i){
		cout << vect[i] << endl;
	}
}

class AVL{
protected:
	struct AVLNode{
		int height;
		int val;
		AVLNode *left;
		AVLNode *right;
		AVLNode(){ height = 1; val = 0; left = nullptr; right = nullptr; }
		AVLNode(int x){ val = x; height = 1; left = nullptr; right = nullptr; }
	};
	AVLNode *root;
	void rotateL(AVLNode *troot); 
	void rotateR(AVLNode *troot);
	void rotateLR(AVLNode *troot);
	void rotateRL(AVLNode *troot);
	int height(AVLNode *troot);
public:
	AVL(){
		root = nullptr;
	}
	~AVL(){
		if (root == nullptr)return;
		AVLNode *curr = root;
		queue<AVLNode*> tnQueue;
		tnQueue.push(root);
		while (!tnQueue.empty()){
			curr = tnQueue.front();
			tnQueue.pop();
			if (curr->left != nullptr)tnQueue.push(curr->left);
			if (curr->right != nullptr)tnQueue.push(curr->right);
			delete curr;
		}
	}
	void insert(int val);
	bool remove(int val);
	int height(){
		return height(root);
	}
};
void AVL::rotateL(AVLNode *troot){
	AVLNode *subL = troot->right;
	swap(troot->val,subL->val);
	troot->right = subL->right;
	subL->right = subL->left;
	subL->left = troot->left;
	troot->left = subL;
	--subL->height;
}
void AVL::rotateR(AVLNode *troot){
	AVLNode *subR = troot->left;
	swap(troot->val, subR->val);
	troot->left = subR->left;
	subR->left = subR->right;
	subR->right = troot->right;
	troot->right = subR;
	--subR->height;
}
void AVL::rotateLR(AVLNode *troot){
	AVLNode *subL = troot->left, *subR = subL->right,*tempPtr;
	swap(troot->val,subR->val);
	tempPtr = troot->right;
	troot->right = subR;
	subL->right = subR->left;
	subR->left = subR->right;
	subR->right = tempPtr;
	--subL->height;
}
void AVL::rotateRL(AVLNode *troot){
	AVLNode *subR = troot->right, *subL = subR->left, *tempPtr;
	swap(troot->val, subL->val);
	tempPtr = troot->left;
	troot->left = subL;
	subR->left = subL->right;
	subL->right = subL->left;
	subL->left = tempPtr;
	--subR->height;
}
void AVL::insert(int val){
	AVLNode *currPtr = root,*prePtr=nullptr;
	stack<AVLNode *>avlStack;
	while (currPtr != nullptr){
		prePtr = currPtr;
		avlStack.push(currPtr);
		if (currPtr->val == val)return;
		else if (val < currPtr->val)currPtr=currPtr->left;
		else currPtr=currPtr->right;
	}
	if (prePtr == nullptr){
		root = new AVLNode(val); 
		return;
	}
	if (val < prePtr->val){
		prePtr->left = new AVLNode(val);
	}
	else{
		prePtr->right = new AVLNode(val);
	}
	prePtr->height = 2;
	avlStack.pop();
	while (!avlStack.empty()){
		currPtr = avlStack.top();
		avlStack.pop();
		int lHeight, rHeight;
		if (currPtr->left == nullptr)lHeight = 0;
		else lHeight = currPtr->left->height;
		if (currPtr->right == nullptr)rHeight = 0;
		else rHeight = currPtr->right->height;
		if (lHeight == rHeight){
			break;
		}
		else if (lHeight - rHeight == 1){
			currPtr->height = lHeight + 1;
		}
		else if (rHeight - lHeight == 1){
			currPtr->height = rHeight + 1;
		}
		else{//abs()==2
			if (lHeight - rHeight == 2){
				if (currPtr->left->left == nullptr)lHeight = 0;
				else lHeight = currPtr->left->left->height;
				if (currPtr->left->right == nullptr)rHeight = 0;
				else rHeight = currPtr->left->right->height;
				if (lHeight>rHeight)rotateR(currPtr);
				else rotateLR(currPtr);
			}
			else{
				if (currPtr->right->left == nullptr)lHeight = 0;
				else lHeight = currPtr->right->left->height;
				if (currPtr->right->right == nullptr)rHeight = 0;
				else rHeight = currPtr->right->right->height;
				if (lHeight>rHeight)rotateRL(currPtr);
				else rotateL(currPtr);
			}
			break;
		}

	}
}
bool AVL::remove(int val){
	if (root == nullptr){
		return false;
	}
	stack<AVLNode *>avlStack;
	AVLNode *curr = root;
	while (curr != nullptr){
		if (val == curr->val)break;
		else if (val < curr->val){
			avlStack.push(curr);
			curr = curr->left;
		}
		else{
			avlStack.push(curr);
			curr = curr->right;
		}
	}
	if (curr == nullptr)return false;
	if (curr->left == nullptr&&curr->right == nullptr){
		if (avlStack.empty()){
			delete curr;
			root = nullptr;
		}
		else if (avlStack.top()->left == curr){
			avlStack.top()->left = nullptr;
			delete curr;
		}
		else if (avlStack.top()->right == curr){
			avlStack.top()->right = nullptr;
			delete curr;
		}
	}
	else if (curr->left != nullptr&&curr->right == nullptr){
		if (avlStack.empty()){
			root = curr->left;
			delete curr;
		}
		else if (avlStack.top()->left == curr){
			avlStack.top()->left = curr->left;
			delete curr;
		}
		else if (avlStack.top()->right == curr){
			avlStack.top()->right = curr->left;
			delete curr;
		}
	}
	else if (curr->left == nullptr&&curr->right != nullptr){
		if (avlStack.empty()){
			root = curr->right;
			delete curr;
		}
		else if (avlStack.top()->left == curr){
			avlStack.top()->left = curr->right;
			delete curr;
		}
		else if (avlStack.top()->right == curr){
			avlStack.top()->right = curr->right;
			delete curr;
		}
	}
	else{
		AVLNode *successive = curr->right;
		while (successive->left != nullptr)successive = successive->left;
		int succVal = successive->val;
		bool res = remove(successive->val);
		curr->val = succVal;
		return res;
	}
	//adjust
	while (!avlStack.empty()){
		AVLNode *currPtr = avlStack.top();
		avlStack.pop();
		int lHeight, rHeight;
		if (currPtr->left == nullptr)lHeight = 0;
		else lHeight = currPtr->left->height;
		if (currPtr->right == nullptr)rHeight = 0;
		else rHeight = currPtr->right->height;
		if (lHeight == rHeight){
			currPtr->height = lHeight + 1;
		}
		else if (abs(lHeight - rHeight) == 1){
			break;
		}
		else{//abs()==2
			if (lHeight - rHeight == 2){
				if (currPtr->left->left == nullptr)lHeight = 0;
				else lHeight = currPtr->left->left->height;
				if (currPtr->left->right == nullptr)rHeight = 0;
				else rHeight = currPtr->left->right->height;
				if (lHeight >= rHeight)rotateR(currPtr);
				else rotateLR(currPtr);
			}
			else{
				if (currPtr->right->left == nullptr)lHeight = 0;
				else lHeight = currPtr->right->left->height;
				if (currPtr->right->right == nullptr)rHeight = 0;
				else rHeight = currPtr->right->right->height;
				if (rHeight >= lHeight)rotateL(currPtr);
				else rotateRL(currPtr);
			}
			break;
		}
	}
	return true;
}
int AVL::height(AVLNode *troot){
	if (troot == nullptr)return 0; 
	if (troot->val > 0)return 1 + height((AVLNode *)troot->right);
	else return 1 + height((AVLNode *)troot->left);
}

int _tmain(int argc, _TCHAR* argv[])
{
	AVL avl;
	avl.insert(1); 
	avl.insert(2); 
	avl.insert(3); 
	avl.insert(4); 
	avl.insert(5);
	avl.insert(10); 
	avl.insert(9); 
	avl.insert(8); 
	avl.insert(7); 
	avl.insert(6);

	avl.remove(1);
	avl.remove(7);
	while (getchar() != '\n');
	getchar();
	return 0;
}

