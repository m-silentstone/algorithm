// HeapMain.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Heap.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Heap minHeap;
	minHeap.add(5);
	int cc = minHeap.removeRoot();
	return 0;
}

