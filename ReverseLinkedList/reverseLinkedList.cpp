// reverseLinkedList.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <list>
#include <iostream>
using namespace std;

template<class T> void reverseLinkedList(list<T>& originList){
	list<T> resList;
	for(list<T>::iterator iter=originList.begin();iter!=originList.end();++iter){
		T tempT = *iter;
		resList.push_front(tempT);
	}
	originList.assign(resList.begin(),resList.end());
	return;
}


int _tmain(int argc, _TCHAR* argv[])
{
	list<int> thelist;
	thelist.push_back(1);
	thelist.push_back(3);
	thelist.push_back(5);
	thelist.push_back(7);
	thelist.push_back(9);
	for(list<int>::iterator iter=thelist.begin();iter!=thelist.end();++iter)cout<<*iter<<" ";
	cout<<endl;
	reverseLinkedList(thelist);
	for(list<int>::iterator iter=thelist.begin();iter!=thelist.end();++iter)cout<<*iter<<" ";

	while(getchar()=='\n');
	getchar();
	return 0;
}

