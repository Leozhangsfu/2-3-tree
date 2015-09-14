//author: Zi Hao(Leo) Zhang, Student Number: 301209995

#include "TwoThreeTree.h"
#include <stdexcept>
#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <vector>

int main()
{

	TwoThreeTree newtree;
	string test;
	int integerStart = 0;
	int integer = 0;
	string cap = "";
	string operation = ""; //type of operation
	int value = 0; //The value used for the operation
	int temp;

	ifstream inFile ("input.txt");
	ofstream OutFile("9995.txt");

	if(inFile.is_open())
	{
		getline(inFile,test);
	}
	else
	{
		throw runtime_error("The file is not opened");
	}

	for(int i = 0; i<test.length(); i++) // reading the integers on the first line of input.txt
	{
		if(test[i] == ',')
		{
			cap = test.substr(integerStart,i-integerStart);
			integer = stoi(cap);
			integerStart = i + 1;
			newtree.Insert(integer);
		}
	}

	cap = test.substr(integerStart, test.length()-integerStart);
	integer = stoi(cap);
	newtree.Insert(integer);

	while(inFile>> operation >> value) // reading operations and corresponding values
	{
		if (operation == "Insert")
		{
			OutFile<< "inserted at position: "<<newtree.Insert(value)<<endl;
		}

		else if(operation == "Find")
		{
			temp = newtree.Find(value);

			if(temp == 0)
			{
				OutFile<<"Not Found"<<endl;
			}

			else if(temp > 0)
			{
				OutFile<<"Found; "<<value<<" is the "<<temp<<" element of the list"<<endl;
			}
		}

		else if(operation == "Delete")
		{
			temp = newtree.Delete(value);
			OutFile <<value<<" is the "<<temp <<" element of the list, deleted"<<endl;
		}
		else if(operation == "Selection")
		{
			temp = newtree.Selection(value);
			OutFile <<"The "<<value<< "th element in the tree is "<<temp<<endl;
		}
	}


	vector<int> print; // putting every leaf node into a vector and output them to the output file
	newtree.printTree(print);

	OutFile<<endl<<"The leaf nodes of the tree:"<<endl;
	for(int i = 0; i<print.size(); i++)
	{
		OutFile<<print[i]<<" ";
	}
	

	inFile.close();
	OutFile.close();

	
	return 0;
}

