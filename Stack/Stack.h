#pragma once

template<class T>
class LinkNode{
public:
	T data;
	class LinkNode *next;
	LinkNode(){ next = nullptr; };
	~LinkNode(){};
};

template<class T>
class Stack
{
private:
	LinkNode<T> *_top;
	int size;
public:
	Stack(); 
	~Stack();
	bool pop();
	bool push(T data);
	int getSize();
	LinkNode<T>* top();
};

template<class T>
Stack<T>::Stack(){ _top = nullptr; size = 0; }

template<class T>
Stack<T>::~Stack(){
	while (_top != nullptr)pop();
}

template<class T>
bool Stack<T>::pop(){
	if (size == 0 || _top == nullptr)return false;
	LinkNode<T> *ptrDel = _top;
	_top = _top->next;
	size--;
	delete ptrDel;
	return true;
}

template<class T>
bool Stack<T>::push(T data){
	LinkNode<T> *topPtr = new LinkNode<T>();
	topPtr->data = data;
	topPtr->next = _top;
	_top = topPtr;
	size++;
	return true;
}

template<class T>
int Stack<T>::getSize(){
	return size;
}

template<class T>
LinkNode<T>* Stack<T>::top(){
	return _top;
}
