#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Edge{
public:
	int destVIndex;
	int cost;
	Edge *nextE;
	Edge(){ destVIndex = -1; cost = 0; nextE = nullptr; }
	Edge(int _destVIndex, int _cost, Edge *_nextE = nullptr) :destVIndex(_destVIndex), cost(_cost), nextE(_nextE){}
	bool operator !=(Edge &edge2){ return (edge2.destVIndex == destVIndex) ? false : true; }
};

class Vertex{
public:
	char name;
	Edge *head;//边链表的头指针
	Vertex(){ name = '?'; head = nullptr; }
	Vertex(char _name, Edge *_head = nullptr) :name(_name), head(_head){}
	bool operator ==(Vertex &_vertex){ return name == _vertex.name; }
};


class Graph
{
private:
	vector<Vertex*>  vlist;//顶点链表
	int edgeNum;
	int getVertexPos(const char vname){
		for(int index = 0;index<vlist.size();++index){
			if(vlist[index]->name == vname)return index;
		}
		return -1;
	}
public:
	Graph(void){
		edgeNum = 0;
	}
	~Graph(void){

	}
	unsigned getEdgeNum()const{ return edgeNum; }
	unsigned getVertexNum()const{return vlist.size();} 
	vector<Vertex*>& getVlist(){return vlist;}
	/*Vertex* getVertex(int i){
		if (i < 0 || i >= vlist.size())return nullptr;
		return vlist[i];
	}*/
	
	int getEdgeWeight(const char v1,const char v2);
	int getEdgeWeight(const int v1Index, const int v2Index);
	
	bool insertVertex(const char vname_nvertex);
	bool removeVertex(const int vIndex);
	bool insertEdge(const int v1Index,const int v2Index,const int _cost);
	bool removeEdge(const int v1Index,const int v2Index);
	bool isExistEdge(const int v1Index, const int v2Index);
	Edge* getFirstNeighbor(int vIndex);
	Edge* getNextNeighbor(int vIndex,int preDestVIndex);
	void describe()const;
};

