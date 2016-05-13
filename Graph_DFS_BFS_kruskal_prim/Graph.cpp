#include "StdAfx.h"
#include "Graph.h"
#include "assert.h"

//找对应边的权值，-1表示两点不连通或不存在这两点
int Graph::getEdgeWeight(const char v1, const char v2)
{
	int v1Index = getVertexPos(v1);
	int v2Index = getVertexPos(v2);
	if (v1Index == -1||v2Index==-1)return -1;
	Edge *currentPE = vlist[v1Index]->head;
	while(currentPE != nullptr){
		if (currentPE->destVIndex == v2Index)return currentPE->cost;
		currentPE = currentPE->nextE;
	}
	return -1;
}

int Graph::getEdgeWeight(const int v1Index, const int v2Index)
{
	if (v1Index<0 || v1Index >= vlist.size() || v2Index<0 || v2Index >= vlist.size())return -1;
	Edge *currentPE = vlist[v1Index]->head;
	while (currentPE != nullptr){
		if (currentPE->destVIndex == v2Index)return currentPE->cost;
		currentPE = currentPE->nextE;
	}
	return -1;
}

bool Graph::insertVertex(const char vname_nvertex)
{
	if(getVertexPos(vname_nvertex)==-1){
		Vertex *newV = new Vertex(vname_nvertex);
		vlist.push_back(newV);
		return true;
	}
	else return false;
}
bool Graph::removeVertex(const int vIndex)
{
	if (vIndex < 0 || vIndex >= vlist.size())return false;
	Edge *pCurrentE = vlist[vIndex]->head;
	while(pCurrentE!=nullptr){
		Edge *pE2 = vlist[pCurrentE->destVIndex]->head;
		Edge *pE2pre = nullptr;
		while (pE2 != nullptr){
			if (pE2->destVIndex != vIndex){
				pE2pre = pE2;
				pE2 = pE2->nextE;
			}
			else{
				if (pE2pre != nullptr){
					pE2pre->nextE = pE2->nextE;
					delete pE2;
				}
				else{
					vlist[pCurrentE->destVIndex]->head = pE2->nextE;
					delete pE2;
				}
				break;
			}
		}
		vlist[vIndex]->head = pCurrentE->nextE;
		delete pCurrentE;
		--edgeNum;
		pCurrentE = vlist[vIndex]->head;	
	}
	vlist[vIndex] = vlist[vlist.size() - 1];
	pCurrentE = vlist[vIndex]->head;
	while (pCurrentE != nullptr){
		Edge *pE2 = vlist[pCurrentE->destVIndex]->head;
		while(pE2->destVIndex!=vlist.size()-1&&pE2!=nullptr)pE2=pE2->nextE;
		if (pE2 != nullptr)pE2->destVIndex = vIndex;
		pCurrentE = pCurrentE->nextE;
	}
	vlist.pop_back();
	return true;
}
bool Graph::insertEdge(const int v1Index, const int v2Index, const int _cost)
{
	if (isExistEdge(v1Index, v2Index) == true)return false;
	Edge *newE1 = new Edge(v2Index, _cost);
	if (vlist[v1Index]->head == nullptr)vlist[v1Index]->head = newE1;
	else{
		Edge *pcurrentE = vlist[v1Index]->head;
		while(pcurrentE->nextE!=nullptr)pcurrentE = pcurrentE->nextE;
		pcurrentE->nextE = newE1;
	}

	Edge *newE2 = new Edge(v1Index, _cost);
	if (vlist[v2Index]->head == nullptr)vlist[v2Index]->head = newE2;
	else{
		Edge *pcurrentE = vlist[v2Index]->head;
		while (pcurrentE->nextE != nullptr)pcurrentE = pcurrentE->nextE;
		pcurrentE->nextE = newE2;
	}
	++edgeNum;
	return true;
}

bool Graph::removeEdge(const int v1Index, const int v2Index)
{
	if (isExistEdge(v1Index, v2Index) == false)return false;
	if (vlist[v1Index]->head->destVIndex == v2Index){ Edge *pEdel = vlist[v1Index]->head;  vlist[v1Index]->head = pEdel->nextE; delete pEdel; }
	else{
		Edge *pPre = vlist[v1Index]->head;
		Edge *pCurrentE = pPre->nextE;
		while(pCurrentE!=nullptr){
			if (pCurrentE->destVIndex == v2Index){ 
				pPre->nextE = pCurrentE->nextE;
				delete pCurrentE;
				break;
			}
			else{
				pPre = pCurrentE;
				pCurrentE = pCurrentE->nextE;
			}
		}
	}

	if (vlist[v2Index]->head->destVIndex == v1Index){ Edge *pEdel = vlist[v2Index]->head;  vlist[v2Index]->head = pEdel->nextE; delete pEdel; }
	else{
		Edge *pPre = vlist[v2Index]->head;
		Edge *pCurrentE = pPre->nextE;
		while (pCurrentE != nullptr){
			if (pCurrentE->destVIndex == v1Index){
				pPre->nextE = pCurrentE->nextE;
				delete pCurrentE;
				break;
			}
			else{
				pPre = pCurrentE;
				pCurrentE = pCurrentE->nextE;
			}
		}
	}
	--edgeNum;
	return true;
}

bool Graph::isExistEdge(const int v1Index, const int v2Index){
	if (v1Index < 0 || v1Index >= vlist.size() || v2Index < 0 || v2Index >= vlist.size())return false;
	Edge *currentE = vlist[v1Index]->head;
	while (currentE != nullptr){
		if (currentE->destVIndex == v2Index)return true;
		else currentE = currentE->nextE;
	}
	return false;
}


Edge* Graph::getFirstNeighbor(int vIndex)
{
	return vlist[vIndex]->head;
}
Edge* Graph::getNextNeighbor(int vIndex, int preDestVIndex)
{
	Edge *curr = vlist[vIndex]->head;
	while (curr != nullptr){
		if (curr->destVIndex == preDestVIndex)return curr->nextE;
		else curr = curr->nextE;
	}
	return nullptr;
}

void Graph::describe()const{
	for (int i = 0; i < vlist.size();++i){
		cout<<"点"<<vlist[i]->name<<":";
		Edge *pEdge = vlist[i]->head;
		if(pEdge==nullptr)cout<<"与其他顶点不连通";
		while (pEdge != nullptr){
			cout<<"与点"<<vlist[pEdge->destVIndex]->name<<"连通，权值="<<pEdge->cost<<";";
			pEdge = pEdge->nextE;
		}
		cout<<endl;
	}
}