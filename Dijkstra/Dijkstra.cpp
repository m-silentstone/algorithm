// Dijkstra.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Graph.h"

vector<int> dijkstra(Graph &graph,int start){
	vector<int> resV(graph.getVlist().size(),SHRT_MAX);
	vector<bool> isFound(graph.getVlist().size(),false);
	resV[start] = 0;
	isFound[start] = true;
	int index = start;
	int minDist = 0;
	while (index != -1){
		Edge *curr = graph.getVlist()[index]->head;
		while (curr != nullptr){
			if (resV[curr->destVIndex] > resV[index] + curr->cost){
				resV[curr->destVIndex] = resV[index] + curr->cost;
			}
			curr = curr->nextE;
		}
		index = -1;
		minDist = SHRT_MAX;
		for (int i = 0; i < graph.getVlist().size(); ++i){
			if (isFound[i] == false && resV[i] < minDist){
				index = i;
				minDist = resV[i];
			}
		}
		if (index != -1)isFound[index]=true;
	}
	return resV;
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

	theGraph.insertEdge(0, 1, 7);
	theGraph.insertEdge(0, 2, 5);
	theGraph.insertEdge(0, 3, 7);
	theGraph.insertEdge(0, 5, 1);
	theGraph.insertEdge(1, 3, 10);
	theGraph.insertEdge(3, 2, 3);
	theGraph.insertEdge(2, 4, 6);
	theGraph.insertEdge(1, 2, 9);
	theGraph.insertEdge(3, 5, 4);
	theGraph.describe();
	cout << endl;
	vector<int> resV = dijkstra(theGraph,3);
	for (int i = 0; i < resV.size(); ++i)cout << i << ":" << resV[i] << endl;

	while (getchar() != '\n');
	getchar();
	return 0;
}

