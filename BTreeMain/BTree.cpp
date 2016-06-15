#include "stdafx.h"
#include "BTree.h"

BTree::BTree()
{
	root = nullptr;
}

BTree::~BTree()
{
	clear(root);
}
void BTree::clear(BTreeNode *_root){
	if (_root == nullptr)return;
	for (int i = 0; i <= _root->dataSize; ++i)if (_root->ptrArr[i] != nullptr)clear(_root->ptrArr[i]);
	delete _root;
}
bool BTree::search(int data){
	BTreeNode *curr = root;
	while (curr!=nullptr){
		int index = 0;
		while (index < curr->dataSize&&data > curr->dataArr[index])++index;
		if (data == curr->dataArr[index])return true;
		curr = curr->ptrArr[index];
	}
	return false;
}

BTreeNode* BTree::insertToNode(BTreeNode* _root,int data,BTreeNode* child1,BTreeNode* child2){
	if (_root == nullptr){
		_root = new BTreeNode();
		_root->dataArr[0] = data;
		_root->ptrArr[0] = child1;
		_root->ptrArr[1] = child2;
		if (child1 != nullptr)child1->parent = _root;
		if (child2 != nullptr)child2->parent = _root;
		_root->dataSize = 1;
		root = _root;
		return root;
	}
	int index = _root->dataSize - 1;
	while (index >= 0 && _root->dataArr[index] > data){
		_root->dataArr[index + 1] = _root->dataArr[index];
		_root->ptrArr[index + 2] = _root->ptrArr[index + 1];
		--index;
	}
	_root->dataArr[index + 1] = data;
	_root->ptrArr[index + 1] = child1;
	_root->ptrArr[index + 2] = child2;
	if (child1 != nullptr)child1->parent = _root;
	if (child2 != nullptr)child2->parent = _root;
	++_root->dataSize;

	if (_root->dataSize <= M - 1)return _root;
	else{
		//需要分裂
		BTreeNode *btn1=_root, *btn2=new BTreeNode();
		int size1 = ceil(M / 2.0) - 1;
		int size2 = M - size1 - 1;
		for (int i = 0; i < size2; ++i){
			btn2->dataArr[i] = _root->dataArr[size1 + 1 + i];
			btn2->ptrArr[i] = _root->ptrArr[size1 + 1 + i];
			if (btn2->ptrArr[i]!=nullptr)btn2->ptrArr[i]->parent = btn2;
		}
		btn2->ptrArr[size2] = _root->ptrArr[M];
		if (btn2->ptrArr[size2] != nullptr)btn2->ptrArr[size2]->parent = btn2;
		btn2->parent = _root->parent;
		btn2->dataSize = size2;
		int midData = _root->dataArr[size1];
		for (int i = size1; i < M; ++i){
			btn1->dataArr[i] = 0;
			btn1->ptrArr[i + 1] = nullptr;
		}
		btn1->parent = _root->parent;
		btn1->dataSize = size1;
		return insertToNode(_root->parent,midData,btn1,btn2);
	}
}

bool BTree::insert(int data){
	if (search(data))return false;
	BTreeNode *curr = root;
	while (curr != nullptr&&curr->ptrArr[0] != nullptr){
		int index = 0;
		while (index < curr->dataSize&&data > curr->dataArr[index])++index;
		curr = curr->ptrArr[index];
	}
	//curr是要插入的节点
	insertToNode(curr,data,nullptr,nullptr);
	return true;
}

