//author: Zi Hao(Leo) Zhang

#include <stdexcept>
#include <iostream>
using namespace std;
#include <string>

#include "TwoThreeTree.h"


//constructor

// PARAM: 

//        

// PRE: 

// POST: a tree with no root is initiated
TwoThreeTree:: TwoThreeTree()
{
	root = NULL;
}


//destructor

// PARAM: 

//        

// PRE: 

// POST: delete all nodes in the tree
TwoThreeTree:: ~TwoThreeTree()
{
	removeall(root);
	root = NULL;

}


//removeall, helper method for destructor

// PARAM: 

//        

// PRE: 

// POST: 
void TwoThreeTree::removeall(Node* nd)
{
	if(nd != NULL)
	{
		removeall(nd->FirstChild);
		removeall(nd->SecondChild);
		removeall(nd->ThirdChild);
		Node* temp = nd;
		delete temp;
	}
	
}


//printTree

// PARAM: 

//        

// PRE: 

// POST: traverse every leaf node and print them out 
void TwoThreeTree::printTree(vector<int>& Traverse)
{
	printRecurse(root,Traverse);
}


//printRecurse, helper method for printTree

// PARAM: 

//        

// PRE: 

// POST: 
void TwoThreeTree:: printRecurse(Node* nd, vector<int>& trav)
{
	if(!(isLeafNode(nd))) // use recursion to visit every child node
	{
		printRecurse(nd->FirstChild, trav);
		printRecurse(nd->SecondChild,trav);
		if(nd->ThirdChild != NULL)
		{
			printRecurse(nd->ThirdChild, trav);
		}
	}
	else if((isLeafNode(nd))) // print out the leaf node
	{
		trav.push_back(nd->Storedvalue);
	}
}


//find

// PARAM: interger val

//        

// PRE: 

// POST: return the rank of the leaf node storing the integer val, return 0 if not found
int TwoThreeTree:: Find(int val)
{

	int index = 0;
	if (root == NULL)
	{
		return 0;
	}
	else if ((isLeafNode(root)) && root->Storedvalue == val) // only node in the tree storing val
	{
		return 1;
	}
	else if ((isLeafNode(root)) && root-> Storedvalue != val)// return zero if not storing val
	{
		return 0;
	}

	Node* travel = root; 

	while(!(isLeafNode(travel->FirstChild)))// travels to the leaf nodes and count the number of node on the left of val on the way
	{
		if(val <= travel->L)
		{
			travel = travel->FirstChild;
		}

		else if (val > travel->L && val <= travel->M)
		{
			index += travel->FNum;
			travel = travel->SecondChild;
		}

		else if (val > travel->M && travel->ThirdChild != NULL)
		{
			index += (travel->FNum + travel->SNum);
			travel = travel ->ThirdChild;
		}

		else if(val > travel->M && travel->ThirdChild == NULL)// the val is larger than M and Third Child does not exist, return 0
		{
			return 0;
		}
	}


	// reached the parent of the leaf node
	if(travel ->FirstChild ->Storedvalue == val)
	{
		index += 1;
	}

	else if(travel->SecondChild ->Storedvalue == val)
	{
		index += 2;
	}
	else if(travel->ThirdChild != NULL && travel->ThirdChild->Storedvalue == val)
	{
		index += 3;
	}
	else if (travel->ThirdChild == NULL) // return 0 if not found in the bottom level
	{
		return 0;
	}

	return index;

}


//selection

// PARAM: k, the rank of the element which the method looks for

//        

// PRE: The tree must contains atleast one leaf node, k must be smaller or equal to the number of leaf nodes in the tree

// POST: return the kth smallest element in the tree
int TwoThreeTree:: Selection(int k)
{
	if(isLeafNode(root->FirstChild)) // check if root is the parent of the leaf nodes, if yes, return the leaf node
	{
		if( k == 1)
		{
			return root->FirstChild->Storedvalue;
		}
		else if (k == 2)
		{
			return root->SecondChild->Storedvalue;
		}
		else if (k == 3 && root->ThirdChild != NULL)
		{
			return root->ThirdChild->Storedvalue;
		}
	}

	Node* travel = root;

	int index = k;

	while(!(isLeafNode(travel->FirstChild))) // travel to the bottom level of the tree, decreasing index on the way
	{
		if(k <= travel->FNum)
		{
			travel = travel->FirstChild;
		}
		else if(k > travel->FNum && k <= (travel->FNum + travel->SNum))
		{
			index -= travel->FNum;
			travel = travel->SecondChild;
		}
		else if(k > (travel->FNum + travel->SNum) && k <= (travel->FNum + travel->SNum + travel->TNum))
		{
			index -= (travel->FNum + travel->SNum);
			travel = travel->ThirdChild;
		}
	}


	// reached the parent of the leaf node, return the leaf node corresponds to index
	if( index == 1)
	{
		return travel->FirstChild->Storedvalue;
	}
	else if (index == 2)
	{
		return travel->SecondChild->Storedvalue;
	}
	else if (index == 3 && travel->ThirdChild != NULL)
	{
		return travel->ThirdChild->Storedvalue;
	}
	else // returing zero if k is bigger than the number of leaf nodes in the tree
	{
		return 0;
	}
}

