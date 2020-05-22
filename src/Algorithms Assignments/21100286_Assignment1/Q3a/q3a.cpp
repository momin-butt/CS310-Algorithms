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

// I use the Depth First Search (DFS) traversal to visit every node in the graph and apply Topological Sort on it. 
// This takes O(V+E) time. Through traversing, I insert these nodes into the stack.

// Once this is done, I implement another function named cycleSort that is used to identify if the respective
// graph is a DAG or not. If it's a DAG, topoSort is implemented. Otherwise, the followed path is outputted.
// DFS is implemented in this function too, thus, it also takes O(V+E) time. 

// Total time complexity: O(V+E) + O(V+E) = O(2V+2E) which is equal to O(V+E).
// Space complexity of adjacency list: O(V+E)

// */

void topoSort(Graph const&graph, int vertices, bool explored[], stack<int> &topsort, int start_vertex)
{
	explored[start_vertex] = true;

	Vertex *headNode = graph.list[start_vertex].head;

	while(headNode != NULL)
	{
		int index = headNode->dest;

		if(!explored[index])
		{ 
			topoSort(graph,vertices, explored,topsort,index);
		}
	
		headNode = headNode->next;
	}

	topsort.push(start_vertex);
}

bool cycleSort(Graph const&graph, int vertices, bool explored[], vector<int> &cycle, int start_vertex)
{
	explored[start_vertex] = true;
	cycle.push_back(start_vertex);

	Vertex *headNode = graph.list[start_vertex].head;

	while(headNode != NULL)
	{
		int index = headNode->dest;

		if(!explored[index])
		{
			if(cycleSort(graph,vertices, explored,cycle,index))
			{
				return true;
			}
		}

		else if(explored[index])
		{
			for(int i = 0; i<vertices; i++)
			{
				if(cycle[i] == index)
				{
					cycle.push_back(index);
					return true;
				}
			}
		}

		headNode = headNode->next;
	}

	cycle.pop_back();
	return false;
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

	//graph.showGraph();

	bool *visited = new bool[vertices];
	vector<int> cycle;

	bool *explored = new bool[vertices];
	stack<int> Stack;

	string res;
	bool notcycle = false;

	for (int i = 0; i < vertices; i++) 
	{
		if(graph.incoming_edge[i] == 0)
		{
			notcycle = true;
		}

		visited[i] = false; 
		explored[i] = false;	
	}

	if(notcycle)
	{
		for(int i = 0; i < vertices; i++)
		{
			if (explored[i] == false)	
			{
				topoSort(graph,vertices, explored, Stack,i);
			}	    	    		
		}

		while(!Stack.empty())
		{
			res = res + to_string(Stack.top()) + " ";
			Stack.pop();

		}

		cout << "Yes\n" + res + "\n";		
	}

	else
	{
		string cycle_str;

		cycle_str = "No\n";

		for(int i = 0; i < vertices; i++)
		{	
			cycleSort(graph,vertices,visited,cycle,i);
		}

		for(int i = 0; i < vertices; i++)
		{
			if(i == vertices-1)
			{
				cycle_str = cycle_str + to_string(cycle[i]);
			}
			else
			{
				cycle_str = cycle_str + to_string(cycle[i]) + "->";
			}		
		}

		cout << cycle_str;
	}

	 return 0; 

} 

