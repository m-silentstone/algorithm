#include "StdAfx.h"
#include "Heap.h"


Heap::Heap(void)
{
}

Heap::~Heap(void)
{
}
//½»»»ÔªËØ
void Heap::myswap(vector<int>::iterator iter1,vector<int>::iterator iter2){
	int temp = *iter1;
	*iter1 = *iter2;
	*iter2 = temp;
}

void Heap::siftDown(vector<int>::iterator iter){
	if((iter-coredatas.begin())*2+1>=coredatas.size())return;
	vector<int>::iterator leftchild = coredatas.begin()+(iter-coredatas.begin())*2+1;

	vector<int>::iterator iter_min = leftchild;
	if((iter-coredatas.begin())*2+2<coredatas.size()){
		vector<int>::iterator rightchild = coredatas.begin()+(iter-coredatas.begin())*2+2;
		if(*rightchild<*leftchild){
			iter_min = rightchild;
		}
	}
	
	if(*iter>*iter_min){
		myswap(iter,iter_min);
		siftDown(iter_min);
	}
}

void Heap::siftUp(vector<int>::iterator iter){
	//coredatas.begin()+(iter-coredatas.begin()-1)/2;
	vector<int>::iterator iter_father = coredatas.begin()+((iter-coredatas.begin())-1)/2;
	if(*iter>=*iter_father)return;
	int data = *iter;
	while(data < *(coredatas.begin()+(iter-coredatas.begin()-1)/2)){
		if(iter == coredatas.begin())break;
		*iter = *(coredatas.begin()+(iter-coredatas.begin()-1)/2);
		iter = (coredatas.begin()+(iter-coredatas.begin()-1)/2);
	}
	*iter = data;
}
void Heap::add(int data){
	coredatas.push_back(data);
	siftUp(coredatas.end()-1);

}
int Heap::removeRoot(){
	int res = coredatas[0];
	if(coredatas.size()>1){
		myswap(coredatas.begin(),coredatas.end()-1);
		coredatas.erase(coredatas.end()-1);
		siftDown(coredatas.begin());
	}
	else{
		coredatas.erase(coredatas.end()-1);
	}
	return res;
}