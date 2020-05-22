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

// I use the Depth First Search (DFS) traversal to visit every node in the graph. As we visit every node,
// we assign two values to each node: discovery_link and low_link. Discovery link is the ordering number
// in which we visit each node and initially we will keep both values same. 

// Once all children of a node are visited, we backtrack according to the placement of the vertices in the
// adjacency list. We will update the low_link value of the vertex by comparing this value with the low_link
// values of all its neighbours other than the parent. Once this is done, we compare this low_link value of
// the current vertex with the discovery_link value of its parent. If the latter is smaller then the edge is
// a bridge. I have only used dynamic arrays to store these values and also maintain a parents array.

// Space complexity of adjacency list: O(V+E) 
// Overall time complexity: O(V+E) 


int increment = 0;
int counter = 0;

int find_lowest_link(int x,int y)
{
	if(x < y)
		return x;
	else 
		return y;
}

void DFSvulnerable(Graph const&graph, int vertices, bool explored[], int disc_link[], int low_link[], int daddies[], int start_vertex, string &result)
    {
        	disc_link[start_vertex] = increment+1;
        	low_link[start_vertex] = disc_link[start_vertex];
        
        	explored[start_vertex] = true;

            Vertex *headNode = graph.list[start_vertex].head;

            while(headNode!=NULL)
            {
                int index = headNode->dest;

                if(explored[index] == false)
                {
                    daddies[index] = start_vertex;
                    increment++;

                    DFSvulnerable(graph,vertices,explored,disc_link,low_link,daddies,index,result);

                     low_link[start_vertex] = find_lowest_link(low_link[start_vertex],low_link[index]);	

                    if(low_link[index] > disc_link[start_vertex])
                    {
                    	counter++;         
                    	result = result + "(" + to_string(start_vertex) + "," + to_string(index) + ")" + "\n";            	
        			    
                    }
                    	
                }

                else if(index != daddies[start_vertex])
                {
                	low_link[start_vertex] = find_lowest_link(low_link[start_vertex],disc_link[index]);
                    
                }

                headNode = headNode->next;
            }
                    
    }

int main(int argc, char** argv)
{	
	string filename = argv[1];

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

        bool explored[vertices]; 
        int disc_link[vertices]; 
        int low_link[vertices]; 
        int daddies[vertices]; 
        string result;        

        for (int i = 0; i < vertices; i++)
        {
        	disc_link[i] = 0;
        	low_link[i] = 0;
        	daddies[i] = 0;
        }

        for(int i = 0; i < vertices; i++)
        {
        	explored[i] = false;
        }

        for(int i = 0; i < vertices; i++)
        {
            DFSvulnerable(graph, vertices, explored, disc_link, low_link, daddies, i, result);
        }                 

        if(counter > 0)
        {
        	result = to_string(counter) + "\n" + result;
        	cout<<result;
        }
        else if(counter <= 0)
        {
        	result = to_string(counter) + "\n";
        	cout<<result;
        }
        
	return 0;
}
