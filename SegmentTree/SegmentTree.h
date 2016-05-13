#pragma once
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

//线段树求解问题：数轴上存在多条线段，最后彼此重合组成的线段，长度之和是多少
//info表示某个范围是否在线段中，0不在，1在
//query得到线段长度之和

class SegmentTreeNode{
public:
	int left;
	int right;
	int info;
	SegmentTreeNode *leftchild;
	SegmentTreeNode *rightchild;
	SegmentTreeNode(){ left = 0; right = 0; info = 0; leftchild = nullptr; rightchild = nullptr; }
	SegmentTreeNode(int l, int r){ left = l; right = r; info = 0; leftchild = nullptr; rightchild = nullptr; }
};
class SegmentTree
{
private:
	SegmentTreeNode* root;
	SegmentTreeNode* buildIn(int l, int r);
	void insert(int l, int r, SegmentTreeNode* _root);
	void remove(int l, int r, SegmentTreeNode* _root);
	int query(vector<int> &coord,SegmentTreeNode* _root);
public:
	SegmentTree();
	~SegmentTree();
	void clear();
	void build(int l,int r);
	void insert(int l,int r);
	void remove(int l,int r);
	int query(vector<int> &coord);

};

