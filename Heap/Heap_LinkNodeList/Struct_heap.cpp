// Struct_heap.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "math.h"
#include <iostream>
using namespace std;
//最小堆


class LinkNode{
public:
	LinkNode(){data=0;leftChild=NULL;rightChild=NULL;next=NULL;father=NULL;}
	int data;
	LinkNode *leftChild;
	LinkNode *rightChild;
	LinkNode *next;
	LinkNode *father;
};

class Heap{
private:
	LinkNode *m_root;
	int m_size;
	void dragDown(LinkNode *);
	void swapNode(LinkNode *param1,LinkNode *param2);
public:
	Heap(){m_root = NULL;m_size = 0;}
	~Heap(){while(m_root != NULL)removeRoot();}
	int getSize(){return m_size;}
	void add(int data);
	int removeRoot();
	void sortPrint();
};

void Heap::swapNode(LinkNode *param1,LinkNode *param2){
	int temp = param1->data;
	param1->data = param2->data;
	param2->data = temp;
}
void Heap::dragDown(LinkNode *element){
	if(element->leftChild == NULL)return;
	else if(element->leftChild !=NULL && element->rightChild == NULL){
		LinkNode *leftChild = element->leftChild;
		if(element->data > leftChild->data)swapNode(element,leftChild);
		return;
	}
	LinkNode *leftChild = element->leftChild;
	LinkNode *rightChild = element->rightChild;
	if((element->data > leftChild->data) || (element->data > rightChild->data)){
		LinkNode *minChild = NULL;
		if(leftChild->data < rightChild->data)minChild = leftChild;
		else minChild = rightChild;

		swapNode(minChild,element);
		dragDown(minChild);
	}
}

void Heap::add(int data){
	LinkNode *newElement = new LinkNode();
	newElement->father = NULL;
	newElement->leftChild = NULL;
	newElement->rightChild= NULL;
	newElement->next = NULL;
	newElement->data = data;

	if(m_root == NULL){
		m_root = newElement;
		m_size++;
		return;
	}
	int insertLayer = floor(log((double)(m_size+1))/log((double)2));
	int elementBefore = (int)(m_size - pow(2.0,insertLayer)+1);
	LinkNode *insertPosition = m_root;
	for(int i=1;i<insertLayer;i++){
		insertPosition = insertPosition->leftChild;
	}
	LinkNode *insertPositionPre = NULL;
	if(elementBefore !=0){
		for(int i=1;i<elementBefore/2+1;i++){
			insertPositionPre = insertPosition;
			insertPosition = insertPosition->next;
		}
	}
	newElement->father = insertPosition;
	if(elementBefore%2 == 0){
		insertPosition->leftChild = newElement;
		if(elementBefore !=0){
			((LinkNode *)insertPositionPre->rightChild)->next = newElement;
		}
	}
	else{
		insertPosition->rightChild = newElement;
		if(elementBefore !=0){
			((LinkNode *)insertPosition->leftChild)->next = newElement;
		}
	}
	m_size++;
	LinkNode *compareElement=newElement;
	int newData = newElement->data;
	//dragUp
	while(compareElement->father != NULL){
		if(newData >= ((LinkNode *)compareElement->father)->data)break;
		compareElement->data = ((LinkNode *)compareElement->father)->data;
		compareElement = compareElement->father;
	}
	compareElement->data = newData;
}

int Heap::removeRoot(){
	int result = m_root->data;
	if(m_root->leftChild == NULL){
		delete m_root;
		m_root = NULL;
		return result;
	}
	LinkNode *lastElement = m_root;
	while(lastElement->leftChild != NULL){
		lastElement = lastElement->leftChild;
	}
	LinkNode *lastElementPre = NULL;
	while(lastElement->next != NULL){
		lastElementPre = lastElement;
		lastElement = lastElement->next;
	}
	m_root->data = lastElement->data;
	if(lastElementPre!=NULL)lastElementPre->next = NULL;
	if(((LinkNode *)lastElement->father)->leftChild == lastElement)((LinkNode *)lastElement->father)->leftChild = NULL;
	else ((LinkNode *)lastElement->father)->rightChild = NULL;
	delete lastElement;
	//作调整
	dragDown(m_root);
	return result;
}

void Heap::sortPrint(){
	while(m_root != NULL){
		int num = removeRoot();
		cout<<num<<endl;
	}


}

int _tmain(int argc, _TCHAR* argv[])
{
	Heap minHeap;
	minHeap.add(10);
	minHeap.add(2);
	minHeap.add(5);
	minHeap.add(7);
	minHeap.add(11);
	minHeap.add(1);
	minHeap.add(4);
	minHeap.add(3);
	minHeap.sortPrint();

	char hold;
	cin>>hold;
	return 0;
}

