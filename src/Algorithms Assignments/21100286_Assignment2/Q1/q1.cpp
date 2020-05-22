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
using namespace std;

int char_to_int(int c){

	return c - '0';
}

int makeGrid(int* rows,int* cols,int boxsize)
{
	int** grid = new int*[boxsize];
	bool spot = true;

	for(int i = 0; i < boxsize; i++)
	{
		grid[i] = new int[boxsize];

		for(int j = 0; j < boxsize; j++)
		{
			grid[i][j] = !spot;
		}
	}

    int colcheck = 0;

	for (int i = 0; i < boxsize; i++)	
	{		
		do
		{
			int checker = -1000;
			for(int j = 0; j < boxsize; j++)
			{
				if(cols[j] > checker)
				{
                    if(grid[i][j] == !spot)
                    {
                        colcheck = j;
                        checker = cols[j]; 
                    }										
				}

				else
				{
					continue;
				}
			}

			grid[i][colcheck] = spot;
			rows[i] = rows[i]-1;
			cols[colcheck] = cols[colcheck]-1;

		} while(rows[i] != false);
	}

    bool empty = false;
    int traversal = 0;

	while(traversal < boxsize)
	{
        traversal++;

		if(rows[traversal] != empty || cols[traversal] != empty)
		{
			cout << "Not Possible." << endl;
			return 0;
		}

		else
		{
			continue;
		}
	}

	string answer = "";

	for(int i = 0; i < boxsize; i++)
	{
		for(int j = 0; j < boxsize; j++)
		{
			if(grid[i][j])
			{
				answer = answer + "(" + to_string(i+1) + "," + to_string(j+1) + ") ";
			}

			else
			{
				continue;
			}
		}

		answer = answer.substr(0,answer.length()-1);
		answer = answer + "\n";
	}

	cout << answer;

    for (int i = 0; i < boxsize; i++) 
    {
        delete[] grid[i];
    }
    delete[] grid;

	return 1;
}

int main(int argc, char** argv){
	
	char* filename = argv[1];

	vector<int> row_str;
	vector<int> col_str;

	for(int i = 0; i < row_str.size(); i++)
	{
		row_str[i] = 0;
	}

	for(int i = 0; i < col_str.size(); i++)
	{
		col_str[i] = 0;
	}

	string line;
	int boxsize = 0;

	ifstream myFile;
	myFile.open(filename);

	if(!myFile)
	{
		cout << "Error! Unable to open the file. \n";
		return 0;
	}

	getline(myFile,line);
	stringstream s0(line);

    string temp0;

    s0 >> temp0;
    s0 >> boxsize;

    getline(myFile,line);

    stringstream s1(line);

    string temp1;

    s1 >> temp1;

    for(int i = 0; i < boxsize; i++)
    {
        int l = 0;
        s1 >> l;
        row_str.push_back(l);
    }

    getline(myFile,line);

    stringstream s2(line);

    string temp2;

    s2 >> temp2;

    for(int i = 0; i < boxsize; i++)
    {
        int l = 0;
        s2 >> l;
        col_str.push_back(l);
    }

	int *rows = new int[boxsize];
	int *cols = new int[boxsize];

	for(int iter3 = 0; iter3 < boxsize; iter3++)
	{
		rows[iter3] = row_str[iter3];
		cols[iter3] = col_str[iter3];
	}

	makeGrid(rows,cols,boxsize);

    // Printing the grid.

	// cout << "\nn " << boxsize;
	// cout << endl << "Row";

	// for(int i = 0; i < boxsize; i++)
	// {
	// 	cout << " " << rows[i];
	// }

	// cout << endl << "Col";

	// for(int j = 0; j < boxsize; j++)
	// {
	// 	cout << " " << cols[j];
	// }

	// cout << endl;

	return 0;
}


	

