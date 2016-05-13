// GraphMain.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Graph.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <functional>
#include "assert.h"

class EdgeNode{
	public:
		int v1Index;
		int v2Index;
		int weight;
		EdgeNode() :v1Index(-1), v2Index(-1), weight(0){}
		EdgeNode(int _v1Index, int _v2Index, int _weight) :v1Index(_v1Index), v2Index(_v2Index), weight(_weight){}
		bool operator ==(const EdgeNode &enode)const{ return (weight == enode.weight) && ((v1Index == enode.v1Index&&v2Index == enode.v2Index) || (v1Index == enode.v2Index&&v2Index == enode.v1Index)); }
		bool operator <(const EdgeNode &enode)const{return weight<enode.weight;}
		bool operator >(const EdgeNode &enode)const{return weight>enode.weight;}
};
//��������
//class SameVertex{
//	char vname;
//public:
//	SameVertex(){vname='?';}
//	SameVertex(char vparam){vname=vparam;}
//	bool operator ()(Vertex &vertex){
//		if(vertex.name == vname)return true;
//		else return false;
//	}
//	
//};

Graph kruskal(Graph &graph){
	vector<EdgeNode> EVector;
	//������
	for (int i = 0; i < graph.getVlist().size();++i){
		Edge *pCurrentE = graph.getVlist()[i]->head;
		while(pCurrentE!=NULL){
			if (i < pCurrentE->destVIndex)EVector.push_back(EdgeNode(i, pCurrentE->destVIndex, pCurrentE->cost));
			pCurrentE=pCurrentE->nextE;
		}
	}
	sort(EVector.begin(),EVector.end());
	//���鼯�������ж�2���Ƿ���ͬһ��֧
	int *UFSet = new int[graph.getVlist().size()];
	for (int i = 0; i < graph.getVlist().size(); ++i){
		UFSet[i] = i;
	}
	//���μ��룬ֱ��ȫ��ͨ
	Graph resGraph;
	//�������е㣬û�бߴ���
	int edgeNum = 0;
	for (int i = 0; i < graph.getVlist().size(); ++i)
		resGraph.getVlist().push_back(new Vertex(graph.getVlist()[i]->name));
	int eIndex = 0;
	while (edgeNum+1<graph.getVertexNum() && eIndex<EVector.size()){
		int s1 = EVector[eIndex].v1Index, s2 = EVector[eIndex].v2Index;
		while (s1 != UFSet[s1])s1 = UFSet[s1];
		while (s2 != UFSet[s2])s2 = UFSet[s2];
		if (s1!=s2){
			++edgeNum;
			resGraph.insertEdge(EVector[eIndex].v1Index, EVector[eIndex].v2Index, EVector[eIndex].weight);
			UFSet[s1] = s2;
		}
		++eIndex;
	}
	delete[]UFSet;
	if (edgeNum+1 < graph.getVertexNum())return Graph();
	return resGraph;
}

