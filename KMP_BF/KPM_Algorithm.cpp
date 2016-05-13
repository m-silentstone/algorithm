// KPM_Algorithm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

template<class Iter1,class Iter2>Iter1 kmpSearch(Iter1 left1,Iter1 right1,Iter2 left2,Iter2 right2){
	if(left2>=right2||left1>=right1)return right1;
	if(right1-left1<right2-left2)return right1;
	//生成动态规划数组，记录适配后重新检测位置
	vector<int> checkPosVector(right2-left2,-1);
	//checkPosVector[0]=-1;
	Iter2 iter2=left2+1;
	if(iter2!=right2){
		checkPosVector[1]=0;
		++iter2;
	}
	while(iter2!=right2){
		/*int j=iter2-left2;
		int maxK=0;
		for(int k=1;k<j;++k){
			Iter2 iter2_cp1=left2;
			Iter2 iter2_cp2=left2+j-k;
			while(iter2_cp2!=left2+j &&*iter2_cp1 == *iter2_cp2){++iter2_cp1;++iter2_cp2;}
			if(iter2_cp2==left2+j)maxK=k;
		}
		checkPosVector[iter2-left2]=maxK;*/

		if(*(iter2-1)==*(left2+checkPosVector[iter2-left2-1]))checkPosVector[iter2-left2]=checkPosVector[iter2-left2-1]+1;
		else{
			int nindex = checkPosVector[iter2-left2-1];
			checkPosVector[iter2-left2]=0;
			while(nindex>0){
				nindex = checkPosVector[nindex];
				if(*(left2+nindex)==*(iter2-1)){checkPosVector[iter2-left2]=nindex+1;break;}
			}
		}

		++iter2;
	}

	//1趟检测字串1，查找匹配位置
	Iter1 iter1=left1;
	iter2=left2;
	while(iter1<right1-(right2-left2)+1){
		while(iter2!=right2&&*iter1==*iter2){
			++iter1;
			++iter2;
		}
		if(iter2==right2)return iter1-(right2-left2);
		int checkPos = checkPosVector[iter2-left2];
		if(checkPos==-1){iter2=left2;++iter1;}
		else{iter2=left2+checkPos;}
	}
	return right1;
}

template<class Iter1,class Iter2>Iter1 bfSearch(Iter1 left1,Iter1 right1,Iter2 left2,Iter2 right2){
	if(left2>=right2||left1>=right1)return right1;
	if(right1-left1<right2-left2)return right1;

	Iter1 iter = left1;
	while(iter<right1-(right2-left2)+1){
		Iter1 iterThisTurn = iter;
		Iter2 iterThisTurn2 = left2;
		while((iterThisTurn2!=right2)&&(iterThisTurn!=right1)&&(*iterThisTurn == *iterThisTurn2)){++iterThisTurn;++iterThisTurn2;}
		if(iterThisTurn2 == right2)return iterThisTurn-(right2-left2);
		++iter;
	}
	return right1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string str1("assdfsgfhfh334sdfs");
	string str2("fhfh34");
	string::iterator iter;

	iter = kmpSearch(str1.begin(),str1.end(),str2.begin(),str2.end());
	cout<<"KMP算法：";
	if(iter == str1.end())cout<<"未找到匹配字符串"<<endl;
	else cout<<"匹配位置："<<iter-str1.begin()<<endl;

	iter = bfSearch(str1.begin(),str1.end(),str2.begin(),str2.end());
	cout<<"BF算法：";
	if(iter == str1.end())cout<<"未找到匹配字符串"<<endl;
	else cout<<"匹配位置："<<iter-str1.begin()<<endl;

	while(getchar()!='\n');
	getchar();
	return 0;
}

