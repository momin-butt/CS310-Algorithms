#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <stack>
#include <vector>
#include <stdlib.h>
#include <stack>
#include <string>
#include <queue>
#include <sstream>
#include <set>

using namespace std;

/* 

Time Complexity: O(n)
Recurrence Relation: if m = 0 then return 0
					 else mininumlights = mininumlights + switchOnorOff

*/

int char_to_int(int c){

	return c - '0';
}

struct Light
{
	int minimum_numLights;
	int childrenLights;
	int childNum;
	vector<int> checkLights;
	bool *explored;

	Light()
	{
		minimum_numLights = 0;
		childrenLights = 0;
		childNum = 0;

		for(int i = 0; i++;)
        {
       		explored[i] = false;
        }

	}
};

struct Vertex
{
	int vertex;
	bool isLight;
	struct Vertex *Vertex_next;
	struct Vertex* Vertex_dest;
};

struct Vertexes
{
	int child_vertexes;
	struct Vertex* head;
	struct Vertex* tail;
	bool isLight;

	Vertexes()
	{
		isLight = false;
		child_vertexes = 0;
	}
};

class Graph
{
	public:
			int vertice_num;
			struct Vertexes *vertex_array;

			Graph(int x)
			{
				vertice_num = x;
				vertex_array = new Vertexes[vertice_num];
				vector<Vertex*> edges;
			}


			void addEdge(int start, int end)
			{
				vertice_num++;

				Vertex* temp = new Vertex;
				temp->isLight = 0;

				vertex_array[start].child_vertexes++;

				temp->vertex = end;
				temp->Vertex_next = vertex_array[start].head;
				vertex_array[start].head = temp;
			}

			void showGraph()
	        {
	            int n;
	            for (n = 0; n < vertice_num; n++)
	            {
	                Vertex* parseFile = vertex_array[n].head;
	                cout << n;

	                while (parseFile)
	                {
	                    cout << "->" << parseFile->Vertex_dest;
	                    parseFile = parseFile->Vertex_next;
	                }
	                cout<<endl;
	            }

	        }

};


int switchOnorOff(Light lighted, Graph const &graph, int parent_Vertex, int* memo_array) 
{
	Vertex *temp_Vertex = graph.vertex_array[parent_Vertex].head;
	int child_turn = graph.vertex_array[parent_Vertex].child_vertexes;

	lighted.childNum = 0;
    lighted.minimum_numLights = 0;
    lighted.childrenLights = 0;

    lighted.explored[parent_Vertex] = true;

    Vertex* traverse_vertex = graph.vertex_array[parent_Vertex].head; 

	while(traverse_vertex!= NULL)
    {
        if(lighted.explored[traverse_vertex->vertex] == false)
        {
            lighted.childNum = lighted.childNum+1;   	
        }

        traverse_vertex = traverse_vertex->Vertex_next;
    }

    bool yes = false;

	for(int i = 0; i < child_turn ; i++)
	{
		int child = temp_Vertex->vertex;
        if(lighted.explored[child] == false)
        {

            lighted.minimum_numLights = lighted.minimum_numLights + switchOnorOff(lighted,graph,child,memo_array);
            (graph.vertex_array[child].isLight == true) ? lighted.childrenLights++ : yes = true;
        }

		temp_Vertex = temp_Vertex->Vertex_next;
	}

	bool less_than = lighted.childrenLights < lighted.childNum;

	if(less_than)
	{
		graph.vertex_array[parent_Vertex].isLight = true;
		lighted.minimum_numLights = lighted.minimum_numLights+1;
	}

	return lighted.minimum_numLights;
}

int main(int argc, char** argv)
{
	char *filename = argv[1];

	string row;
	int vertices;
	int* memo_array;

	ifstream myFile;
	myFile.open(filename);


	if(!myFile)
	{
		cout << "Error! Unable to open the file. \n";
		return 0;
	}

	getline(myFile, row);

	for(int l = 0; l < row.length(); l++)
	{
		if(row[l] == 'n')
		{
			vertices = stoi(row.substr(l+1, row.length()-l+1));
			break;
		}
	}

	memo_array = new int[vertices];
	for(int i=0; i<vertices; i++)
	{
		memo_array[i] = -1;
	}

	Graph graph(vertices);

	string temp;
	int index = 0;

	while (!myFile.eof())
	{
		getline(myFile, row);
		stringstream s1(row);

		s1 >> temp >> temp;

		while(s1 >> temp)
		{
			graph.addEdge(index,stoi(temp));

		}

		index++;
	}

	Light lighted2;

    lighted2.explored = new bool[vertices];

	string ans0 = "\n{";
	string ans1 = "Minimum Lights ";
	string ans2 = ", ";
	string ans3 = "}\n";

	bool on = true;
	int lightResult = switchOnorOff(lighted2,graph,0,memo_array);

	ans1 = ans1 + to_string(lightResult) + ans0;

	for(int i = 0; i < vertices; i++)
    {
        if(graph.vertex_array[i].isLight == on)
        {
           lighted2.checkLights.push_back(i);
        }
        else
        	continue;
    }

    int vecsize = lighted2.checkLights.size();
    string result = ans1;

    for(int i = 0; i < vecsize; i++)
    {
        (i != vecsize-1) ? result = result + to_string(lighted2.checkLights[i]) + ans2 : result = result + to_string(lighted2.checkLights[i]) + ans3;
    }
    
    delete [] memo_array;
    delete [] lighted2.explored;
    
    cout << result;

}