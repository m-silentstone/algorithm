// TreeVector.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <time.h>
#include <vector>
#include <iostream>
using namespace std;

class TreeVector{
private:
	vector<int> ivect;
	vector<int> isvect;
	int lowbit(int k){
		return (k+1)&(-(k+1));
	}

public:
	void init(vector<int> &originVect){
		isvect.assign(originVect.size(),0);
		for (int i = 0; i < originVect.size(); ++i){
			ivect.push_back(originVect[i]);
			int index = i;
			while (index < originVect.size()){
				isvect[index] += originVect[i];
				index = index + lowbit(index);
			}
		}
	}

	int sum(int i){  //0->i
		int res = 0;
		while (i >= 0){
			res += isvect[i];
			i = i - lowbit(i);
		}
		return res;
	}

	void modify(int i, int v){ //ivect[i]=v
		int oldV = ivect[i];
		ivect[i] = v;
		int offset = v - oldV;
		while (i < isvect.size()){
			isvect[i] += offset;
			i = i + lowbit(i);
		}
	}
	void outputIS(){
		cout << "S:";
		for each (auto var in isvect)
		{
			cout << var << " ";
		}
		cout << endl;
	}
	void outputI(){
		cout << "I:";
		for each (auto var in ivect)
		{
			cout << var << " ";
		}
		cout << endl;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> ivectOrigin;
	srand(time(nullptr));
	for (int i = 1; i <= 10; ++i){
		ivectOrigin.push_back(rand()%10);
	}
	TreeVector tv;
	tv.init(ivectOrigin);
	tv.outputI();
	tv.outputIS();

	cout<<tv.sum(4)<<endl;
	cout << tv.sum(7)<<endl;
	cout << tv.sum(3)<<endl;

	tv.modify(2,5);
	tv.modify(6,4);
	tv.outputI();
	tv.outputIS();
	cout << tv.sum(4) << endl;
	cout << tv.sum(7) << endl;
	cout << tv.sum(3) << endl;
	while (getchar() == '\n');
	getchar();
	return 0;
}

