//author: Zi Hao(Leo) Zhang, 

#pragma once

#include <stdexcept>
#include <iostream>
using namespace std;
#include <string>
#include <vector>


class Node
{
public:

	Node(int val); // constructor for creating leaf node

	Node(Node* FC, Node* SC); // constructor for creating interior node

	int Storedvalue; // value stored in the leaf node

	int L; // largest value in the first subtree 

	int M; // largest value in the second subtree

	int MaxVal; //the largest value in the subtree

	int FNum; // number of element in the first subtree

	int SNum; // number of element in the second subtree

	int TNum; // number of element in the third subtree

	int MaxNum; // total number of element in the subtree

	Node* parent; // parent of the node

	Node* FirstChild; // first child of the node

	Node* SecondChild; // second child of the node

	Node* ThirdChild; // Third child of the node

};

class TwoThreeTree
{
public:
	TwoThreeTree();

	~TwoThreeTree();

	int Find (int val);

	int Insert(int val); // insert a node into the tree, if inserted returns true, if already existed, returns false

	int Delete(int val); // remove the value from the tree, if removed sucesssfully, return true, else return false

	int Selection(int k); // return the k smallest element in the tree'

	void printTree(vector<int>& Traverse); // output the tree from left to right

	Node* root;

private:

	//Node* root;
	bool isLeafNode(Node* nd); // check if a node is leaf node

	void printRecurse(Node* nd, vector<int>& trav); // helper method which traverse the left node using recursion

	void removeall(Node* nd);

	int inTwoChild(Node* p, Node* c, int InsAt); // insertion helper method, insert node c into p, p has two children

	void updatetree(Node* nd); // update the tree starting from Node nd up to root;

	Node* findsibling(Node* nd); //find the sibling of nd

	int ChildNum(Node* nd);  // return the number of children in the node

	void deleteSibThree(Node* cleft, Node* trav, Node* travP, Node* Sib); //helper for deletion when sibling has three children

	void deleteTravPThree(Node* cleft, Node* trav, Node* travP, Node* Sib); // helper for deletion when travel parent has three children
};
// TODO: reference additional headers your program requires here