//insert

// PARAM: The integer which will be inserted to the tree 

//        

// PRE: 

// POST: The integer is inserted, return its rank in the tree
int TwoThreeTree:: Insert(int val)
{
	int InsertedAt = 0; // the rank of the inserted value

	if(root == NULL) // no node in the tree
	{
		root = new Node(val);
		InsertedAt = 1;
		return InsertedAt;
	}

	else if (root != NULL && (isLeafNode(root))) // if there is only one node in the tree
	{
		Node* temp = new Node(val);

		if(val > root->Storedvalue)
		{
			Node* newroot = new Node(root,temp);
			root = root->parent;
			InsertedAt = 2;
			return InsertedAt;
		}

		else if (val <= root->Storedvalue)
		{
			Node* newroot = new Node(temp,root);
			root = root->parent;
			InsertedAt = 1;
			return InsertedAt;
		}
	}

	Node* travel = root;

	while(!(isLeafNode(travel->FirstChild)))// while loop stop when reach the second last level of the tree
	{										// InsertedAt will be accumulated on the way in order to return val's rank at the end
		if(val <= travel->L)
		{
			travel= travel->FirstChild;
		}
		else if(val> travel->L && val <= travel->M )
		{
			InsertedAt += travel->FNum; 
			travel = travel->SecondChild;
		}
		else if(val > travel->M && travel->ThirdChild ==NULL)
		{
			InsertedAt += travel->FNum;
			travel = travel->SecondChild;
		}
		else if(val > travel->M && travel->ThirdChild != NULL)
		{
			InsertedAt += (travel->FNum + travel->SNum);
			travel = travel->ThirdChild;
		}
	}

	//now travel points at the parent of the leaf node

	if(travel->ThirdChild == NULL) // if travel only have two children, make this a function for inserting node to two chilren parent
	{
		Node* newval = new Node(val); // a new node for the new value inserted to the tree
		InsertedAt = inTwoChild(travel, newval, InsertedAt); // insert newval as the child travel and update the tree
		return InsertedAt;

	}// end of if parent of the leaf node has two hildren

	else if(travel -> ThirdChild != NULL)// travel has three children, split is required
	{
		Node* newparent;
		Node* newval = new Node(val); // a new node for the new value inserted to the tree
		
		if(newval->MaxVal <= travel->L)
		{
			InsertedAt += 1;
		}

		else if(newval -> MaxVal > travel -> L && newval ->MaxVal <= travel->M)
		{
			InsertedAt += 2;
		}

		else if (newval -> MaxVal > travel->M && newval->MaxVal <= travel->MaxVal)
		{
			InsertedAt += 3;
		}

		else if(newval->MaxVal > travel->MaxVal)
		{
			InsertedAt += 4;
		}

		while(travel -> ThirdChild != NULL && travel != root) 
		{
			if(newval->MaxVal <= travel->L)// each if statement check where should the new leaf node or subtree should be inserted
			{
				newparent = new Node(newval,travel->FirstChild); //a new node which holds 2 out of 4 children of travel
				travel->FirstChild = travel->SecondChild; // rearranging the parent's leaf nodes
				travel->SecondChild = travel->ThirdChild;
				travel->ThirdChild = NULL;
				travel->L = travel->FirstChild->MaxVal; // updating the L and M 
				travel->M = travel->SecondChild->MaxVal;
				travel->MaxVal = travel->M;
				travel->FNum = travel->FirstChild->MaxNum; // updating the number of elements stored in the subtree
				travel->SNum = travel->SecondChild->MaxNum;
				travel->TNum = 0;
				travel->MaxNum = travel->FNum + travel->SNum + travel->TNum;
				travel = travel-> parent;
				newval = newval->parent;
			}

			else if(newval -> MaxVal > travel -> L && newval ->MaxVal <= travel->M)
			{
				newparent = new Node(travel->FirstChild,newval);
				travel->FirstChild = travel->SecondChild;
				travel->SecondChild = travel->ThirdChild;
				travel->ThirdChild = NULL;
				travel->L = travel->FirstChild->MaxVal;
				travel->M = travel->SecondChild->MaxVal;
				travel->MaxVal = travel->M;
				travel->FNum = travel->FirstChild->MaxNum;
				travel->SNum = travel->SecondChild->MaxNum;
				travel->TNum = 0;
				travel->MaxNum = travel->FNum + travel->SNum + travel->TNum;
				travel = travel-> parent;
				newval = newval->parent;
			}

			else if (newval -> MaxVal > travel->M && newval->MaxVal <= travel->MaxVal)
			{
				newparent = new Node(newval,travel->ThirdChild);
				travel->ThirdChild = NULL;
				travel->L = travel->FirstChild->MaxVal;
				travel->M = travel->SecondChild->MaxVal;
				travel->MaxVal = travel->M;
				travel->TNum = 0;
				travel->MaxNum = travel->FNum + travel->SNum + travel->TNum;
				travel = travel-> parent;
				newval = newval->parent;
			}

			else if(newval->MaxVal > travel->MaxVal)
			{
				newparent = new Node(travel->ThirdChild,newval);
				travel->ThirdChild = NULL;
				travel->L = travel->FirstChild->MaxVal;
				travel->M = travel->SecondChild->MaxVal;
				travel->MaxVal = travel->M;
				travel->TNum = 0;
				travel->MaxNum = travel->FNum + travel->SNum + travel->TNum;
				travel = travel-> parent;
				newval = newval->parent;
			}
			//newval now points to the new subtree separate from the parent after the split
			//travel now points to the new parent of newval
			// the while loop will terminated if travel points to root, or a interior node with only two children
		}	// end of the split while loop
		
		//now travel will be either at the root of the tree
		//or travel is pointing to a interior node with two children

		if(travel == root)// if travel is pointing to the root
		{
			if(travel->ThirdChild == NULL) // the root only have two children
			{
				travel->L = travel->FirstChild->MaxVal; // updating the L and M 
				travel->M = travel->SecondChild->MaxVal;
				travel->MaxVal = travel->M;
				travel->FNum = travel->FirstChild->MaxNum; // updating the number of elements stored in the subtree
				travel->SNum = travel->SecondChild->MaxNum;
				travel->TNum = 0;
				travel->MaxNum = travel->FNum + travel->SNum + travel->TNum;
				inTwoChild(travel, newval,InsertedAt); // call the method for inserting node or subtree into parent with two children
			}

			else if(root->ThirdChild != NULL) // if the root has 3 children
			{
				if(newval->MaxVal <= travel->L) // in each if statement, similar opeartions are being performed
				{
					newparent = new Node(newval,travel->FirstChild); // split the root into two nodes
					travel->FirstChild = travel->SecondChild;		 // rearranging the chldren of root
					travel->SecondChild = travel->ThirdChild;
					travel->ThirdChild = NULL;
					travel->L = travel->FirstChild->MaxVal;			 //updates the attributes
					travel->M = travel->SecondChild->MaxVal;
					travel->MaxVal = travel->M;
					travel->FNum = travel->FirstChild->MaxNum;       //update the number of elements stored in each subtree
					travel->SNum = travel->SecondChild->MaxNum;
					travel->TNum = 0;
					travel->MaxNum = travel->FNum + travel->SNum;
					newval = newval->parent;
					newparent = new Node(newval,travel); // create a new node to join newval and the old root
					root = travel->parent;
				}

				else if(newval -> MaxVal > travel -> L && newval ->MaxVal <= travel->M)
				{
					newparent = new Node(travel->FirstChild,newval);
					travel->FirstChild = travel->SecondChild;
					travel->SecondChild = travel->ThirdChild;
					travel->ThirdChild = NULL;
					travel->L = travel->FirstChild->MaxVal;
					travel->M = travel->SecondChild->MaxVal;
					travel->MaxVal = travel->M;
					travel->FNum = travel->FirstChild->MaxNum;
					travel->SNum = travel->SecondChild->MaxNum;
					travel->TNum = 0;
					travel->MaxNum = travel->FNum + travel->SNum;
					newval = newval->parent;
					newparent = new Node(newval,travel);
					root = travel->parent;
				}

				else if (newval -> MaxVal > travel->M && newval->MaxVal <= travel->MaxVal)
				{
					newparent = new Node(newval,travel->ThirdChild);
					travel->ThirdChild = NULL;
					travel->L = travel->FirstChild->MaxVal;
					travel->M = travel->SecondChild->MaxVal;
					travel->MaxVal = travel->M;
					travel->FNum = travel->FirstChild->MaxNum;
					travel->SNum = travel->SecondChild->MaxNum;
					travel->TNum = 0;
					travel->MaxNum = travel->FNum + travel->SNum;
					newval = newval->parent;
					newparent = new Node(travel,newval);
					root = travel->parent;
				}

				else if(newval->MaxVal > travel->MaxVal)
				{
					newparent = new Node(travel->ThirdChild,newval);
					travel->ThirdChild = NULL;
					travel->L = travel->FirstChild->MaxVal;
					travel->M = travel->SecondChild->MaxVal;
					travel->MaxVal = travel->M;
					travel->FNum = travel->FirstChild->MaxNum;
					travel->SNum = travel->SecondChild->MaxNum;
					travel->TNum = 0;
					travel->MaxNum = travel->FNum + travel->SNum;
					newval = newval->parent;
					newparent = new Node(travel,newval);
					root = travel->parent;
				}
			}// end of if root has three children
		}
		// travel is not the root, but only has two children

		else if(travel != root) // if travel is not pointing to the root
		{
			inTwoChild(travel, newval, InsertedAt); // insert the new subtree into the interior node with two children
		}// end of travel != root

	}// end of if the split is required
	return InsertedAt; // return the rank of the inserted value

}// end of insert 


