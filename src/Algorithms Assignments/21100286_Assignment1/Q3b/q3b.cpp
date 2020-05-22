#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <stack>
#include <vector>
#include <stdlib.h>
#include "graph.cpp"
#include <stack>
#include <string>

using namespace std;

// ----------------------------------- ALGORITHM DESCRIPTION ----------------------------------------
// I am traversing each node in my graph to output a topological sorting in the form of rows. 
// At first, I check if my graph is a DAG or not. If it is, I print out its topological ordering using
// the indegree method. 
// In my algorithm, I am using a vector of vectors that stores the information about the decrementing
// indegrees and a queue that stores all the vertices that are coming afresh from the visited array.

// Total complexity: O(V+E)
// Space complexity of adjacency list: O(V+E) 


void traverseDFS(Graph const &graph, int vertices, queue<int> &myqueue, vector<vector<int>> &sort, vector <int> &numbered_row, int &token)
{
	while(true)
	{
		if(myqueue.empty())
		{
			break;
		}
		for(int iter2 = 0; iter2 < myqueue.size(); iter2++)
		{
			
			int start_vertex = myqueue.front();
			numbered_row.push_back(start_vertex);
			Vertex *headNode = graph.list[start_vertex].head;

			myqueue.pop();			

			while(true)
			{
				if(!headNode)
				{
					break;
				}

				graph.incoming_edge[headNode->dest] = graph.incoming_edge[headNode->dest]-1;

				if(!graph.incoming_edge[headNode->dest])
				{
					myqueue.push(headNode->dest);
				}

				headNode= headNode->next;
			}

			token++;

		}

		sort.push_back(numbered_row);
		numbered_row.clear();

	}
}

int main(int argc, char** argv) 
{ 
	char* filename = argv[1];

	string row;
	int vertices;

	ifstream myFile;
	myFile.open(filename);

	if(!myFile)
	{
		cout << "Error! Unable to open the file. \n";
		return 0;
	}

	getline(myFile,row);

	for(int l = 0; l < row.length(); l++)
	{
		if(row[l] == 'n')
		{
			vertices = stoi(row.substr(l+1, row.length()-l+1));
			break;
		}
	}

	Graph graph(vertices);

	for(int i = 0; i < vertices; i++)
	{
		getline(myFile,row);
		int iter1,iter2;

		for(iter1 = 0; iter1 < row.length(); iter1++)
		{
			if(row[iter1] == ':')
			{
				break;
			}

			else if(row[iter1] == ' ')
			{
				continue;
			}
		}

		for(iter2 = iter1+1; iter2 < row.length(); iter2++)
		{
			if(isdigit(row[iter2]))
			{
				int end_pos = char_to_int(row[iter2]);
				graph.addEdge(i,end_pos);
			}
		}
	}

	
	queue<int> myqueue;

	vector <int> numbered_row;	
	vector<vector<int>> sort;

	for(int iter1 = 0; iter1 < vertices; iter1++)
	{
		if(!graph.incoming_edge[iter1])
		{
			
			myqueue.push(iter1);
		}
	}	

	int token = 0;
	traverseDFS(graph, vertices, myqueue, sort, numbered_row, token);

	
	if(token == vertices)
	{
		
		int r = sort.size();
		string myanswer;

		myanswer = "Yes\nR " + to_string(r) + "\n"; 


		for(int i=0; i<r; i++)
		{
			int a = sort[i].size();

			for(int j=0; j<a; j++)
			{
				if(j<a)
				{
					myanswer = myanswer + to_string(sort[i][j]) + " ";
				}
				else
				{
					myanswer = myanswer + to_string(sort[i][j]);
				}
				
			}
			myanswer = myanswer + "\n";
		}

		cout<<myanswer;
	}
	else if(token!=vertices)
	{
		string x = "No\n";
		cout << x;
	}

	return 0;

}