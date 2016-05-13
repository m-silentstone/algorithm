// knapsack01.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void knapsack01(){
	int m, capacity;
	cin >> m >> capacity;
	vector<int> weight(m),value(m);
	for (int i = 0; i < m; ++i){
		cin>>weight[i]>>value[i];
	}
	vector<vector<int>> dp(m,vector<int>(capacity+1));
	for (int j = capacity; j >= 0; --j)dp[0][j] = (j >= weight[0])?value[0]:0;
	for (int i = 1; i < m; ++i){
		for (int j = capacity; j >= 0; --j){
			if (j < weight[i])dp[i][j] = dp[i - 1][j];
			else dp[i][j] = max(dp[i-1][j],dp[i-1][j-weight[i]]+value[i]);
		}
	}
	cout << dp[m-1][capacity];
}



int _tmain(int argc, _TCHAR* argv[])
{
	knapsack01();
	while (getchar() == '\n');
	getchar();
	return 0;
}

