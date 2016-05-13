// Union-Find_Sets.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <map>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

template<class T>
class UnionFindSet {
	class UnionFindSet_node {
	public :
		T m_parent;
		int m_iRank;//rank只有在节点是集合的头结点才有意义
		UnionFindSet_node() {}
		UnionFindSet_node(T parent,int iRank=1) { m_parent = parent; m_iRank = iRank; }		
	};
public:
	map<T, UnionFindSet_node> m_mapData;

	UnionFindSet() {}
	T find(T element) {
		T parent = m_mapData[element].m_parent;
		if (parent == element)return parent;
		else {
			//路径压缩
			m_mapData[element].m_parent = find(parent);
			return m_mapData[element].m_parent;
		}
	}
	void unionSet(T element1, T element2) {
		if (isSameSet(element1, element2))return;
		//按秩合并
		if (m_mapData[find(element1)].m_iRank < m_mapData[find(element2)].m_iRank) {
			m_mapData[find(element1)].m_parent = find(element2);
		}
		else {
			m_mapData[find(element2)].m_parent = find(element1);
			if (m_mapData[find(element1)].m_iRank == m_mapData[find(element2)].m_iRank) {
				++m_mapData[find(element1)].m_iRank;
			}
		}
	}

	void init(vector<T>& vectElements) {
		for (int i = 0; i < vectElements.size(); ++i) {
			if (m_mapData.count(vectElements[i]) == 0) {
				m_mapData[vectElements[i]] = UnionFindSet_node(vectElements[i]);
			}
		}
	}

	bool isSameSet(T element1, T element2) {
		return (find(element1) == find(element2));
	}

	void outputSet(T element) {
		T root = find(element);
		for each (auto pair in m_mapData)
		{
			if(find(pair.first)==root)cout<<pair.first<<":";
		}
		cout << endl;
	}
};

int main()
{
	UnionFindSet<int> ufsTest;
	vector<int> vectInput;
	for (int i = 0; i < 20; ++i) {
		vectInput.push_back(i);
	}
	ufsTest.init(vectInput);
	ufsTest.unionSet(1,2);
	ufsTest.unionSet(3, 4);
	ufsTest.unionSet(11, 12);
	ufsTest.unionSet(13, 12);
	ufsTest.unionSet(13, 14);

	for each(auto var in ufsTest.m_mapData) {
		if (var.first == var.second.m_parent) {
			ufsTest.outputSet(var.first);
		}
	}

	while (getchar() == '\n');
	getchar();
    return 0;
}

