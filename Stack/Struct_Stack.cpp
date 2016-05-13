// Struct_Stack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

typedef struct LINKNODE{
	string data;
	struct LINKNODE *next;
}linknode;

class Stack{
private:
	linknode *top;
	int size;
public:
	Stack(){top = NULL;size=0;}
	~Stack(){
		while(top!= NULL){
			LINKNODE *ptr_temp = pop();
			delete ptr_temp;
		}
	}

	linknode* pop();
	bool push(string data);
	int getSize();
	linknode* getTop();
};
linknode* Stack::pop(){
	if(size == 0)return NULL;
	linknode *ptr_temp = top;
	top = top->next;
	size--;
	return ptr_temp;
}
bool Stack::push(string data){
	linknode *topLinknode = new linknode();
	topLinknode->data = data;
	topLinknode->next = top;
	top = topLinknode;
	size++;
	return true;
}
int Stack::getSize(){
	return size;
}
linknode* Stack::getTop(){
	return top;
}




int _tmain(int argc, _TCHAR* argv[])
{
	Stack stack;
	cout<<"stack初始大小："<<stack.getSize()<<endl;
	stack.push("asdasd");
	stack.push("zx,cz");
	stack.push("qerq");
	cout<<"stack大小："<<stack.getSize()<<endl;
	while(stack.getSize()>0){
		linknode *ptr = stack.pop();cout<<"pop:"<<(ptr->data)<<endl;
	}
	char res;
	cin>>res;
	return 0;
}

