#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <sstream>

using namespace std;

int char_to_int(int c){

	return c - '0';
}

struct Vertex

{
    int dest;
    struct Vertex* next;

};

struct AdjList

{
    struct Vertex *head;

};

class Graph

{
    private:

        int vertices;
        
    public:

    	struct AdjList* list;
        int *incoming_edge;

        Graph(int nodes)

        {	
            incoming_edge = new int[vertices];

            vertices = nodes;
            list = new AdjList[vertices];

            for (int l = 0; l < vertices; l++)
            {
            	list[l].head = NULL;
            }

            for (int y = 0; y < vertices; y++)
            {
                incoming_edge[y] = 0;
            }

        }

        void addEdge(int start, int end)

        {

            incoming_edge[end] += 1; 
            Vertex* addNode = new Vertex;
            addNode->dest = end;
            addNode->next = list[start].head;
            list[start].head = addNode;

        }

        void showGraph()
        {
            int n;
            for (n = 0; n < vertices; n++)
            {
                Vertex* parseFile = list[n].head;
                cout << n;

                while (parseFile)
                {
                    cout << "->" << parseFile->dest;
                    parseFile = parseFile->next;
                }
                cout<<endl;
            }

        }

};


/*                        ALGORITHM DESCRIPTION

I use the Depth First Search (DFS) traversal to visit every node in the graph and apply Topological Sort on it. 
This takes O(V+E) time. Through traversing, I insert these nodes into the stack.

Once this is done, I implement another function named cycleSort that is used to identify if the respective
graph is a DAG or not. If it's a DAG, topoSort is implemented. Otherwise, the followed path is outputted.
DFS is implemented in this function too, thus, it also takes O(V+E) time. 

Total time complexity: O(V+E) + O(V+E) = O(2V+2E) which is equal to O(V+E).
Space complexity of adjacency list: O(V+E)

*/