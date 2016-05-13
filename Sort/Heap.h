#pragma once
#include <vector>
using namespace std;

//×îÐ¡¶Ñ
class Heap
{
private:
	vector<int> coredatas;
	void siftDown(int i);
	void siftUp(int i);
	//void myswap(vector<int>::iterator iter1,vector<int>::iterator iter2);
public:
	Heap(void);
	~Heap(void);
	void add(int data);
	int removeRoot();
	bool isEmpty(){return coredatas.empty();}
};

