#include "StdAfx.h"
#include "ClueBinaryTree.h"

ClueBinaryTree::~ClueBinaryTree(void)
{
}

bool ClueBinaryTree::copyFromBinaryTree(BinaryTreeNode *btRoot){
	if (btRoot == nullptr)return false;
	clear();
	root = new ClueBinaryTreeNode(btRoot->data);
	root->ltag = 0; root->rtag = 0;
	queue<pair<ClueBinaryTreeNode *, BinaryTreeNode *>> que;
	que.push(make_pair(root,btRoot));
	
	while (!que.empty()){
		auto pairNode = que.front();
		que.pop();
		if (pairNode.second->leftchild != nullptr){
			pairNode.first->leftchild = new ClueBinaryTreeNode(pairNode.second->leftchild->data);
			pairNode.first->leftchild->ltag = 0; pairNode.first->leftchild->rtag = 0;
			que.push(make_pair(pairNode.first->leftchild, pairNode.second->leftchild));
		}
		if (pairNode.second->rightchild != nullptr){
			pairNode.first->rightchild = new ClueBinaryTreeNode(pairNode.second->rightchild->data);
			pairNode.first->rightchild->ltag = 0; pairNode.first->rightchild->rtag = 0;
			que.push(make_pair(pairNode.first->rightchild, pairNode.second->rightchild));
		}
	}
	ClueBinaryTreeNode *pre = nullptr;
	clueDeal(root, pre);
}

void ClueBinaryTree::clueDeal(ClueBinaryTreeNode *curr, ClueBinaryTreeNode *&pre){
	if (curr->leftchild == nullptr)curr->ltag = 1;
	if (curr->rightchild == nullptr)curr->rtag = 1;

	if (curr->leftchild != nullptr && curr->ltag == 0){
		clueDeal(curr->leftchild, pre);
	}
	if (pre != nullptr){
		if (pre->rightchild == nullptr){
			pre->rightchild = curr;
			pre->rtag = 1;
		}
		if (curr->leftchild == nullptr){
			curr->leftchild = pre;
			curr->ltag = 1;
		}
	}
	pre = curr;
	if (curr->rightchild != nullptr && curr->rtag == 0)clueDeal(curr->rightchild, pre);
}

ClueBinaryTreeNode *ClueBinaryTree::first(ClueBinaryTreeNode *current){
	ClueBinaryTreeNode *p = current;
	while(p->ltag == 0)p = p->leftchild;
	return p;
}
ClueBinaryTreeNode *ClueBinaryTree::last(ClueBinaryTreeNode *current){
	ClueBinaryTreeNode *p = current;
	while(p->rtag == 0)p = p->rightchild;
	return p;
}
ClueBinaryTreeNode *ClueBinaryTree::next(ClueBinaryTreeNode *current){
	if(current->rtag == 1)return current->rightchild;
	else return first(current->rightchild);
}
ClueBinaryTreeNode *ClueBinaryTree::prev(ClueBinaryTreeNode *current){
	if(current->ltag == 1)return current->leftchild;
	else return last(current->leftchild);
}
void ClueBinaryTree::inorder(void (*visit)(ClueBinaryTreeNode *p)){
	ClueBinaryTreeNode *current = first(root);
	while(current != NULL){
		visit(current);
		current = next(current);
	}

}
void ClueBinaryTree::preorder(void (*visit)(ClueBinaryTreeNode *p)){
	ClueBinaryTreeNode *current = root;
	while(current != NULL){
		visit(current);
		if(current->ltag == 0)current = current->leftchild;
		else if(current->rtag == 0)current = current->rightchild;
		else{
			while(current != NULL && current->rtag == 1)current = current->rightchild;
			if(current != NULL)current = current->rightchild;
		}
	}
}
void ClueBinaryTree::postorder(void (*visit)(ClueBinaryTreeNode *p)){
	ClueBinaryTreeNode *current = root;
	while(current->ltag == 0 || current->rtag == 0){
		if(current->ltag == 0)current = current->leftchild;
		else if(current->rtag == 0)current = current->rightchild;
	}
	visit(current);

	ClueBinaryTreeNode *father;
	while((father = findparent(current)) != NULL){
		if(father->rightchild == current || father->rtag == 1)current = father;
		else{
			current = father->rightchild;
			while(current->ltag == 0 || current->rtag == 0){
				if(current->ltag == 0)current = current->leftchild;
				else if(current->rtag == 0)current = current->rightchild;
			}
		}
		visit(current);
	}
}
ClueBinaryTreeNode *ClueBinaryTree::findparent(ClueBinaryTreeNode *current){
	if(current == root)return NULL;
	ClueBinaryTreeNode *p;
	for(p=current;p->ltag==0;p=p->leftchild);
	if(p->leftchild != NULL){
		for(p=p->leftchild;p!=NULL && p->leftchild!=current && p->rightchild!=current;p=p->rightchild);
	}
	if(p==NULL || p->leftchild == NULL){
		for(p=current;p->rtag==0;p=p->rightchild);
		for(p=p->rightchild;p!=NULL && p->leftchild!=current && p->rightchild!=current;p=p->leftchild);
	}
	return p;
}