//remove

// PARAM: The integer which will be deleted

//        

// PRE: The val must be stored in the tree

// POST: If the integer is deleted, return its rank. If not return 0
int TwoThreeTree:: Delete(int val)
{

	int ValIndex = 0; // used to store the rank of the deleted value
	if(Find(val) == 0) // find out whether val is stored in the tree
	{
		return 0;
	}

	if((isLeafNode(root))) //only one node in the tree
	{
		delete root;
		root = NULL;
		ValIndex = 1;
		return ValIndex;
	}
	else if ((isLeafNode(root->FirstChild)) && root->ThirdChild == NULL) // if the root has only two children
	{
		if(val == root->FirstChild ->Storedvalue)
		{
			Node* temp = root->SecondChild;
			delete root->FirstChild;
			delete root;
			root = temp;
			root->parent = NULL;
			ValIndex = 1;
		}
		else if(val == root->SecondChild->Storedvalue)
		{
			Node* temp = root->FirstChild;
			delete root->SecondChild;
			delete root;
			root = temp;
			root->parent = NULL;
			ValIndex = 2;
		}

		return ValIndex;
	}


	Node* travel = root; // pointer to the parent of leaf node storing val

	while(!(isLeafNode(travel->FirstChild)))// while loop stop when reach the second last level of the tree
	{										// ValIndex is being accumulated on the way to the bottom level in order to return the
											// rank of the deleted node
		if(val <= travel->L)
		{
			travel= travel->FirstChild;
		}
		else if(val> travel->L && val <= travel->M )
		{
			ValIndex += travel->FNum;
			travel = travel->SecondChild;
		}
		else if(val > travel->M)
		{
			ValIndex += (travel->FNum + travel->SNum);
			travel = travel->ThirdChild;
		}
	}
	// now travel points to the parent of the leaf node storing val
	
	if(travel->ThirdChild != NULL) //travel has three children
	{
		Node* temp;

		if(travel->FirstChild->Storedvalue == val) // each if statement checks which child needs to be deleted
		{
			temp = travel->FirstChild;
			travel->FirstChild = travel->SecondChild; // re-organize the position of the children
			travel->SecondChild = travel->ThirdChild;
			travel->ThirdChild = NULL;
			travel->L = travel->FirstChild->Storedvalue; // updating the atributes of the parent
			travel->M = travel->SecondChild->Storedvalue;
			travel->MaxVal = travel->M;
			travel->FNum = travel->FirstChild ->MaxNum; // updating number of elements stored in each child
			travel->SNum = travel->SecondChild->MaxNum;
			travel->TNum = 0;
			travel->MaxNum = (travel->FNum + travel->SNum);
			delete temp; // delete the child storing val
			ValIndex += 1;
		}
		
		else if(travel->SecondChild->Storedvalue == val)
		{
			temp = travel->SecondChild;
			travel->SecondChild = travel->ThirdChild;
			travel->ThirdChild = NULL;
			travel->M = travel->SecondChild->Storedvalue;
			travel->MaxVal = travel->M;
			travel->SNum = travel->SecondChild->MaxNum;
			travel->TNum = 0;
			travel->MaxNum = (travel->FNum + travel->SNum);
			delete temp;
			ValIndex +=2;
		}

		else if(travel->ThirdChild->Storedvalue == val)
		{
			temp = travel->ThirdChild;
			travel->ThirdChild = NULL;
			travel->MaxVal = travel->M;
			travel->TNum = 0;
			travel->MaxNum = (travel->FNum + travel->SNum);
			delete temp;
			ValIndex += 3;
		}

		updatetree(travel); // update the interior node on the traverse path
		return ValIndex;    // return the rank of the deleted node

	}// end of if travel has three Children

	else if(travel->ThirdChild == NULL) // travel has only two children
	{
		Node* sibling = findsibling(travel); // finding the sibling of travel

		Node* travelparent = travel->parent; // points to the parent of travel;
		Node* childleft; // child being left after deletion
		Node* newval; // the new node that replace travel;

		if(val == travel ->FirstChild ->Storedvalue) // delete the node storing val, and separate the other child from the parent
		{
			childleft = travel->SecondChild;
			childleft->parent = NULL;
			delete travel->FirstChild;
			travel->FirstChild = NULL;
			travel->SecondChild = NULL;
			ValIndex += 1;
		}

		else if (val == travel->SecondChild ->Storedvalue)
		{
			childleft = travel->FirstChild;
			childleft->parent = NULL;
			delete travel->SecondChild;
			travel->FirstChild = NULL;
			travel->SecondChild = NULL;
			ValIndex += 2;
		}

		if(sibling->ThirdChild != NULL) // sibling has three children, split is required after merge
		{
			deleteSibThree(childleft, travel, travelparent, sibling); // calling this method when sibling has three children
			return ValIndex;
		} // end of sibling has three children

		else if(sibling->ThirdChild == NULL) // sibling only has two children
		{

			if(travelparent->ThirdChild != NULL)// if travelparent has three child, merge is not required after the deletion of travel
			{
				deleteTravPThree(childleft, travel, travelparent, sibling);
				return ValIndex;
			}// end of if travelparent has three children

			else if(travelparent->ThirdChild == NULL)// travel parent has two children, merge is required after the deletion of travel
			{

				if(travel == travelparent->FirstChild)
				{
					sibling->ThirdChild = sibling->SecondChild; // rearranging the children of sibling, and updates its attributes
					sibling->MaxVal = sibling->ThirdChild->MaxVal;
					sibling->TNum = sibling->ThirdChild->MaxNum;
					sibling->SecondChild = sibling->FirstChild;
					sibling->M = sibling->SecondChild->MaxVal;
					sibling->SNum = sibling->SecondChild->MaxNum;
					sibling->FirstChild = childleft; // merge the childleft into sibling
					childleft->parent = sibling;
					sibling->L = childleft->MaxVal; // updates the attribute again
					sibling->FNum = sibling->FirstChild->MaxNum;
					sibling->MaxNum = (sibling->FNum + sibling->SNum + sibling->TNum);
					delete travel; 
					travelparent->FirstChild = NULL;
					childleft = sibling; // re-pointing the pointers for the next merge operation, if required
					travel = travelparent;
					travelparent= travelparent->parent;
				}

				else if(travel == travelparent->SecondChild)
				{
					sibling->ThirdChild = childleft;
					sibling->MaxVal = childleft->MaxVal;
					childleft->parent = sibling;
					sibling->TNum = sibling->ThirdChild->MaxNum;
					sibling->MaxNum = (sibling->FNum + sibling->SNum + sibling->TNum);
					delete travel;
					travelparent->SecondChild = NULL;
					childleft = sibling;
					travel = travelparent;
					travelparent = travelparent->parent;
				}

				while(ChildNum(travel) != 2 && travel != root) // while loop for merge operation, terminate if merge is not required
				{											   // or travel is pointing to the root
															   // the pattern of this while loop is similar to opeartion above
					sibling = findsibling(travel);
					if(sibling->ThirdChild != NULL) // sibling has three children, split is required after merge,
					{
						deleteSibThree(childleft, travel, travelparent, sibling);
						return ValIndex;
					}

					else if(sibling->ThirdChild == NULL) // sibling only has two children
					{
						if(travelparent->ThirdChild != NULL)// if travelparent has three child, merge is not required after the deletion of travel
						{
							deleteTravPThree(childleft, travel, travelparent, sibling);
							return ValIndex;
						}// end of if travelparent has three children

						else if(travelparent->ThirdChild == NULL)// travel parent has two children, merge is required
						{
							if(travel == travelparent->FirstChild)
							{
								sibling->ThirdChild = sibling->SecondChild; // re-arranging the children of sibling, and update attributes
								sibling->MaxVal = sibling->ThirdChild->MaxVal;
								sibling->TNum = sibling->ThirdChild->MaxNum;
								sibling->SecondChild = sibling->FirstChild;
								sibling->M = sibling->SecondChild->MaxVal;
								sibling->SNum = sibling->SecondChild->MaxNum;
								sibling->FirstChild = childleft;
								childleft->parent = sibling; // merge the subtree into sibling
								sibling->L = childleft->MaxVal;
								sibling->FNum = sibling->FirstChild->MaxNum;
								sibling->MaxNum = (sibling->FNum + sibling->SNum + sibling->TNum);
								delete travel;
								travelparent->FirstChild = NULL;
								childleft = sibling; // re-pointing each pointers for next merge operation, if required
								travel = travelparent;
								travelparent= travelparent->parent;
							}
							else if(travel == travelparent->SecondChild)
							{
								sibling->ThirdChild = childleft;
								sibling->MaxVal = childleft->MaxVal;
								childleft->parent = sibling;
								sibling->TNum = sibling->ThirdChild->MaxNum;
								sibling->MaxNum = (sibling->FNum + sibling->SNum + sibling->TNum);
								delete travel;
								travelparent->SecondChild = NULL;
								childleft = sibling;
								travel = travelparent;
								travelparent = travelparent->parent;
							}
						}
					}
				}//end of while loop


				//out of the while loop, travel is pointing to root and root has only one child
				if(travel == root)
				{
					if(travel->FirstChild == NULL)
					{
						travel = travel->SecondChild;
						delete root;
						root = travel;
						root->parent = NULL;
					}

					else if(travel->SecondChild == NULL)
					{
						travel = travel->FirstChild;
						delete root;
						root = travel;
						root->parent = NULL;
					}
				}
			}
		}
	}
	return ValIndex;
}


