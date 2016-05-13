// ClueBinaryTreeMain.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ClueBinaryTree.h"
#include <iostream>
using namespace std;

void output(ClueBinaryTreeNode *p){
	cout<<p->data<<"  ";
}

int _tmain(int argc, _TCHAR* argv[])
{
	ClueBinaryTree cbt;
	
	BinaryTreeNode *btRoot = new BinaryTreeNode(0);
	btRoot->leftchild = new BinaryTreeNode(1);
	btRoot->rightchild = new BinaryTreeNode(2);
	btRoot->leftchild->leftchild = new BinaryTreeNode(3);
	btRoot->leftchild->rightchild = new BinaryTreeNode(4);
	btRoot->leftchild->rightchild->leftchild = new BinaryTreeNode(5);
	btRoot->leftchild->rightchild->rightchild = new BinaryTreeNode(6);

	cbt.copyFromBinaryTree(btRoot);

	//adjustInOrder
	//ClueBinaryTreeNode *root = new ClueBinaryTreeNode(0);
	//root->tag0();
	//root->leftchild = new ClueBinaryTreeNode(1); root->leftchild->tag0();
	//root->rightchild = new ClueBinaryTreeNode(2); root->rightchild->tag0();
	//ClueBinaryTreeNode *ptr1 = root->leftchild;
	//ptr1->leftchild = new ClueBinaryTreeNode(3); ptr1->leftchild->tag0();
	//ptr1->rightchild = new ClueBinaryTreeNode(4); ptr1->rightchild->tag0();
	//ClueBinaryTreeNode *ptr4 = ptr1->rightchild;
	//ptr4->leftchild = new ClueBinaryTreeNode(5); ptr4->leftchild->tag0();
	//ptr4->rightchild = new ClueBinaryTreeNode(6); ptr4->rightchild->tag0();
	//cbt.setRoot(root);
	//cbt.adjustInOrder();


	/*cbt.insertRoot(12);
	cbt.insertLeft(cbt.getRoot(),15);
	cbt.insertLeft(cbt.getRoot(),19);
	cbt.insertLeft(cbt.getRoot(),11);
	
	cbt.insertRight(cbt.getRoot(),21);
	cbt.insertLeft(cbt.getRoot()->rightchild,17);
	cbt.insertRight(cbt.getRoot()->rightchild,18);
	cbt.insertRight(cbt.getRoot()->leftchild,22);
	cbt.insertRight(cbt.getRoot()->leftchild->leftchild,6);
	cbt.insertRight(cbt.getRoot()->leftchild->leftchild->rightchild,9);
	cbt.insertLeft(cbt.getRoot()->leftchild->leftchild->rightchild,31);

	cbt.removeNode(cbt.getRoot());
	
	cout<<"中序：";
	cbt.inorder(output);
	cout<<endl;

	cout<<"前序：";
	cbt.preorder(output);
	cout<<endl;

	cout<<"后序：";
	cbt.postorder(output);
	cout<<endl;

	cbt.clear();*/




	/*ClueBinaryTreeNode *p;
	p = cbt.getRoot();
	if(cbt.findparent(p)!=NULL){
		cout<<p->data<<"的父节点是"<<cbt.findparent(p)->data<<endl;
	}
	else{cout<<p->data<<"是根节点"<<endl;}

	p = cbt.getRoot()->leftchild->leftchild;
	if(cbt.findparent(p)!=NULL){
		cout<<p->data<<"的父节点是"<<cbt.findparent(p)->data<<endl;
	}
	else{cout<<p->data<<"是根节点"<<endl;}
	p = cbt.getRoot()->rightchild;
	if(cbt.findparent(p)!=NULL){
		cout<<p->data<<"的父节点是"<<cbt.findparent(p)->data<<endl;
	}
	else{cout<<p->data<<"是根节点"<<endl;}*/

	char res;
	cin>>res;
	return 0;
}

