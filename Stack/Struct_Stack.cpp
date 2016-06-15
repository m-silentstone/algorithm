// Struct_Stack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Stack.h"
#include <string>
#include <iostream>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Stack<string> stack;
	cout<<"stack初始大小："<<stack.getSize()<<endl;
	stack.push("asdasd");
	stack.push("zx,cz");
	stack.push("qerq");
	cout<<"stack大小："<<stack.getSize()<<endl;
	while(stack.getSize()>0){
		cout << "栈顶:" << (stack.top()->data) << endl;
		stack.pop();
	}
	char res;
	cin>>res;
	return 0;
}

