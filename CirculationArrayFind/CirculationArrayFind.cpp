// CirculationArrayFind.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "time.h"
#include <vector>
#include <iostream>
using namespace std;

int circulationArrayFind(vector<int> inputVector,int target){
	int left=0;
	int right = inputVector.size()-1;

	while(left<right){
		int mid = (left+right)/2;
		if(inputVector[mid] == target)return mid;
		if(inputVector[left] == target)return left;
		if(inputVector[right] == target)return right;

		if(inputVector[left]<inputVector[right]){
			if(target<inputVector[mid]){
				right = mid-1;
			}
			else{
				left = mid+1;
			}
		}
		else{
			if(inputVector[mid]>inputVector[left]){//前半部有序
				if(target>inputVector[left]&&target<inputVector[mid])right=mid-1;
				else left=mid+1;
			}
			else{ //后半部有序
				if(target>inputVector[mid]&&target<inputVector[right])left=mid+1;
				else right=mid-1;
			}
		}
	}

	return -1;
}


int _tmain(int argc, _TCHAR* argv[])
{

	vector<int> thevector;
	for(int i=0;i<10;++i)thevector.push_back(i);
	srand(time(NULL));
	int randNum = rand()%10;
	rotate(thevector.begin(),thevector.begin()+randNum,thevector.end());
	for(vector<int>::iterator iter=thevector.begin();iter!=thevector.end();++iter)cout<<*iter<<" ";
	cout<<endl;

	int pos = circulationArrayFind(thevector,7);
	cout<<"7's pos:"<<pos<<endl;

	pos = circulationArrayFind(thevector,13);
	cout<<"13's pos:"<<pos<<endl;

	while(getchar()!='\n');
	getchar();
	return 0;
}

