#include "stdafx.h"
#include "SegmentTree.h"


SegmentTree::SegmentTree()
{
	root = nullptr;
}


SegmentTree::~SegmentTree()
{
	clear();
}
void SegmentTree::clear(){
	if (root == nullptr)return;
	stack<SegmentTreeNode *> stStack;
	stStack.push(root);
	while (!stStack.empty()){
		SegmentTreeNode *curr = stStack.top();
		stStack.pop();
		if (curr->rightchild != nullptr)stStack.push(curr->rightchild);
		if (curr->leftchild != nullptr)stStack.push(curr->leftchild);
		delete curr;
	}
	root = nullptr;
}
void SegmentTree::build(int l, int r){
	clear();
	root = buildIn(l,r);
}

SegmentTreeNode* SegmentTree::buildIn(int l, int r){
	if (l >= r)return nullptr;
	SegmentTreeNode *ptrNode = new SegmentTreeNode(l,r);
	if (l + 1 < r){
		ptrNode->leftchild = buildIn(l,(l+r)/2);
		ptrNode->rightchild = buildIn((l + r) / 2, r);
	}
	return ptrNode;
}

void SegmentTree::insert(int l, int r){
	insert(l,r,root);
}
void SegmentTree::remove(int l, int r){
	remove(l, r, root);
}
int SegmentTree::query(vector<int> &coord){
	return query(coord,root);
}
void SegmentTree::insert(int l, int r, SegmentTreeNode *_root){
	if (_root == nullptr)return;
	if (_root->info == 1)return;
	int mid = (_root->left + _root->right) / 2;
	if (l <= _root->left && r >= _root->right)_root->info=1;
	else{
		if (l < mid)insert(l, r, _root->leftchild);
		if (r > mid)insert(l, r, _root->rightchild);
		if (_root->leftchild->info == 1 && _root->rightchild->info == 1)_root->info = 1;
	}

}
void SegmentTree::remove(int l, int r, SegmentTreeNode *_root){
	if (_root == nullptr)return;
	int mid = (_root->left + _root->right) / 2;
	if (_root->info==1){
		if(_root->leftchild!=nullptr)_root->leftchild->info = 1;
		if (_root->rightchild != nullptr)_root->rightchild->info = 1;
		_root->info = 0;
	}
	if (l < mid)remove(l, r, _root->leftchild);
	if (r > mid)remove(l, r, _root->rightchild);
}
int SegmentTree::query(vector<int> &coord, SegmentTreeNode *_root){
	if (_root == nullptr)return 0;
	if (_root->info !=0)return coord[_root->right] - coord[_root->left];
	else{
		return query(coord,_root->leftchild) + query(coord,_root->rightchild);
	}
}