//deleteSibThree
// if the sibling has three children, instead of spliting it after merging, the method
// will take one of silbing's child and insert it into a new parent along with cleft (childleft)

// PARAM: cleft = child that is being left after deleteion, trav = the parent of childleft

//        travP = the parent of trav, Sib = the sibling of trav

// PRE: 

// POST: The structure of the tree is re-organized and consistent to 2-3 tree strucutre
void TwoThreeTree:: deleteSibThree(Node* cleft, Node* trav, Node* travP, Node* Sib)
{
	Node* newNode;
	if(trav == travP->FirstChild) // insert sibling's child and childleft into a new node
	{							  // and use the new node to replace travel
		newNode = new Node(cleft,Sib->FirstChild);
		newNode->parent = travP;
		travP ->FirstChild = newNode; // insert the new node into the parent of sibling/travel, 
		travP->L = newNode->MaxVal;   // re-arranging the poistion and updating the attributes of travP
		travP->FNum = newNode->MaxNum;
		Sib->FirstChild = Sib->SecondChild; // re-arranging the children of sibling and update its attributes
		Sib->SecondChild = Sib->ThirdChild;
		Sib->ThirdChild = NULL;
		Sib->L = Sib->FirstChild ->MaxVal;
		Sib->M = Sib->SecondChild->MaxVal;
		Sib->MaxVal = Sib->M;
		Sib->FNum = Sib->FirstChild->MaxNum;
		Sib->SNum = Sib->SecondChild->MaxNum;
		Sib->TNum = 0;
		Sib->MaxNum = (Sib->FNum + Sib->SNum);
		delete trav;
	}

	else if(trav == travP->SecondChild)
	{
		newNode = new Node(Sib->ThirdChild,cleft);
		newNode->parent = travP;
		travP ->SecondChild = newNode;
		travP->M = newNode->MaxVal;
		travP->SNum = newNode->MaxNum;
		Sib->ThirdChild = NULL;
		Sib->MaxVal = Sib->M;
		Sib->TNum = 0;
		Sib->MaxNum = (Sib->FNum + Sib->SNum);
		delete trav;
	}

	else if(trav == travP->ThirdChild)
	{
		newNode = new Node(Sib->ThirdChild,cleft);
		newNode->parent = travP;
		travP ->ThirdChild = newNode;
		travP->MaxVal = newNode->MaxVal;
		travP->TNum = newNode->MaxNum;
		Sib->ThirdChild = NULL;
		Sib->MaxVal = Sib->M;
		Sib->TNum = 0;
		Sib->MaxNum = (Sib->FNum + Sib->SNum);
		delete trav;
	}

	updatetree(Sib); // update the 2-3 tree on the way to root

}


