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
    //int low_key;
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

        Graph(int nodes)

        {	

            vertices = nodes;
            list = new AdjList[vertices];

            for (int l = 0; l < vertices; l++)
            {
            	list[l].head = NULL;
            }

        }

        /*

         * Creating New Adjacency List Node

         */ 

        // Vertex* newVertex(int end)

        // {
        //     Vertex* createNode = new Vertex;

        //     createNode->dest = end;
        //     createNode->next = NULL;

        //     return createNode;
        // }

        /*

         * Adding Edge to Graph

         */ 

        void addEdge(int start, int end)

        {
            Vertex* addNode = new Vertex;
            addNode->dest = end;
            addNode->next = list[start].head;
            list[start].head = addNode;

            // addNode = newVertex(start);
            // addNode->next = list[end].head;
            // list[end].head = addNode;
        }

        /*

         * Print the graph

         */ 

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

