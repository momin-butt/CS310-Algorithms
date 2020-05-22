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

// My algorithm uses the Depth First Search (DFS) traversal to check if the graph 
// is bipartite or not. The time complexity of this algorithm is O(V+E).
// I have used an Adjacency List to store the vertices and edges information. The odd-length cycles are
// found by coloring the vertices into two colors using DFS.

// If the data cannot be divided into two boxes, I use the Depth First Search (DFS)
// traversal to find a cycle of odd length on the problematic node. The time complexity for this is also O(V+E).
// The other data structures that I have used include dynamic arrays, vectors and stacks. Traversing and insertion
// into the stack takes O(V) time.

// Space complexity of adjacency list: O(V+E) 
// Overall time complexity: O(V+E) 

int BiPartiteness(Graph &graph, int vertices, bool explored[], int color_array[], int node_indexer, stack<int> &uneven_cycle)
{
	for(int iter = node_indexer; iter < vertices; iter++)
	{
		Vertex *headNode = graph.list[iter].head;

		do
		{
			int index = headNode->dest;
			
			if (!explored[index])
			{
				uneven_cycle.push(index);

				explored[index] = 1;
				color_array[index] = !color_array[iter];

				while(BiPartiteness(graph,vertices,explored,color_array,index,uneven_cycle) != 1)
				{
					return 0;
				}

				return 1;

			}
			else if(color_array[index] == color_array[iter])
			{
				uneven_cycle.push(index);
			
				return 0;
			}

            headNode = headNode->next;

		} while(headNode != NULL);
	}

	return 1;
}

void printstack(stack<int> s)
  {
    if (s.empty())
    {
      return;
    }

    int last = s.top();
    s.pop();

    string token = to_string(last) + "->"; 

    while(!s.empty())
    {
    	token = token + to_string(s.top());
    	if(last == s.top())
    	{
    		break;
    	}

    	token = token + "->";
    	s.pop();
    }

    cout << token;
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

	vector<int> b1;
	vector<int> b2;

	string res1,res2;

	bool discovered[vertices];
    int colored[vertices];

    discovered[0] = true;
    colored[0] = 0;

    stack<int> uneven_cycle;

    if(BiPartiteness(graph, vertices, discovered, colored, 0, uneven_cycle) == 1)
    {	
		for(int iter = 0; iter < vertices; iter++)
		{

			if(colored[iter] == 1)
			{
				b1.push_back(iter);
			}

			else if(colored[iter] == 0)
			{
				b2.push_back(iter);
			}

		}

		int chems1 = b1.size()-1;
		int chems2 = b2.size()-1;

		
		for (int iter1 = 0; iter1 < b1.size(); iter1++)
		{
			if(iter1 == chems1)
			{
				res1 = res1 + to_string(b1[iter1]);
			}

			else if(iter1 != chems1)
			{
				res1 = res1 + to_string(b1[iter1]) + " ";
			}
		} 
	     
	    for (int iter2 = 0; iter2 < b2.size(); iter2++)
	    {
	    	if(iter2 == chems1)
			{
				res2 = res2 + to_string(b2[iter2]);
			}

			else if(iter2 != chems2)
			{
				res2 = res2 + to_string(b2[iter2]) + " ";
			}
	    } 

	    string results = "Yes\n"+res1+"\n"+res2;
	    cout << results << endl;
    }
    else
    {
    	cout << "No" << endl;
    	printstack(uneven_cycle);
    	cout << endl;
    	
    }

    return 0;
}