//deleteTravPThree
// This method is called if the parent of sibling/travel has three Children then merge is not required
// it is used for re-arranging the structure of the interior nodes and updating attributes

// PARAM: cleft = child that is being left after deleteion, trav = the parent of childleft

//        travP = the parent of trav, Sib = the sibling of trav    

// PRE: 

// POST: The structure of the tree is re-organized and consistent to 2-3 tree strucutre
void TwoThreeTree:: deleteTravPThree(Node* cleft, Node* trav, Node* travP, Node* Sib)
{
	if(trav == travP->FirstChild)
	{
		Sib->ThirdChild =Sib->SecondChild; // re-arranging the Children of sibling, and update its attributes
		Sib->MaxVal = Sib->ThirdChild->MaxVal;
		Sib->SecondChild = Sib->FirstChild;
		Sib->M = Sib->SecondChild->MaxVal;
		Sib->FirstChild = cleft;
		cleft->parent = Sib;
		Sib->L = cleft->MaxVal;
		Sib->FNum = Sib->FirstChild->MaxNum;
		Sib->SNum = Sib->SecondChild->MaxNum;
		Sib->TNum = Sib->ThirdChild->MaxNum;
		Sib->MaxNum = (Sib->FNum + Sib->SNum + Sib->TNum);
		travP->FirstChild = travP->SecondChild; // re-arranging the Children of sibling's parent, and update its attributes
		travP->L = travP->FirstChild->MaxVal;
		travP->FNum = travP->FirstChild->MaxNum;
		travP->SecondChild = travP->ThirdChild;
		travP->SNum = travP->SecondChild->MaxNum;
		travP->ThirdChild = NULL;
		travP->TNum = 0;
		travP->MaxNum = (travP->FNum + travP->SNum);
		travP->MaxVal = travP->M = travP->SecondChild->MaxVal;
		delete trav;
	}

	else if(trav == travP->SecondChild)
	{
		Sib->ThirdChild = cleft;
		cleft->parent = Sib;
		Sib->MaxVal = cleft->MaxVal;
		Sib->TNum = Sib->ThirdChild->MaxNum;
		Sib->MaxNum = (Sib->FNum + Sib->SNum + Sib->TNum);
		travP->FNum = travP->FirstChild->MaxNum;
		travP->L = travP->FirstChild->MaxVal;
		travP->SecondChild = travP->ThirdChild;
		travP->SNum = travP->SecondChild->MaxNum;
		travP->ThirdChild = NULL;
		travP->TNum =0;
		travP->MaxNum = (travP->FNum + travP->SNum);
		travP->MaxVal = travP->M = travP->SecondChild->MaxVal;
		delete trav;
	}

	else if(trav == travP->ThirdChild)
	{
		Sib->ThirdChild = cleft;
		cleft->parent = Sib;
		Sib->MaxVal = cleft->MaxVal;
		Sib->TNum = Sib->ThirdChild->MaxNum;
		Sib->MaxNum = (Sib->FNum + Sib->SNum + Sib->TNum);
		travP->ThirdChild = NULL;
		travP->TNum =0;
		travP->SNum = travP->SecondChild->MaxNum;
		travP->MaxNum = (travP->FNum + travP->SNum);
		travP->M = travP->SecondChild->MaxVal;
		travP->MaxVal = travP->M;
		delete trav;
	}

	updatetree(travP); // update the tree along the path from travP to root
}