void BTree::removeFromNode(BTreeNode* _root, int data){
	if (_root == nullptr)return;
	//并到左边，右子可删
	int index = 0;
	while (index<_root->dataSize&&_root->dataArr[index] < data)index++;
	if (index >= _root->dataSize)return;
	if (_root->dataArr[index] != data)return;
	
	BTreeNode *delPtr = _root->ptrArr[index + 1];
	delete delPtr;
	for (int i = index; i < _root->dataSize - 1; ++i){
		_root->dataArr[i] = _root->dataArr[i + 1];
		_root->ptrArr[i + 1] = _root->ptrArr[i + 2];
	}
	--_root->dataSize;
	_root->dataArr[_root->dataSize] = 0;
	_root->ptrArr[_root->dataSize + 1] = nullptr;

	//超过半满，可以直接删
	if (_root->dataSize >= ceil(M/2.0) - 1 ||(_root->parent==nullptr && _root->dataSize>=1)){
		
		return;
	}
	else{
		BTreeNode *parent = _root->parent;
		if (parent == nullptr){
			root = _root->ptrArr[0];
			if(root!=nullptr)root->parent = nullptr;
			delete _root;
			return;
		}
		int ptrIndex = 0;
		while (ptrIndex <= parent->dataSize&&parent->ptrArr[ptrIndex] != _root)++ptrIndex;
		assert(ptrIndex>=0&&ptrIndex <= parent->dataSize);
		//从左边借
		if (ptrIndex > 0 && parent->ptrArr[ptrIndex - 1]->dataSize > ceil(M / 2.0) - 1){
			int parentData = parent->dataArr[ptrIndex-1];
			parent->dataArr[ptrIndex - 1] = parent->ptrArr[ptrIndex - 1]->dataArr[parent->ptrArr[ptrIndex - 1]->dataSize-1];
			for (int i = _root->dataSize; i >0; --i){
				_root->dataArr[i] = _root->dataArr[i-1];
				_root->ptrArr[i + 1] = _root->ptrArr[i];
			}
			
			_root->ptrArr[1]=_root->ptrArr[0];
			_root->ptrArr[0] = parent->ptrArr[ptrIndex - 1]->ptrArr[parent->ptrArr[ptrIndex - 1]->dataSize];
			if (_root->ptrArr[0] != nullptr)_root->ptrArr[0]->parent = _root;
			_root->dataArr[0] = parentData;
			++_root->dataSize;
			removeFromNode(parent->ptrArr[ptrIndex - 1], parent->ptrArr[ptrIndex - 1]->dataArr[parent->ptrArr[ptrIndex - 1]->dataSize-1]);
			return;
		}
		
		//从右边借
		if (ptrIndex < parent->dataSize && parent->ptrArr[ptrIndex + 1]->dataSize > ceil(M / 2.0) - 1){
			int parentData = parent->dataArr[ptrIndex];
			parent->dataArr[ptrIndex] = parent->ptrArr[ptrIndex + 1]->dataArr[0];

			_root->dataArr[_root->dataSize] = parentData;
			_root->ptrArr[_root->dataSize + 1] = parent->ptrArr[ptrIndex + 1]->ptrArr[0];
			if (_root->ptrArr[_root->dataSize + 1] != nullptr)_root->ptrArr[_root->dataSize + 1]->parent = _root;
			parent->ptrArr[ptrIndex + 1]->ptrArr[0] = parent->ptrArr[ptrIndex + 1]->ptrArr[1];
			++_root->dataSize;
			removeFromNode(parent->ptrArr[ptrIndex + 1], parent->ptrArr[ptrIndex + 1]->dataArr[0]);
			return;
		}

		//合并节点
		if (ptrIndex > 0){
			BTreeNode *left = parent->ptrArr[ptrIndex - 1];
			BTreeNode *right = parent->ptrArr[ptrIndex];
			left->dataArr[left->dataSize] = parent->dataArr[ptrIndex - 1];
			++left->dataSize;
			for (int i = 0; i < right->dataSize; ++i){
				left->dataArr[left->dataSize + i] = right->dataArr[i];
				left->ptrArr[left->dataSize + i] = right->ptrArr[i];
				if (left->ptrArr[left->dataSize + i] != nullptr)left->ptrArr[left->dataSize + i]->parent = left;
			}
			left->dataSize += right->dataSize;
			left->ptrArr[left->dataSize] = right->ptrArr[right->dataSize];
			if (left->ptrArr[left->dataSize] != nullptr)left->ptrArr[left->dataSize]->parent = left;
			removeFromNode(parent, parent->dataArr[ptrIndex - 1]);
		}
		else{
			BTreeNode *left = parent->ptrArr[ptrIndex];
			BTreeNode *right = parent->ptrArr[ptrIndex+1];
			left->dataArr[left->dataSize] = parent->dataArr[ptrIndex];
			++left->dataSize;
			for (int i = 0; i < right->dataSize; ++i){
				left->dataArr[left->dataSize + i] = right->dataArr[i];
				left->ptrArr[left->dataSize + i] = right->ptrArr[i];
				if (left->ptrArr[left->dataSize + i]!=nullptr)left->ptrArr[left->dataSize + i]->parent = left;
			}
			left->dataSize += right->dataSize;
			left->ptrArr[left->dataSize] = right->ptrArr[right->dataSize];
			if (left->ptrArr[left->dataSize] != nullptr)left->ptrArr[left->dataSize]->parent = left;
			removeFromNode(parent, parent->dataArr[ptrIndex]);
		}
		

	}
	return;
}


bool BTree::remove(int data){
	if (search(data)==false)return false;
	BTreeNode *curr = root;
	int index = 0;
	while (curr != nullptr){
		index = 0;
		while (index < curr->dataSize&&data > curr->dataArr[index])++index;
		if (data == curr->dataArr[index])break;
		else curr = curr->ptrArr[index];
	}
	//curr是要删除的节点，curr->dataArr[index]是要删除的值

	//检测是不是分支
	while (curr->ptrArr[0]!=nullptr){
		//左分支的最大值代替
		curr->dataArr[index] = curr->ptrArr[index]->dataArr[curr->ptrArr[index]->dataSize - 1];
		curr = curr->ptrArr[index];
		data = curr->dataArr[curr->dataSize - 1];
		index = curr->dataSize-1;
	}
	//curr是要删除的叶子节点，curr->dataArr[index]是要删除的值
	if (curr == root){
		if (curr->dataSize == 1){
			delete curr;
			root = nullptr;
		}
		else{
			for (int i = index+1; i < curr->dataSize; ++i){
				curr->dataArr[i - 1] = curr->dataArr[i];
			}
			curr->dataArr[curr->dataSize - 1] = 0;
			--curr->dataSize;
		}
		return true;
	}
	//要删除的是非根叶子节点
	removeFromNode(curr, data);
	return true;
}