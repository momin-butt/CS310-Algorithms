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

Time Complexity: O(n^2)

*/


int main(int argc, char** argv)
{

	char* filename = argv[1];

	string line;
	int teams = 0;
	int indexer = 0;

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
	s0 >> teams;


	vector<int> *locations = new vector<int>[teams];

	while(!myFile.eof())
	{
		getline(myFile,line);

		stringstream s1(line);
		string temp1;

		s1 >> temp1 >> temp1;

		while(s1 >> temp1)
		{
			if(temp1 == "-")
			{
				locations[indexer].push_back(-1);
			}

			else
			{
				int ind_loc = stoi(temp1.substr(1,1));
				locations[indexer].push_back(ind_loc);
			}
		}

		indexer++;
	}

		vector<int>* teams_preferences = new vector<int>[teams];
		vector<int>* locations_preferences = new vector<int>[teams]; 

		int size = locations[0].size()-1;

		for(int i = 0; i < teams; i++)
		{
		for(int j = size ; j >= 0; j--)
		{
			if(locations[i][j] != -1)
			{
				int loc = locations[i][j];
				teams_preferences[i].push_back(loc-1);
			} 

		}
		// cout<<endl;
	}

	// for(int i =0; i < teams; i++){
	// 	for(int j =0; j <teams_preferences[i].size(); j++){
	// 		// if(matrix[i][j] != -1){
	// 			cout<<teams_preferences[i][j]<<" ";
	// 		// } 
	// 	}
	// 	cout<<endl;
	// }

	for(int i = size; i >= 0; i--)
	{
		for(int j = 0 ; j < teams; j++)
		{
			if(locations[j][i] != -1)
			{
				// cout<<locations[i][j]<<" ";
				int loc = locations[j][i];
				locations_preferences[loc-1].push_back(j);
			} 

		}
		// cout<<endl;
	}

	// for(int i =0; i < teams; i++){
	// 	for(int j =0; j <locations_preferences[i].size(); j++){
	// 		// if(matrix[i][j] != -1){
	// 			cout<<locations_preferences[i][j]<<" ";
	// 		// } 
	// 	}
	// 	cout<<endl;
	// }

	queue<int> freeteams;
	int	*matches = new int[teams];
	int *freelocations = new int[teams];

	for(int i = 0; i < teams; i++)
	{
		matches[i] = -1;
		freelocations[i] = true;
	} 

	bool isFree = true;

	while(isFree)
	{

		int freeloc = 0;

		for(int i = 0; i < teams; i++)
		{
			if(freelocations[i] == 0)
			{
				isFree = false;
				
			}
			else if(freelocations[i])
			{
				freeloc = i;
				isFree = true;
				break;
			}
		}

		if(isFree == false)
		{
			break;
		}

		for(int i = 0; i < teams && freelocations[freeloc]; i++)
		{
			int j = locations_preferences[freeloc][i];
			if(matches[j] == -1)
			{
				matches[j] = freeloc;
				freelocations[freeloc] = false;
			} 
			else 
			{
				bool betteroption = false;
				int loc2 = matches[j];

				for(int i = 0; i < teams; i++)
				{
					if(teams_preferences[j][i] == freeloc)
					{
						betteroption = true;
						// break;
					}
					else if(teams_preferences[j][i] == loc2)
					{
						betteroption = false;
						break;

					}
				}

				if(betteroption)
				{
					freelocations[loc2] = true;
					matches[j] = freeloc;
					freelocations[loc2] = false;
				}
			}
		}
	}


 string result = "Final Destinations: ";
 int t_size = teams-1;
 string tstring = " T";
 string lstring = "L";


 for(int i = 0; i < teams;  i++) 
 {
 	if(i != t_size)
 	{
 		result = result + lstring + to_string(matches[i]+1) + tstring + to_string(i+1) + ",";
 	}

 	else
 	{
 		result = result + lstring + to_string(matches[i]+1) + tstring + to_string(i+1);
 	}
 }

 cout << result << endl;

	return 0;
}