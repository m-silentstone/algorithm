// Struct_Stack.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Stack.h"
#include <string>
#include <iostream>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Stack<string> stack;
	cout<<"stack��ʼ��С��"<<stack.getSize()<<endl;
	stack.push("asdasd");
	stack.push("zx,cz");
	stack.push("qerq");
	cout<<"stack��С��"<<stack.getSize()<<endl;
	while(stack.getSize()>0){
		cout << "ջ��:" << (stack.top()->data) << endl;
		stack.pop();
	}
	char res;
	cin>>res;
	return 0;
}

