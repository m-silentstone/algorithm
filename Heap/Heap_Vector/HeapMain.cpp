// HeapMain.cpp : �������̨Ӧ�ó������ڵ㡣
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

