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
