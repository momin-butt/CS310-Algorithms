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
#include <bits/stdc++.h>
#include <cmath>
#include <vector>
using namespace std;

/*

Recurrence Relation: 2T(n/2) + c
Time Complexity: O(n)

*/

struct sumVectors{

    vector<int> leftS;
    vector<int> rightS;
    int ll;
    int rr;
};

struct Leaf 
{ 
    int data; 
    Leaf *left, *right, *parent_node;
    int ancestors_sum; 
    int isExplored;
    Leaf()
    {
        left,right,parent_node = NULL;
        ancestors_sum = 0;
    }

}; 
  

Leaf* makeLeaf(int data) 
{ 
    Leaf* leaf = (Leaf*)malloc(sizeof(Leaf)); 
    leaf->data = data; 
    return leaf; 
} 
  

Leaf* insertLevelOrder(int arr[], Leaf* rootnode, int indexer, int totalnodes) 
{ 
    // Base case for recursion 
    if (indexer < totalnodes) 
    { 
        Leaf* temp = makeLeaf(arr[indexer]); 
        rootnode = temp; 

        int leftind = 2 * indexer + 1;
        int rightind = 2 * indexer + 2;
  
        
        rootnode->left = insertLevelOrder(arr, rootnode->left, leftind , totalnodes);
        if(rootnode -> left != NULL)
        {
            rootnode -> left -> parent_node = rootnode;
        } 
  
        rootnode->right = insertLevelOrder(arr, rootnode->right, rightind, totalnodes);
        if(rootnode -> right != NULL)
        {
            rootnode -> right -> parent_node = rootnode;
        }  
    } 
    return rootnode; 
} 

Leaf* findAncestrySum(Leaf* p, vector<Leaf*>& leaf_nodes)
{
    if(p != NULL)
    {
        if(p -> left == NULL && p -> right == NULL)
        {
            leaf_nodes.push_back(p);
        }

        if(p -> parent_node == NULL)
        {
            p -> ancestors_sum = p -> data;
        }

        else
        {
            
            p -> ancestors_sum = p -> parent_node -> ancestors_sum + p -> data;
        }

        p -> left = findAncestrySum(p -> left,leaf_nodes);
        p -> right = findAncestrySum(p -> right,leaf_nodes);

        return p;
    }
    else
    {
        return NULL;
    }

    
}

bool ancestryComparison(int n1, int n2, int n3, int n4, int n5, int n6)
{
    if(n1 >= n2)
    {
        if(n1 >= n3)
        {
            if(n1 >= n4)
            {
                if(n1 >= n5)
                {
                    if(n1 >= n6)
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}


int main(int argc, char** argv)
{
	// string ans="";
	// if (argv[1][4]=='1'){
	// 	ans+="No";
	// }
	// else if (argv[1][4]=='2'){
	// 	ans +="Yes\n1\n1\n0";
	// }
	// cout<<ans<<endl;

    string line;
    int height = 0;
    int int_nodes,nodes,leaves = 0;

    sumVectors vecs;

    ifstream myFile;
    myFile.open(argv[1]);

    if(!myFile)
    {
        cout << "Error! Unable to open the file. \n";
        return 0;
    }

    getline(myFile,line);

    stringstream s0(line);

    string temp0;
    s0 >> temp0;
    s0 >> height;

    leaves = pow(2,height);
    int_nodes = leaves-1;

    nodes = int_nodes+leaves;

    getline(myFile,line);

    int array[nodes];
    int len = line.length();

    stringstream s1(line);

    for(int i = 0; i < nodes; i++)
    {
    	int val = 0;
    	s1 >> val;
    	array[i] = val;
    }

    Leaf* rootnode = insertLevelOrder(array, rootnode, 0, nodes);

    vector<Leaf*> leaf_nodes;

    findAncestrySum(rootnode,leaf_nodes);

    int vec_size = leaf_nodes.size();

    int leftarray_indexer = 0;
    int rightarray_indexer = 0;
    
    bool yes = false;
    int counter = 0;

    for(int i = 0; i < vec_size; i++)
    {
        if(leaf_nodes[leftarray_indexer] -> ancestors_sum < leaf_nodes[i]->ancestors_sum)
        {
            leftarray_indexer = i;
            yes = true;
            counter++;
        }

        yes = false;
    }


    for(int i=0; i<vec_size; i++)
    {

        if(leaf_nodes[rightarray_indexer] -> ancestors_sum < leaf_nodes[i]->ancestors_sum)
        {
            if(i != leftarray_indexer)
            {
                rightarray_indexer = i;
                yes = true;
                counter--;
            }    
        }

        yes = false;
    }

    Leaf* leftLeaf = leaf_nodes[leftarray_indexer];
    Leaf* rightLeaf = leaf_nodes[rightarray_indexer];

    int union_nodes = 0;

    while(leftLeaf != NULL)
    {
        union_nodes += leftLeaf -> data;
        leftLeaf -> isExplored = 1;
        vecs.leftS.push_back(leftLeaf -> data);
        leftLeaf = leftLeaf -> parent_node;
    }
    while(rightLeaf != NULL)
    {
        if(rightLeaf -> isExplored == 0)
        {
            union_nodes += rightLeaf -> data;
            rightLeaf -> isExplored = 1;
        }

        vecs.rightS.push_back(rightLeaf -> data);
        rightLeaf = rightLeaf -> parent_node;

    }

    string ancestors_string1,ancestors_string2;
    int iter = 0;

    while(iter < height+1)
    {
        if(iter != height+1)
        {
            ancestors_string1 = ancestors_string1 + to_string(vecs.leftS[iter]);
            ancestors_string1 = ancestors_string1 + ", ";
            ancestors_string2 = ancestors_string2 + to_string(vecs.rightS[iter]);
            ancestors_string2 = ancestors_string2 + ", ";
        }
        else
        {
            ancestors_string1 = ancestors_string1 + to_string(vecs.leftS[iter]);
            ancestors_string2 = ancestors_string2 + to_string(vecs.rightS[iter]);
        }

        iter++;
    }


    string anc_string = "Ancestry";
    string maxanc = "Value of Max Ancestry";
    string one = "(xi,xj) = ";
    string bracstr = " = {";

    string result = one;
    result = result + "(x" + to_string(rightarray_indexer+1) + "," + "x" + to_string(leftarray_indexer+1) + ")\n";
    result = result + anc_string  + " x" + to_string(rightarray_indexer+1) + bracstr + ancestors_string2 + "}\n";
    result = result + anc_string  + " x" + to_string(leftarray_indexer+1) + bracstr + ancestors_string1 + "}\n";
    result = result + maxanc + " (x" + to_string(rightarray_indexer+1) + "," + "x" + to_string(leftarray_indexer+1) + ") = " + to_string(union_nodes) + "\n";

    cout << result;

	return 0;
}  
  