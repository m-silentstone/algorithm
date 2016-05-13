// TrieTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "assert.h"
#include <set>
#include <stack>
#include <string>
#include <iostream>
using namespace std;

class TrieNode{
public:
	char character;
	TrieNode *parent;
	TrieNode *children[26];
	set<int> idgroup;
	int frequency;
	TrieNode(){
		character = '?';
		frequency = 0;
		parent = NULL;
		for(int i=0;i<26;i++){
			children[i] = NULL;
		}
	}
	void insertStringTo(TrieNode *root, string word, int id);
	void deleteStringFrom(TrieNode *root, string word, int id);
};

void TrieNode::insertStringTo(TrieNode *root, string word, int id){
	if(word.length() == 0)return;
	char ch = word.at(0);
	int insertIndex = ch-'a';
	if(root->children[insertIndex] == NULL){
		root->children[insertIndex] = new TrieNode();
		root->children[insertIndex]->parent = root;
		root->children[insertIndex]->character = ch;
	}
	root->children[insertIndex]->idgroup.insert(id);

	string restword = word.substr(1);
	if(restword.length() == 0)root->children[insertIndex]->frequency++;
	insertStringTo(root->children[insertIndex], restword, id);
}

void TrieNode::deleteStringFrom(TrieNode *root, string word, int id){
	if(word.length() == 0)return;
	char ch = word.at(0);
	int insertIndex = ch-'a';
	if(root->children[insertIndex] == NULL)return;
	root->children[insertIndex]->idgroup.erase(id);
	string restWord = word.substr(1);
	if(restWord.length() == 0){
		root->children[insertIndex]->frequency--;
		assert(frequency>=0);
		if(root->children[insertIndex]->idgroup.empty()){
			delete root->children[insertIndex];
			root->children[insertIndex] = NULL;
		}
	}
	deleteStringFrom(root->children[insertIndex], restWord,id);
}


class TrieTree{
public:
	TrieNode *root;

	TrieTree(){root = new TrieNode();}
	void insertWord(string word, int id);
	void deleteWord(string word, int id);
	void updateWord(string oldword, string newword, int id);
	void outputWordFrequency();
	void prefixOutputWordFrequency(string prefix);
};

void TrieTree::insertWord(string word, int id){
	root->insertStringTo(root,word,id);
}

void TrieTree::deleteWord(string word, int id){
	root->deleteStringFrom(root,word,id);
}

void TrieTree::updateWord(string oldword, string newword, int id){
	root->deleteStringFrom(root,oldword,id);
	root->insertStringTo(root,newword,id);
}

void TrieTree::outputWordFrequency(){
	stack<TrieNode *> workstack;
	workstack.push(root);
	while(workstack.empty() == false){
		TrieNode *node = workstack.top();
		workstack.pop();
		if(node->frequency>0){
			TrieNode *temp = node;
			string word="";
			while(temp->character != '?'){
				word+=temp->character;
				temp = temp->parent;
			}
			for(int i=0;i<word.length()/2;i++){
				char cht = word.at(i);
				word[i] = word[word.length()-i-1];
				word[word.length()-i-1] = cht;
			}
			cout<<word<<":"<<node->frequency<<endl;
		}

		for(int i=25;i>=0;i--){
			if(node->children[i] != NULL)workstack.push(node->children[i]);
		}
	}
}

void TrieTree::prefixOutputWordFrequency(string prefix){
	string resthead = prefix;
	TrieNode *node = root;
	while(resthead.length()>0){
		int index = resthead.at(0) - 'a';
		if(node->children[index] == NULL){cout<<"word not found."<<endl;return;}
		node = node->children[index];
		resthead = resthead.substr(1);
	}

	stack<TrieNode *> workstack;
	workstack.push(node);
	while(workstack.empty() == false){
		TrieNode *worknode = workstack.top();
		workstack.pop();
		if(worknode->frequency>0){
			TrieNode *temp = worknode;
			string word="";
			while(temp->character != '?'){
				word+=temp->character;
				temp = temp->parent;
			}
			for(int i=0;i<word.length()/2;i++){
				char cht = word.at(i);
				word[i] = word[word.length()-i-1];
				word[word.length()-i-1] = cht;
			}
			cout<<word<<":"<<worknode->frequency<<endl;
		}

		for(int i=25;i>=0;i--){
			if(worknode->children[i] != NULL)workstack.push(worknode->children[i]);
		}
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	TrieTree trieTree;
	//string inputstr = "abc";
	trieTree.insertWord("abc",1);
	trieTree.insertWord("aaa",2);
	trieTree.insertWord("aaa",2);
	trieTree.insertWord("aaa",2);
	trieTree.insertWord("bas",3);
	trieTree.insertWord("csd",4);
	trieTree.insertWord("aa",5);
	trieTree.insertWord("a",6);
	trieTree.insertWord("ghfertxcv",7);
	trieTree.insertWord("er",8);

	//trieTree.deleteWord("aa",1);

	//trieTree.updateWord("a","ghf",6);

	//trieTree.outputWordFrequency();
	trieTree.prefixOutputWordFrequency("a");
	char result;
	cin>>result;
	return 0;
}

