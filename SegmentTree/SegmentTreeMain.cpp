// SegmentTreeMain.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SegmentTree.h"
#include "SegmentTree1.h"

//SegmentTree1的数组版本，为了执行速度快
int a[50005];
int n1[150100];
int n2[150100];
void build(int i,int l,int r){
	if (l == r){
		n1[i] = a[l];
		n2[i] = a[l];
	}
	else{
		int mid = (l + r) / 2;
		build(i*2+1,l,mid);
		build(i * 2 + 2, mid+1,r);
		n1[i] = max(n1[2*i+1],n1[2*i+2]);
		n2[i] = min(n2[2 * i + 1], n2[2 * i + 2]);
	}
}

int find1(int i,int l,int r,int li,int ri){
	if (li <= l && ri >= r)return n1[i];
	int mid = (l + r) / 2;
	int num1=0;
	if (li <= mid){
		num1 = find1(i*2+1,l,mid,li,ri);
	}
	if (ri > mid){
		num1 = max(num1,find1(i * 2 + 2, mid+1, r, li, ri));
	}
	return num1;
}

int find2(int i, int l, int r, int li, int ri){
	if (li <= l && ri >= r)return n2[i];
	int mid = (l + r) / 2;
	int num2 = 1000001;
	if (li <= mid){
		num2 = find2(i * 2 + 1, l, mid, li, ri);
	}
	if (ri > mid){
		num2 = min(num2, find2(i * 2 + 2, mid + 1, r, li, ri));
	}
	return num2;
}


int _tmain(int argc, _TCHAR* argv[])
{
	/*vector<int> dots;
	dots.push_back(10000);
	dots.push_back(22000);
	dots.push_back(30300);
	dots.push_back(44000);
	dots.push_back(55000);
	dots.push_back(60000);
	SegmentTree st;
	st.build(0,5);
	st.insert(0,1);
	st.insert(2, 4);
	st.insert(3, 5);
	st.insert(4, 5);
	st.remove(3,4);
	cout << st.query(dots) << endl;*/



	/*vector<int> heights;
	heights.push_back(1);
	heights.push_back(7);
	heights.push_back(3);
	heights.push_back(4);
	heights.push_back(2);
	heights.push_back(5);
	SegmentTree1 st1;
	st1.build(heights);
	cout << st1.queryDist(0,4)<<endl;
	cout << st1.queryDist(3, 5) << endl;
	cout << st1.queryDist(1, 1) << endl;*/



	int m, n;
	cin >> m >> n;
	for (int i = 0; i<m; ++i){
		cin >> a[i];
	}
	build(0, 0, m - 1);
	int li, ri;
	for (int i = 0; i<n; ++i){
		cin >> li >> ri;
		int num1 = find1(0, 0, m - 1, li - 1, ri - 1);
		int num2 = find2(0, 0, m - 1, li - 1, ri - 1);
		cout << num1 - num2 << endl;
	}

	while (getchar() == '\n');
	getchar();
	return 0;
}

