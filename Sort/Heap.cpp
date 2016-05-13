#include "StdAfx.h"
#include "Heap.h"


Heap::Heap(void)
{
}

Heap::~Heap(void)
{
}
//½»»»ÔªËØ
//void Heap::myswap(vector<int>::iterator iter1,vector<int>::iterator iter2){
//	int temp = *iter1;
//	*iter1 = *iter2;
//	*iter2 = temp;
//}

void Heap::siftDown(int i){
	if(i*2+1>=coredatas.size())return;
	int iLeft = i*2+1;

	int iMin = iLeft;
	if(i*2+2<coredatas.size()){
		int iRight =i*2+2;
		if (coredatas[iLeft]>coredatas[iRight]){
			iMin = iRight;
		}
	}
	if(coredatas[i]>coredatas[iMin]){
		swap(coredatas[i], coredatas[iMin]);
		siftDown(iMin);
	}
}

void Heap::siftUp(int i){
	if (i == 0)return;
	int iFather = (i-1) / 2;
	int num = coredatas[i];
	while(num < coredatas[iFather]){
		coredatas[i] = coredatas[iFather];
		i = iFather;
		if(i == 0)break;
		iFather = (i-1)/2;	
	}
	coredatas[i] = num;
}

void Heap::add(int num){
	coredatas.push_back(num);
	siftUp(coredatas.size()-1);
}

int Heap::removeRoot(){
	if (coredatas.size() == 0)return -1;
	int res = coredatas[0];
	if(coredatas.size()>1){
		swap(coredatas[0],coredatas[coredatas.size()-1]);
		coredatas.erase(coredatas.end() - 1);
		siftDown(0);
	}
	else{
		coredatas.erase(coredatas.end()-1);
	}
	return res;
}