void ClueBinaryTree::insertRight(ClueBinaryTreeNode *father,int data){
	if(father == NULL)return;
	ClueBinaryTreeNode *insertPtr = new ClueBinaryTreeNode();
	insertPtr->data = data;
	insertPtr->ltag = 1;
	insertPtr->rtag = 1;

	if(father->rtag == 1){
		insertPtr->rightchild = father->rightchild;
		insertPtr->leftchild = father;
		father->rtag=0;
		father->rightchild=insertPtr;
	}
	else{
		ClueBinaryTreeNode *originRightchild = father->rightchild;
		father->rightchild = insertPtr;
		
		insertPtr->leftchild = father;
		insertPtr->rightchild = originRightchild;
		insertPtr->rtag=0;
		first(originRightchild)->leftchild = insertPtr;
	}

}
void ClueBinaryTree::insertLeft(ClueBinaryTreeNode *father,int data){
	if(father == NULL)return;
	ClueBinaryTreeNode *insertPtr = new ClueBinaryTreeNode();
	insertPtr->data = data;
	insertPtr->ltag = 1;
	insertPtr->rtag = 1;

	if(father->ltag == 1){
		insertPtr->rightchild = father;
		insertPtr->leftchild = father->leftchild;

		father->ltag=0;
		father->leftchild=insertPtr;
	}
	else{
		ClueBinaryTreeNode *originLeftchild = father->leftchild;
		father->leftchild = insertPtr;
		
		insertPtr->rightchild = father;
		insertPtr->leftchild = originLeftchild;
		insertPtr->ltag=0;
		last(originLeftchild)->rightchild = insertPtr;
	}
}
void ClueBinaryTree::removeNode(ClueBinaryTreeNode *removePtr){
	if(removePtr == NULL)return;
	ClueBinaryTreeNode *father = findparent(removePtr);
	//删除的是根节点
	if(father == NULL){
		//无子
		if(removePtr->ltag==1 && removePtr->rtag==1){delete removePtr;root = NULL;return;}
		else{
			//无左子，有右子
			if(removePtr->ltag == 1){
				first(removePtr->rightchild)->leftchild = NULL;
				root = removePtr->rightchild;
			}
			//有左子，无右子
			else if(removePtr->rtag == 1){
				last(removePtr->leftchild)->rightchild = NULL;
				root = removePtr->leftchild;
			}
			//有左子，有右子
			else{
				ClueBinaryTreeNode *lastPtr = last(removePtr->leftchild);
				root = removePtr->leftchild;
				lastPtr->rightchild = removePtr->rightchild;
				lastPtr->rtag = 0;
				first(removePtr->rightchild)->leftchild = lastPtr;
			}
		}
	}
	//删除的是右子
	else if(father->rtag == 0 && father->rightchild == removePtr){
		//无子
		if(removePtr->ltag==1 && removePtr->rtag==1){
			father->rtag = 1;
			father->rightchild = removePtr->rightchild;
			
		}
		else{
			//无左子，有右子
			if(removePtr->ltag == 1){
				father->rightchild = removePtr->rightchild;
				first(removePtr->rightchild)->leftchild = removePtr->leftchild;
			}
			//有左子，无右子
			else if(removePtr->rtag == 1){
				father->rightchild = removePtr->leftchild;
				last(removePtr->leftchild)->rightchild = removePtr->rightchild;
			}
			//有左子，有右子
			else{
				ClueBinaryTreeNode *leftLastPtr = last(removePtr->leftchild);
				father->rightchild = removePtr->leftchild;
				leftLastPtr->rightchild = removePtr->rightchild;
				leftLastPtr->rtag = removePtr->rtag;
				first(removePtr->rightchild)->leftchild=leftLastPtr;
			}
		}

	}
	//删除的是左子
	else if(father->ltag == 0 && father->leftchild == removePtr){
		//无子
		if(removePtr->ltag==1 && removePtr->rtag==1){
			father->ltag = 1;
			father->leftchild = removePtr->leftchild;
		}
		else{
			//无左子，有右子
			if(removePtr->ltag == 1){
				father->leftchild = removePtr->rightchild;
				first(removePtr->rightchild)->leftchild = removePtr->leftchild;
			}
			//有左子，无右子
			else if(removePtr->rtag == 1){
				father->leftchild = removePtr->leftchild;
				last(removePtr->leftchild)->rightchild = removePtr->rightchild;
			}
			//有左子，有右子
			else{
				father->leftchild = removePtr->leftchild;
				ClueBinaryTreeNode *leftLastPtr = last(removePtr->leftchild);
				leftLastPtr->rightchild = removePtr->rightchild;
				leftLastPtr->rtag = removePtr->rtag;
				first(removePtr->rightchild)->leftchild = leftLastPtr;
			}
		}
	}
	delete removePtr;
	return;

}

void ClueBinaryTree::clear(){
	clear(root);
	root = nullptr;
}

void ClueBinaryTree::clear(ClueBinaryTreeNode *_root){
	if (_root == nullptr)return;
	if (_root->leftchild != nullptr &&_root->ltag == 0)clear(_root->leftchild);
	if (_root->rightchild != nullptr &&_root->rtag == 0)clear(_root->rightchild);
	delete _root;
}

void ClueBinaryTree::insertRoot(int data){
	if(root != NULL)return;
	ClueBinaryTreeNode *insertPtr = new ClueBinaryTreeNode();
	insertPtr->data = data;
	insertPtr->ltag = 1;
	insertPtr->rtag = 1;
	root = insertPtr;
}