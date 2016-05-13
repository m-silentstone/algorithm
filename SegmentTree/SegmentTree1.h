#pragma once
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
using namespace std;

class SegmentTreeNode1{
public:
	int left;
	int right;
	int minNum;
	int maxNum;
	SegmentTreeNode1 *leftchild;
	SegmentTreeNode1 *rightchild;
	SegmentTreeNode1(){ left = 0; right = 0; leftchild = nullptr; rightchild = nullptr; }
	SegmentTreeNode1(int l, int r){ left = l; right = r; leftchild = nullptr; rightchild = nullptr; }
};
class SegmentTree1
{
private:
	SegmentTreeNode1* root;
	SegmentTreeNode1* buildIn(int l,int r,vector<int> &data);
	//void add(int l, int r, int num, SegmentTreeNode1* _root);
	int queryMax(int l, int r, SegmentTreeNode1* _root);
	int queryMin(int l, int r, SegmentTreeNode1* _root);
public:
	SegmentTree1();
	~SegmentTree1();
	//void clear();
	void build(vector<int> &data);
	//void add(int l, int r,int num);
	int queryDist(int l,int r);

};

