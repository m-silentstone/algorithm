#pragma once
#include <vector>
using namespace std;

//×îÐ¡¶Ñ
class Heap
{
private:
	vector<int> coredatas;
	void siftDown(vector<int>::iterator iter);
	void siftUp(vector<int>::iterator iter);
	void myswap(vector<int>::iterator iter1,vector<int>::iterator iter2);
public:
	Heap(void);
	~Heap(void);
	void add(int data);
	int removeRoot();
	bool isEmpty(){return coredatas.empty();}
};
