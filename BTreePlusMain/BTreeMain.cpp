// BTreeMain.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "BTree.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	BTree bt;
	bt.insert(3);
	bt.insert(13);
	bt.insert(22);
	bt.insert(14);
	bt.insert(16);
	bt.insert(6);
	bt.insert(8);
	bt.insert(7);
	bt.insert(11);
	bt.insert(42);
	bt.insert(35);
	bt.insert(62);
	bt.insert(44);
	bt.insert(11);

	cout<<"1:"<<bt.search(1)<<endl;
	cout << "23:" << bt.search(23) << endl;
	cout << "14:" << bt.search(14) << endl;
	cout << "52:" << bt.search(52) << endl;
	cout << "7:" << bt.search(7) << endl;
	cout << "15:" << bt.search(15) << endl;
	cout << "31:" << bt.search(31) << endl;
	cout << "3:" << bt.search(3) << endl;
	cout << "62:" << bt.search(62) << endl;
	
	bt.remove(1);
	bt.remove(99);

	bt.remove(3);
	bt.remove(13);
	bt.remove(22);
	bt.remove(14);
	bt.remove(16);
	bt.remove(6);
	bt.remove(8);
	bt.remove(7);
	bt.remove(11);
	bt.remove(42);
	bt.remove(35);
	bt.remove(62);
	bt.remove(44);
	bt.remove(11);


	while (getchar() == '\n');
	getchar();
	return 0;
}