Graph prim(Graph &graph){
//	//��ʼ�� �㼯��vlist1��vlist2��ѡһ����㣬���ڱ߼���
//	Graph resGraph;
//	list<Vertex> vlist1,vlist2;
//	priority_queue<EdgeNode,vector<EdgeNode>,greater<EdgeNode>> edgeQueueSorted;
//	list<Vertex> &vlist = graph.getVlist();
//	for(list<Vertex>::iterator iter = vlist.begin();iter!=vlist.end();++iter){
//		if(iter==vlist.begin()){
//			resGraph.insertVertex(iter->name);
//			vlist1.push_back(*iter);
//			Edge *pCurrentE = iter->head;
//			while(pCurrentE!=NULL){
//				if(iter->name < pCurrentE->destV)
//					edgeQueueSorted.push(EdgeNode(iter->name,pCurrentE->destV,pCurrentE->cost));
//				pCurrentE = pCurrentE->nextE;
//			}	
//		}
//		else vlist2.push_back(*iter);
//	}
//
//	//ѭ��ѡ��С�ߣ���������ֱ���vlist1��vlist2�У������vlist1���߲���߶���
//	//ֱ����n��
//	while(vlist1.size()<vlist.size()){
//		EdgeNode currentEdgeNode = edgeQueueSorted.top();
//		edgeQueueSorted.pop();
//		if(count_if(vlist1.begin(),vlist1.end(),SameVertex(currentEdgeNode.v1)) ^
//			count_if(vlist1.begin(),vlist1.end(),SameVertex(currentEdgeNode.v2))
//			){
//				//�����
//				if(resGraph.insertVertex(currentEdgeNode.v1)==true){
//					list<Vertex>::iterator iter = find_if(vlist2.begin(),vlist2.end(),SameVertex(currentEdgeNode.v1));
//					assert(iter!=vlist2.end());
//					
//					Edge *pCurrentE = iter->head;
//					while(pCurrentE!=NULL){
//						if(iter->name < pCurrentE->destV)
//						edgeQueueSorted.push(EdgeNode(iter->name,pCurrentE->destV,pCurrentE->cost));
//						pCurrentE = pCurrentE->nextE;
//					}	
//
//					vlist1.push_back(*iter);
//					vlist2.erase(iter);
//				}
//				else{
//					bool insertRes = resGraph.insertVertex(currentEdgeNode.v2);
//					assert(insertRes);
//
//					list<Vertex>::iterator iter = find_if(vlist2.begin(),vlist2.end(),SameVertex(currentEdgeNode.v2));
//					assert(iter!=vlist2.end());
//					
//					Edge *pCurrentE = iter->head;
//					while(pCurrentE!=NULL){
//						if(iter->name < pCurrentE->destV)
//						edgeQueueSorted.push(EdgeNode(iter->name,pCurrentE->destV,pCurrentE->cost));
//						pCurrentE = pCurrentE->nextE;
//					}	
//
//					vlist1.push_back(*iter);
//					vlist2.erase(iter);
//				}
//				//�����
//				resGraph.insertEdge(currentEdgeNode.v1,currentEdgeNode.v2,currentEdgeNode.weight);
//		}
//
//	}
//
//	//����
//	return resGraph;

	Graph resGraph;
	for (int i = 0; i < graph.getVlist().size(); ++i)resGraph.getVlist().push_back(new Vertex(graph.getVlist()[i]->name));
	if (graph.getVlist().size() <= 1)return resGraph;
	set<int> vIndice1, vIndice2;
	priority_queue<EdgeNode, vector<EdgeNode>, greater<EdgeNode>> edgeQueueSorted;
	//��ʼ�� �㼯��vIndice1��vIndice2��ѡһ����㣬���ڱ߼���
	vIndice1.insert(0);
	for (int i = 1; i < graph.getVlist().size(); ++i)vIndice2.insert(i);
	Edge *current = graph.getVlist()[0]->head;
	while (current != nullptr){
		edgeQueueSorted.push(EdgeNode(0,current->destVIndex ,current->cost));
		current = current->nextE;
	}

	while (!edgeQueueSorted.empty()){
		EdgeNode en = edgeQueueSorted.top();
		edgeQueueSorted.pop();
		if (vIndice1.count(en.v1Index) > 0 && vIndice1.count(en.v2Index) == 0){
			vIndice1.insert(en.v2Index);
			vIndice2.erase(en.v2Index);
			resGraph.insertEdge(en.v1Index,en.v2Index,en.weight);
			Edge *current = graph.getVlist()[en.v2Index]->head;
			while (current != nullptr){
				if (vIndice2.count(current->destVIndex) > 0){
					if (current->destVIndex<en.v2Index)edgeQueueSorted.push(EdgeNode(current->destVIndex, en.v2Index, current->cost));
					else edgeQueueSorted.push(EdgeNode(en.v2Index, current->destVIndex, current->cost));
				}
				current = current->nextE;
			}
		}
		if (vIndice1.count(en.v2Index) > 0 && vIndice1.count(en.v1Index) == 0){
			vIndice1.insert(en.v1Index);
			vIndice2.erase(en.v1Index);
			resGraph.insertEdge(en.v1Index, en.v2Index, en.weight);
			Edge *current = graph.getVlist()[en.v1Index]->head;
			while (current != nullptr){
				if (vIndice2.count(current->destVIndex) > 0){
					if (en.v1Index<current->destVIndex)edgeQueueSorted.push(EdgeNode(en.v1Index, current->destVIndex, current->cost));
					else edgeQueueSorted.push(EdgeNode(current->destVIndex, en.v1Index, current->cost));
				}
				current = current->nextE;
			}
		}
	}
	return resGraph;


}

//������ȱ���
void DFSRecursive(Graph &graph, int start,bool *visits){
	if (visits[start] == true)return;
	cout<<graph.getVlist()[start]->name<<" ";
	visits[start] = true;
	Edge *curr = graph.getVlist()[start]->head;
	while (curr != nullptr){
		DFSRecursive(graph,curr->destVIndex,visits);
		curr = curr->nextE;
	}
}
void DFS(Graph &graph,int start){
	bool *visits = new bool[graph.getVlist().size()];
	for (int i = 0; i < graph.getVlist().size(); ++i)visits[i] = false;
	DFSRecursive(graph,start,visits);
	cout << endl;
	delete[]visits;
}

//������ȱ���
void BFS(Graph &graph, int start){
	bool *visits = new bool[graph.getVlist().size()];
	for (int i = 0; i < graph.getVlist().size(); ++i)visits[i] = false;
	queue<int> que;
	que.push(start);
	visits[start] = true;
	while (!que.empty()){
		cout << graph.getVlist()[que.front()]->name<<" ";
		Edge *curr = graph.getVlist()[que.front()]->head;
		que.pop();
		while (curr != nullptr){
			if (visits[curr->destVIndex] == false){
				que.push(curr->destVIndex);
				visits[curr->destVIndex] = true;
			}
			curr = curr->nextE;
		}
	}
	cout << endl;
	delete[]visits;
}


int _tmain(int argc, _TCHAR* argv[])
{
	Graph theGraph;
	theGraph.insertVertex('A');
	theGraph.insertVertex('B');
	theGraph.insertVertex('C');
	theGraph.insertVertex('D');
	theGraph.insertVertex('E');
	theGraph.insertVertex('F');

	theGraph.insertEdge(0,1,7);
	theGraph.insertEdge(0,2,5);
	theGraph.insertEdge(0,3,7);
	theGraph.insertEdge(0, 5, 1);
	theGraph.insertEdge(1,3,10);
	theGraph.insertEdge(3,2,3);
	theGraph.insertEdge(2, 4, 6);
	theGraph.insertEdge(1,2,9);
	theGraph.insertEdge(3, 5, 4);
	theGraph.describe();
	cout << endl;

	/*cout << "DFS:";
	DFS(theGraph,5);
	cout << "BFS:";
	BFS(theGraph,5);*/

	Graph resG1 = kruskal(theGraph);
	resG1.describe();
	cout << endl;
	Graph resG2 = prim(theGraph);
	resG2.describe();
	cout << endl;
	while(getchar()!='\n');
	getchar();
	return 0;
}

