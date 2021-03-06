// BinarySearchTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

template<class T>
void outputV(vector<T> &vect){
	for (int i = 0; i < vect.size(); ++i){
		cout << vect[i] << endl;
	}
}

class BST{
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}

	};
private:
	TreeNode *root;
	TreeNode *minIn(TreeNode *root){
		if (root == nullptr)return root;
		TreeNode *curr = root;
		while (curr->left != nullptr)curr = curr->left;
		return curr;
	}
	TreeNode *maxIn(TreeNode *root){
		if (root == nullptr)return root;
		TreeNode *curr = root;
		while (curr->right != nullptr)curr = curr->right;
		return curr;
	}
	TreeNode *ceilingIn(TreeNode *theroot,int val){
		TreeNode *target;
		if (theroot == nullptr)return nullptr;
		if (val == theroot->val)return theroot;
		else if (val > theroot->val)return ceilingIn(theroot->right, val);
		else{
			target = ceilingIn(theroot->left, val);
			if (target == nullptr)return theroot;
			else return target;
		}
	}
	TreeNode *floorIn(TreeNode *theroot, int val){
		TreeNode *target;
		if (theroot == nullptr)return nullptr;
		if (val == theroot->val)return theroot;
		else if (val < theroot->val)return floorIn(theroot->left, val);
		else{
			target = floorIn(theroot->right, val);
			if (target == nullptr)return theroot;
			else return target;
		}
	}
	vector<int> inorderTraversal(TreeNode *theroot){
		vector<int> sortedVect;
		// stack based
		if (theroot == nullptr)return sortedVect;
		stack<TreeNode *>tnStack;
		TreeNode *curr = theroot;
		while (curr != nullptr || tnStack.empty() == false){
			if (curr != nullptr){
				tnStack.push(curr);
				curr = curr->left;
			}
			else{
				curr = tnStack.top();
				sortedVect.push_back(curr->val);
				tnStack.pop();
				curr = curr->right;
			}

		}
		return sortedVect;
	}

public:
	BST(){
		root = nullptr;
	}
	~BST(){
		if (root == nullptr)return;
		TreeNode *curr = root;
		queue<TreeNode*> tnQueue;
		tnQueue.push(root);
		while (!tnQueue.empty()){
			curr = tnQueue.front();
			tnQueue.pop();
			if (curr->left != nullptr)tnQueue.push(curr->left);
			if (curr->right != nullptr)tnQueue.push(curr->right);
			delete curr;
		}
	}
	void insert(int val){
		if (root == nullptr){
			root = new TreeNode(val);
			return;
		}
		TreeNode *curr = root,*pre=root;
		while (curr != nullptr){
			if (val == curr->val)return;
			else if (val < curr->val){
				pre = curr;
				curr = curr->left;
			}
			else{
				pre = curr;
				curr = curr->right;
			}
		}
		if (val < pre->val)pre->left = new TreeNode(val);
		else pre->right = new TreeNode(val);
	}

	bool remove(int val){
		if (root == nullptr){
			return false;
		}
		TreeNode *curr = root, *pre=nullptr;
		while (curr != nullptr){
			if (val == curr->val)break;
			else if (val < curr->val){
				pre = curr;
				curr = curr->left;
			}
			else{
				pre = curr;
				curr = curr->right;
			}
		}
		if (curr == nullptr)return false;
		if (curr->left == nullptr&&curr->right == nullptr){
			if (pre == nullptr){
				delete curr;
				root = nullptr;
				return true;
			}
			else if (pre->left == curr){
				pre->left = nullptr;
				delete curr;
				return true;
			}
			else if (pre->right == curr){
				pre->right = nullptr;
				delete curr;
				return true;
			}
			else return false;
		}
		else if (curr->left != nullptr&&curr->right==nullptr){
			if (pre == nullptr){
				root = curr->left;
				delete curr;
				return true;
			}
			else if (pre->left == curr){
				pre->left = curr->left;
				delete curr;
				return true;
			}
			else if (pre->right == curr){
				pre->right = curr->left;
				delete curr;
				return true;
			}
			else return false;
		}
		else if (curr->left == nullptr&&curr->right != nullptr){
			if (pre == nullptr){
				root = curr->right;
				delete curr;
				return true;
			}
			else if (pre->left == curr){
				pre->left = curr->right;
				delete curr;
				return true;
			}
			else if (pre->right == curr){
				pre->right = curr->right;
				delete curr;
				return true;
			}
			else return false;
		}
		else{
			TreeNode *successive = curr->right;
			while (successive->left != nullptr)successive = successive->left;
			int succVal = successive->val;
			remove(successive->val);
			curr->val = succVal;
		}
	}

	bool search(int val){
		if (root == nullptr){
			return false;
		}
		TreeNode *curr = root;
		while (curr != nullptr){
			if (val == curr->val)return true;
			else if (val < curr->val){
				curr = curr->left;
			}
			else{
				curr = curr->right;
			}
		}
		return false;
	}
	int min(){
		return minIn(root)->val;
	}
	int max(){
		return maxIn(root)->val;
	}
	int ceiling(int val){
		TreeNode *resNode = ceilingIn(root, val);
		if (resNode == nullptr)return -1;
		return resNode->val;
	}
	int floor(int val){
		TreeNode *resNode = floorIn(root, val);
		if (resNode == nullptr)return -1;
		return resNode->val;
	}
	vector<int> outputTree(){
		return inorderTraversal(root);
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	BST bst;
	bst.insert(10);
	bst.insert(5);
	bst.insert(15);
	bst.insert(3);
	bst.insert(8);
	bst.insert(4);
	bst.insert(7);
	bst.insert(9);
	bst.insert(12);
	bst.insert(17);

	outputV(bst.outputTree());

	cout<<"search 8:"<<bst.search(8)<<endl;
	cout << "search 11:" << bst.search(11) << endl;

	cout<<"max:"<<bst.max()<<endl;
	cout<<"min:"<<bst.min()<<endl;

	cout << "ceiling(6):" << bst.ceiling(6)<<endl;
	cout << "ceiling(3):" << bst.ceiling(3) << endl;
	cout << "ceiling(0):" << bst.ceiling(0) << endl;
	cout << "ceiling(13):" << bst.ceiling(13) << endl;
	cout << "ceiling(18):" << bst.ceiling(18) << endl;

	cout << "floor(6):" << bst.floor(6) << endl;
	cout << "floor(3):" << bst.floor(3) << endl;
	cout << "floor(0):" << bst.floor(0) << endl;
	cout << "floor(13):" << bst.floor(13) << endl;
	cout << "floor(18):" << bst.floor(18) << endl;

	bst.remove(2);
	cout << "after remove 2:" << endl;
	outputV(bst.outputTree());
	bst.remove(9);
	cout << "after remove 9:" << endl;
	outputV(bst.outputTree()); 
	bst.remove(3);
	cout << "after remove 3:" << endl;
	outputV(bst.outputTree()); 
	bst.remove(10);
	cout << "after remove 10:" << endl;
	outputV(bst.outputTree());






	while (getchar() == '\n');
	getchar();
	return 0;
}