//ChildNum
// helper method for counting the number of children stored in nd

// PARAM: nd = an interior node or a leaf node

//  

// PRE: 

// POST: returns the number of children
int TwoThreeTree:: ChildNum(Node* nd)
{
	int CNum = 0;

	if(nd->FirstChild != NULL)
	{
		CNum += 1;
	}

	if(nd->SecondChild != NULL)
	{
		CNum += 1;
	}

	if(nd->ThirdChild != NULL)
	{
		CNum += 1;
	}

	return CNum;
}


//findsibling
// 

// PARAM: nd = an interior node

//            

// PRE: 

// POST: returns the sibling of nd
Node* TwoThreeTree:: findsibling(Node* nd)
{
	Node* temp;

	if(nd == nd->parent->FirstChild)
	{
		temp = nd->parent->SecondChild;
	}

	else if(nd == nd->parent->SecondChild)
	{
		temp = nd->parent->FirstChild;
	}

	else if(nd == nd->parent->ThirdChild)
	{
		temp = nd->parent->SecondChild;
	}

	return temp;
}


//updatetree
// 

// PARAM: nd = an interior node

//            

// PRE: 

// POST: update the 2-3 tree along the path from nd up to root
void TwoThreeTree:: updatetree(Node* nd)
{
	while(nd->parent != NULL)
	{
		if(nd == nd->parent->FirstChild)
		{
			nd->parent->L = nd->MaxVal;
			nd->parent->FNum = nd->MaxNum;
			nd->parent->MaxNum = nd->parent->FNum + nd->parent->SNum + nd->parent->TNum;
			nd = nd->parent;
		}
		else if(nd == nd->parent->SecondChild)
		{
			if(nd->parent->ThirdChild == NULL)
			{
				nd->parent->MaxVal = nd->MaxVal;
			}
			nd->parent->M = nd->MaxVal;
			nd->parent->SNum = nd->MaxNum;
			nd->parent->MaxNum = nd->parent->FNum + nd->parent->SNum + nd->parent->TNum;
			nd = nd->parent;
		}
		else if(nd == nd->parent->ThirdChild)
		{
			nd->parent->MaxVal = nd->MaxVal;
			nd->parent->TNum = nd->MaxNum;
			nd->parent->MaxNum = nd->parent->FNum + nd->parent->SNum + nd->parent->TNum;
			nd = nd->parent;
		}
	} // end of  update

}

