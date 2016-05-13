// LongestCommonSequence.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <deque>
#include <iterator>
#include <algorithm>
#include <assert.h>
#include <iostream>
using namespace std;

//动态规划求公共子序列，结果存到resIter处  LCS:LongestCommonSequence
template<class Iter1,class Iter2,class Iter3> int dynamicFindLCS(Iter1 left1,Iter1 right1,Iter2 left2,Iter2 right2,Iter3 resIter){
	int length1 = right1-left1;
	int length2 = right2-left2;

	int **direction = new int*[length1+1];//0不用,0:从左上来;1:从上来；2：从左来
	for(int i=0;i<length1+1;++i)direction[i]=new int[length2+1];
	int **pLCSlength = new int*[length1+1];
	for(int i=0;i<length1+1;++i)pLCSlength[i]=new int[length2+1];

	for(int i=0;i<length1+1;++i)pLCSlength[i][0]=0;
	for(int i=1;i<length2+1;++i)pLCSlength[0][i]=0;

	for(Iter1 iter1=left1;iter1!=right1;++iter1){
		for(Iter2 iter2=left2;iter2!=right2;++iter2){
			int pos1=iter1-left1+1;
			int pos2=iter2-left2+1;
			if(*iter1==*iter2){
				pLCSlength[pos1][pos2] = pLCSlength[pos1-1][pos2-1]+1;
				direction[pos1][pos2] = 0;
			}
			else{
				if(pLCSlength[pos1][pos2-1]>pLCSlength[pos1-1][pos2]){pLCSlength[pos1][pos2] = pLCSlength[pos1][pos2-1];direction[pos1][pos2] = 2;}
				else{pLCSlength[pos1][pos2] = pLCSlength[pos1-1][pos2];direction[pos1][pos2] = 1;}
			}
		}
	}

	int length=pLCSlength[right1-left1][right2-left2];

	int pos1=right1-left1;
	int pos2=right2-left2;

	deque<int> tempPos;
	while(pos1>0&&pos2>0){
		assert(direction[pos1][pos2]==0||direction[pos1][pos2]==1||direction[pos1][pos2]==2);
		if(direction[pos1][pos2]==0){
			tempPos.push_front(pos1-1);
			--pos1;
			--pos2;
		}
		else if(direction[pos1][pos2]==1){
			--pos1;
		}
		else{--pos2;}
	}

	for(deque<int>::iterator iter=tempPos.begin();iter!=tempPos.end();++iter){
		*resIter = *(left1+*iter);
		++resIter;
	}

	for(int i=0;i<length1+1;++i)delete []direction[i];
	delete direction;
	for(int i=0;i<length1+1;++i)delete []pLCSlength[i];
	delete pLCSlength;

	
	return length;
}

//递归查找公共子序列_长度
template<class Iter1,class Iter2> int recurseFindLCS_length(Iter1 left1,Iter1 right1,Iter2 left2,Iter2 right2,deque<int> &distR){
	//边界
	if(right1-left1==1){
		if(count(left2,right2,*left1)>0){distR.push_front(1);return 1;}
		else return 0;
	}
	if(right1==left1)return 0;
	if(right2-left2==1){
		Iter1 iter1 = find(left1,right1,*left2);
		if(iter1!=right1){distR.push_front(right1-iter1);return 1;}
		else return 0;
	}
	if(right2==left2)return 0;

	deque<int> tempDistR1 = distR;
	deque<int> tempDistR2 = distR;

	int length1=0;
	//要left1
	Iter2 iter2 = find(left2,right2,*left1);

	if(iter2!=right2)length1=1+recurseFindLCS_length(left1+1,right1,iter2+1,right2,tempDistR1);

	//不要left1
	int length2 = recurseFindLCS_length(left1+1,right1,left2,right2,tempDistR2);

	if(length1>length2){distR=tempDistR1;distR.push_front(right1-left1);return length1;}
	else {distR=tempDistR2;return length2;}

}

//递归查找公共子序列
template<class Iter1,class Iter2,class Iter3> int recurseFindLCS(Iter1 left1,Iter1 right1,Iter2 left2,Iter2 right2,Iter3 resIter){
	deque<int> distR;
	int res = recurseFindLCS_length(left1,right1,left2,right2,distR);
	for(deque<int>::iterator iter=distR.begin();iter!=distR.end();++iter){
		*resIter = *(right1-*iter);
		++resIter;
	}
	return res;
}


int _tmain(int argc, _TCHAR* argv[])
{
	string str1("gflrowro");
	string str2("fgorwo");
	string str3;

	//int resLength = recurseFindLCS(str1.begin(),str1.end(),str2.begin(),str2.end(),back_inserter(str3));
	
	int resLength = dynamicFindLCS(str1.begin(),str1.end(),str2.begin(),str2.end(),back_inserter(str3));
	cout<<resLength<<endl;
	cout<<str3;

	while(getchar()!='\n');
	getchar();

	return 0;
}

