// Searches.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "assert.h"
#include "time.h"
#include "HashTree.h"
#include "BinarySortTree.h"
#include <vector>
#include <iostream>
using namespace std;
const int SAMPLENUM = 50;
//交换元素
void myswap(vector<int>::iterator iter1,vector<int>::iterator iter2){
	int temp = *iter1;
	*iter1 = *iter2;
	*iter2 = temp;
}
//快速排序_分区
vector<int>::iterator partition(vector<int>::iterator left,vector<int>::iterator right){
	assert(right-left>0);
	int data1 = *left;
	int data2 = *(left+(right-left)/2);
	int data3 = *right;
	if(data1<data2){
		if(data2<data3)myswap(left,left+(right-left)/2);
		else if(data1<data3)myswap(left,right);
	}
	else{
		if(data2>data3)myswap(left,left+(right-left)/2);
		else if(data1>data3)myswap(left,right);
	}

	vector<int>::iterator i=left+1;
	vector<int>::iterator j=right;

	do{
		while(*i<=*left){
			i++;
			if(!(i>=left&&i<=right))break;
		}
		while(*j>*left){
			j--;
			if(!(j>=left&&i<=right))break;
		}
		if(i<j)myswap(i,j);
	}while(i<j);
	myswap(j,left);
	return j;
}

//快速排序_递归子过程
void quicksort(vector<int>::iterator left,vector<int>::iterator right){
	if(right-left<=1)return;
	vector<int>::iterator sppos = partition(left,right-1);
	quicksort(left,sppos);
	quicksort(sppos+1,right);
}
//快速排序
vector<int> sort_quick(vector<int> data){

	quicksort(data.begin(),data.end());
	return data;
}
//==================================================================================================

//二分法查找
int search_middle(vector<int> data,int target){
	int res_index = -1;
	int left = 0;int right = data.size()-1;
	while(left<=right){
		int middle = (left+right)/2;
		if(target == data[middle]){res_index = middle;break;}
		if(target < data[middle]){
			right = middle-1;
		}
		else{
			left = middle+1;
		}
	}
	return res_index;
}
//hash树查找
HashTreeNode* search_hashTree(vector<int> vect_data,int target){
	HashTree hashTree;
	for(vector<int>::iterator iter=vect_data.begin();iter!=vect_data.end();iter++){
		hashTree.add(*iter);
	}
	HashTreeNode *targetPtr = hashTree.find(target);
	return targetPtr;
}
//二叉排序树查找
BinarySortTreeNode* search_binarySortTree(vector<int> vect_data,int target){
	BinarySortTree binarySortTree;
	for(vector<int>::iterator iter=vect_data.begin();iter!=vect_data.end();iter++){
		binarySortTree.add(*iter);
	}

	BinarySortTreeNode* targetPtr = binarySortTree.find(target);
	return targetPtr;
}
//==========================================
//==========================================
void outputVector(vector<int> data){
	int shownum = SAMPLENUM;
	for(vector<int>::iterator iter = data.begin();iter != data.begin()+shownum;iter++){
		cout<<*iter<<"  ";
	}
	cout<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> data;
	clock_t cstart,cfinish;
	srand(time(NULL));
	for(int i=0;i<SAMPLENUM;i++){
		int num = rand()%100;
		data.push_back(num);
	}
	/*data[SAMPLENUM-1] = 55;*/

	////折半查找
	//cstart = clock();
	//data = sort_quick(data);
	//outputVector(data);
	//int target = 55;
	//int res = search_middle(data,target);
	//cfinish = clock();
	//if(res == -1)cout<<"没找到"<<target<<endl;
	//else{
	//	cout<<"找到了，"<<target<<"在数组的第"<<res<<"处（0为起始）"<<endl;
	//}
	//cout<<"折半查找用时"<<(cfinish-cstart)/(CLOCKS_PER_SEC/1000)<<"ms"<<endl;

	////哈希树查找
	//cstart = clock();
	//outputVector(data);
	//int target = 55;
	//HashTreeNode *targetPtr = search_hashTree(data,target);
	//cfinish = clock();
	//if(targetPtr == NULL)cout<<"没找到"<<target<<endl;
	//else{
	//	cout<<"找到了"<<target<<endl;
	//}
	//cout<<"哈希树查找用时"<<(cfinish-cstart)/(CLOCKS_PER_SEC/1000)<<"ms"<<endl;

	//二叉排序树查找
	cstart = clock();
	outputVector(data);
	int target = 55;
	BinarySortTreeNode* targetPtr = search_binarySortTree(data,target);
	cfinish = clock();
	if(targetPtr == NULL)cout<<"没找到"<<target<<endl;
	else{
		cout<<"找到了"<<target<<endl;
	}
	cout<<"二叉排序树查找用时"<<(cfinish-cstart)/(CLOCKS_PER_SEC/1000)<<"ms"<<endl;

	char reschar;
	cin>>reschar;
	return 0;
}

