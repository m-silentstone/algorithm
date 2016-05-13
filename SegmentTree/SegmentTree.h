#pragma once
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

//�߶���������⣺�����ϴ��ڶ����߶Σ����˴��غ���ɵ��߶Σ�����֮���Ƕ���
//info��ʾĳ����Χ�Ƿ����߶��У�0���ڣ�1��
//query�õ��߶γ���֮��

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

