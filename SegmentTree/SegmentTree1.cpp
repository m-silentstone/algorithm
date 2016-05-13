#include "stdafx.h"
#include "SegmentTree1.h"

SegmentTree1::SegmentTree1()
{
	root = nullptr;
}


SegmentTree1::~SegmentTree1()
{
	//clear();
}
//void SegmentTree1::clear(){
//	if (root == nullptr)return;
//	stack<SegmentTreeNode1 *> stStack;
//	stStack.push(root);
//	while (!stStack.empty()){
//		SegmentTreeNode1 *curr = stStack.top();
//		stStack.pop();
//		if (curr->rightchild != nullptr)stStack.push(curr->rightchild);
//		if (curr->leftchild != nullptr)stStack.push(curr->leftchild);
//		delete curr;
//	}
//	root = nullptr;
//}
void SegmentTree1::build(vector<int> &data){
	//clear();
	root = buildIn(0, data.size()-1, data);
}

SegmentTreeNode1* SegmentTree1::buildIn(int l, int r, vector<int> &data){
	if (l > r)return nullptr;
	SegmentTreeNode1 *ptrNode = new SegmentTreeNode1(l, r);
	if (l == r){
		ptrNode->minNum = data[l];
		ptrNode->maxNum = data[l];
	}
	else{
		ptrNode->leftchild = buildIn(l, (l + r) / 2,data);
		ptrNode->rightchild = buildIn((l + r) / 2+1, r,data);
		ptrNode->maxNum = max(ptrNode->leftchild->maxNum, ptrNode->rightchild->maxNum);
		ptrNode->minNum = min(ptrNode->leftchild->minNum, ptrNode->rightchild->minNum);
	}
	return ptrNode;
}

//void SegmentTree1::add(int l, int r, int num){
//
//}
//void SegmentTree1::add(int l, int r, int num,SegmentTreeNode1 *_root){
//
//}
int SegmentTree1::queryDist(int l, int r){
	int maxNum = queryMax(l,r,root);
	int minNum = queryMin(l, r, root);
	return maxNum - minNum;
}
int SegmentTree1::queryMax(int l, int r, SegmentTreeNode1* _root){
	if (_root->left == _root->right)return _root->maxNum;
	if (l <= _root->left&&r >= _root->right)return _root->maxNum;
	else{
		int mid = (_root->left + _root->right) / 2;
		int maxNum = INT_MIN;
		if (l <= mid)maxNum = queryMax(l,r,_root->leftchild);
		if (r > mid)maxNum = max(maxNum,queryMax(l, r, _root->rightchild));
		return maxNum;
	}
}

int SegmentTree1::queryMin(int l, int r, SegmentTreeNode1* _root){
	if (_root->left == _root->right)return _root->minNum;
	if (l <= _root->left&&r >= _root->right)return _root->minNum;
	else{
		int mid = (_root->left + _root->right) / 2;
		int minNum = INT_MAX;
		if (l <= mid)minNum = queryMin(l, r, _root->leftchild);
		if (r > mid)minNum = min(minNum, queryMin(l, r, _root->rightchild));
		return minNum;
	}
}