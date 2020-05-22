#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <stack>
#include <vector>
#include <stdlib.h>
#include <stack>
#include <string>
#include <sstream> 
#include<iterator>
#include <algorithm>
// #include<list> 

using namespace std;

vector<int> msttree1;
vector<int> msttree2;

void DFS(int v, vector<vector<int>> vertices, bool visited[], int ctr) 
{ 
    visited[v] = true; 
    if(ctr == 1)
    {
    	msttree1.push_back(v);
    }
    else if(ctr == 2)
    {
    	msttree2.push_back(v);
    }

	for (int u : vertices[v])
	{
		if (!visited[u])
			DFS(u, vertices, visited, ctr);
	}
} 

int find(int *parent, int i)  
{    
	if (parent[i] != i)  
		parent[i] = find(parent, parent[i]);  

	return parent[i];  
}  

void Union(int *parent, int *rank, int x, int y)  
{  
	int xroot = find(parent, x);  
	int yroot = find(parent, y);  

	if (rank[xroot] < rank[yroot])  
		parent[xroot] = yroot;  
	else if (rank[xroot] > rank[yroot])  
		parent[yroot] = xroot;  

	else
	{  
		parent[yroot] = xroot;  
		rank[xroot]++;  
	}  
}

struct edge 
{
	pair<int, int> src_dst;
	int weight;

	bool operator<(const struct edge &a) const
	{
		return weight < a.weight;
	}
	bool operator<=(const struct edge &a) const
	{
		return weight <= a.weight;
	}
	bool operator>(const struct edge &a) const
	{
		return weight > a.weight;
	}
	bool operator>=(const struct edge &a) const
	{
		return weight >= a.weight;
	}
};

class graph
{
	vector<edge> edges;
	vector<vector <int> > vertices;
	int n;
	

	void initialize_vertices(int n)
	{
		vector<int> fill_spaces;

		for(int i = 0; i < n; i++)
			vertices.push_back(fill_spaces);
	}
public:
	graph()
	{

	}
	pair<int, int> remove_edge;
	graph(char* filename)
	{
		char temp;
		string line;
		ifstream fin(filename);

		fin >> temp >> n;
		// cout<<n;

		initialize_vertices(n);

		int src, dst, weight;

		for(int i = 0; i < n+1; i++)
		{
			getline(fin, line);

			stringstream ss(line);

			ss >> src >> temp;

			while(!ss.eof())
			{
				ss >> dst >> temp >> weight;
				addEdge(src, dst, weight);
			}
		}

		getline(fin, line);
		// cout<<line;
		stringstream ss(line);
		ss >> temp >> remove_edge.first >> temp >> remove_edge.second >> temp;
	}

	graph get_mst()
	{
		graph g;
		g.initialize_vertices(n);

		vector<struct edge> sorted_edges;
		sorted_edges.swap(edges);

		sort(sorted_edges.begin(), sorted_edges.end());

		int *parent, *rank;

		for(int i = 0; i < n; i++)
		{
			parent[i] = i;
			rank[i] = 0;
		}

		for(int i = 0; i < sorted_edges.size(); i++)
		{
			int src = sorted_edges[i].src_dst.first;
			int dst = sorted_edges[i].src_dst.second;

			int parent_src = find(parent, src);
			int dest_src = find(parent, dst);

			if(parent_src == dest_src)
				continue;

			g.addEdge(src, dst, sorted_edges[i].weight);

			Union(parent, rank, src, dst);

			g.vertices[dst].push_back(src);
		}

		return g;
	}
	void addEdge(int src, int dst, int weight)
	{
		pair<int, int> this_pair;
		this_pair.first = src;
		this_pair.second = dst;

		edge this_edge;

		this_edge.src_dst = this_pair;
		this_edge.weight = weight;

		edges.push_back(this_edge);
		vertices[src].push_back(dst);
	}

	vector<vector<int> > get_vertices()
	{
		return vertices;
	}

};

int main(int argc, char** argv) 
{ 
	char* filename = argv[1];

	string line;
	// int vertices;

	ifstream myFile;
	myFile.open(filename);

	if(!myFile)
	{
		cout << "Error! Unable to open the file. \n";
		return 0;
	}

	graph my_graph(filename);

	graph mst_graph = my_graph.get_mst();


	vector<vector<int> > vertices = mst_graph.get_vertices();

	// for(int i = 0; i < vertices.size(); i++)
	// {
	// 	cout << i << ": ";

	// 	for(int j = 0; j < vertices[i].size(); j++)
	// 	{
	// 		cout << vertices[i][j] << " ";
	// 	}

	// 	cout << endl;
	// }
	int i = 0;
	int j = 0;
	int yes = false;
	int size = vertices.size();
	int source = my_graph.remove_edge.first;
	int dest = my_graph.remove_edge.second;
	// cout<<source; 

	// cout<<my_graph.remove_edge.first<<" "<<my_graph.remove_edge.second;
	for(i = 0; i<size; i++)
	{
		// cout<<i<<endl;
		if(i == source)
		{
		// 	cout<<i<<endl;
			int s = vertices[i].size();
			for(int j = 0; j <s ; j++)
			{

				if(vertices[i][j] == my_graph.remove_edge.second)
				{
					// cout<<i<<" "<<vertices[i][j]<<endl;
					yes = true;

					break;
				}

			}

			
		}

		if(yes)
		{
			break;
		}
	}
	vertices[i].erase(vertices[i].begin() + j);

	yes = false;

		for(i = 0; i<size; i++)
	{
		// cout<<i<<endl;
		if(i == dest)
		{
		// 	cout<<i<<endl;
			int s = vertices[i].size();
			for(int j = 0; j <s ; j++)
			{

				if(vertices[i][j] == source)
				{
					// cout<<i<<" "<<vertices[i][j]<<endl;
					yes = true;

					break;
				}

			}

			
		}

		if(yes)
		{
			break;
		}
	}

	vertices[i].erase(vertices[i].begin() + j);

	cout<<endl<<endl;

	// for(int i = 0; i < vertices.size(); i++)
	// {
	// 	cout << i << ": ";

	// 	for(int j = 0; j < vertices[i].size(); j++)
	// 	{
	// 		cout << vertices[i][j] << " ";
	// 	}

	// 	cout << endl;
	// }


	bool *visited = new bool[size]; 
	for (int i = 0; i < size; i++) 
		visited[i] = false; 

	DFS(source,vertices,visited,1);

	for (int i = 0; i < size; i++) 
		visited[i] = false;

	DFS(dest,vertices,visited,2);

	for(int i = 0; i<msttree1.size(); i++)
	{
		cout<<msttree1[i]<<"  ";
	}

	cout<<"\n";

	for(int i = 0; i<msttree2.size(); i++)
	{
		cout<<msttree2[i]<<"  ";
	}





	

	return 0; 
}


