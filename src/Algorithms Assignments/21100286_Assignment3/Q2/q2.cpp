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
using namespace std;

/*

Recurrence Relation: 2T(n/2) + c
Time Complexity: O(nlogn)

*/

string a;
string b;
 
typedef struct
{
	int val;
	int day;

} entry;

int merge(entry *arr, entry *new_arr, int starting_point, int array_center, int ending_point) 
{ 
    int left_index = starting_point;
    int right_index = array_center;
    int sorted_index = starting_point; 

    int inversions = 0; 
    
    while ((left_index <= array_center-1) && (right_index <= ending_point)) 
    { 

        if (arr[left_index].val <= arr[right_index].val) 
        { 
        	new_arr[sorted_index++] = arr[left_index++];
        }

        else
        {
        	for(int cnt = left_index; cnt <= array_center-1; cnt++)
        	{
        		if(((double)arr[cnt].val/(double)2) > (double)arr[right_index].val)
        		{
                    a = a + "(" + to_string(arr[right_index].day) + "," + to_string(arr[cnt].day) + ")" + "\n";
        			inversions++;                   
        		}

        	}

			new_arr[sorted_index++] = arr[right_index++];
 
        }            
    } 
       

    while (left_index <= array_center - 1) 
    {
        new_arr[sorted_index++] = arr[left_index++]; 
    }
  
    while (right_index <= ending_point) 
    {
        new_arr[sorted_index++] = arr[right_index++]; 
    }
  
    for (left_index = starting_point; left_index <= ending_point; left_index++)
    {
        arr[left_index] = new_arr[left_index];
    }  
  

    return inversions; 
}

int Sort(entry *arr, entry *new_arr, int begin, int end) 
{ 
    int array_center, inversions = 0; 
    if (end > begin) 
    { 
        array_center = (end + begin) / 2; 
  
        inversions = inversions + Sort(arr, new_arr, begin, array_center); 
        inversions = inversions + Sort(arr, new_arr, array_center + 1, end); 

        inversions = inversions + merge(arr, new_arr, begin, array_center + 1, end); 
    } 

    return inversions; 
} 


int mergeSort(entry *arr, int array_size) 
{ 
    entry *new_arr = new entry[array_size]; 
    return Sort(arr, new_arr, 0, array_size - 1); 

	delete[] new_arr;
} 


int main(int argc, char** argv)
{

	char* filename = argv[1];

	string line;
	int size = 0;

	ifstream myFile;
	myFile.open(filename);

	if(!myFile)
	{
		cout << "Error! Unable to open the file. \n";
		return 0;
	}

	getline(myFile,line);

	stringstream s0(line);

	string new_arr0;
	s0 >> new_arr0;
	s0 >> size;

	getline(myFile,line);

	entry *array = new entry[size];

	stringstream s1(line);

	for(int i = 0; i < size; i++)
	{
		int l = 0;
		s1 >> l;
		array[i].val = l;
		array[i].day = i;
	}

	string answer;
    int ans = mergeSort(array, size);

    // for(int i = 0; i < size; i++)
    // {
    //     cout << array[i].val << " ";
    // }

	answer = "Failed Trials " + to_string(ans) + "\n";
    string final_ans;

    final_ans = answer + a;
    cout << final_ans;

	delete[] array;
	return 0;
}