//inTwoChild
// 

// PARAM: nd = an interior node , InsAt = the variable used to record the rank of c

//        c = an interior node or leaf node, p = interior node which c will be inserted into

// PRE: 

// POST: c is inserted into p, rank of c is returned
int TwoThreeTree:: inTwoChild(Node* p, Node* c, int InsAt)
{
	
	if(c->MaxVal <= p->L)
	{
		p->ThirdChild = p->SecondChild; // re-arranging children's position
		p->SecondChild = p->FirstChild;
		p->FirstChild = c; // insert c into p
		c->parent = p;
		p->L = p->FirstChild->MaxVal; // updating attributes
		p->M = p->SecondChild->MaxVal;
		p->MaxVal = p->ThirdChild->MaxVal;
		p->FNum = p->FirstChild->MaxNum;
		p->SNum = p->SecondChild->MaxNum;
		p->TNum = p->ThirdChild->MaxNum;
		p->MaxNum = p->FNum + p->SNum + p->TNum;
		InsAt += 1;
	}
	else if(c->MaxVal> p->L && c->MaxVal <= p->M )
	{
		cout<<"in the right if statement"<<endl;
		p->ThirdChild = p->SecondChild;
		p->SecondChild = c;
		c->parent = p;
		p->L = p->FirstChild->MaxVal;
		p->M = p->SecondChild->MaxVal;
		p->MaxVal = p->ThirdChild->MaxVal;
		p->FNum = p->FirstChild->MaxNum;
		p->SNum = p->SecondChild->MaxNum;
		p->TNum = p->ThirdChild->MaxNum;
		p->MaxNum = p->FNum + p->SNum + p->TNum;
		InsAt += 2;	
	}
	else if(c->MaxVal > p->M )
	{
		p->ThirdChild = c;
		c->parent = p;
		p->L = p->FirstChild->MaxVal;
		p->M = p->SecondChild->MaxVal;
		p->MaxVal = p->ThirdChild->MaxVal;
		p->FNum = p->FirstChild->MaxNum;
		p->SNum = p->SecondChild->MaxNum;
		p->TNum = p->ThirdChild->MaxNum;
		p->MaxNum = p->FNum + p->SNum + p->TNum;
		InsAt += 3;
	}

	//begin to update ancestor

	updatetree(p);
	return InsAt;
}

bool TwoThreeTree::isLeafNode(Node* nd)
{
	if(nd->FirstChild == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Node:: Node(int val) // constructor for creating leaf node , attributes for interior node is set to 0
{
	Storedvalue = val;
	L = 0;
	M = 0;
	MaxVal = val;
	FNum = 0;
	SNum = 0;
	TNum = 0;
	MaxNum = 1;
	parent = FirstChild = SecondChild = ThirdChild = NULL;


}

Node::Node(Node* FC, Node* SC) // constructor for creating interior node
{
	Storedvalue = -1;
	L = FC->MaxVal;
	M = SC->MaxVal;
	MaxVal = SC->MaxVal;
	FNum = FC->MaxNum;
	SNum = SC->MaxNum;
	TNum = 0;
	MaxNum = FNum + SNum + TNum;
	FirstChild = FC;
	SecondChild = SC;
	FC->parent = this;
	SC->parent = this;
	ThirdChild = NULL;
	parent = NULL;
}
