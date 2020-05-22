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

Time Complexity: O(nm)
Recurrence Relation: if str3.length() < 1 then return 1
					 else if str1[0] == str3[0] then Interleaved(i+1,j,k+1)
					 else if str2[0] == str3[0] then Interleaved(i,j+1,k+1)

*/

int *memo_arr;
bool c = false;

string str1,str2,strfinal;
string sel1 = "\n1:";
string sel2 = "\n2:";
string result;


int Interleaved(int i,int j,int k)
{
	if(strfinal.length() == (i+j))
	{
		string ans = "VALID\n";
		cout << ans << result << endl;
		return 1;
	}

	if(str1[i] != strfinal[k] && str2[j] != strfinal[k])
	{
		string ans;
		ans = "INVALID";
		cout << ans << endl;
		return 0;
	}

	int count = 0;

	if(str1[i] == strfinal[k])
	{	
		if(c)
		{
			result = result + str1[i];
		}

		else
		{
			c = true;
			result = result + sel1 + str1[i];
		}
		
		memo_arr[count] = Interleaved(i+1,j,k+1);
		count++;
	}

	else
	{
		int count1 = count+1;

		if(!c)
		{
			result = result + str2[j];
		}
		else
		{
			c = false;
			result = result + sel2 + str2[j];
		}

		memo_arr[count1] = Interleaved(i,j+1,k+1);
		count1++;
	}
	
}


int main(int argc, char** argv)
{
	char* filename = argv[1];

	ifstream myFile;
	myFile.open(filename);

	int numofstrings = 3; 

	myFile >> str1;
	myFile >> str2;
	myFile >> strfinal;

	int string_indices[numofstrings];

	for(int i = 0; i < numofstrings; i++)
	{
		string_indices[i] = 0;
	}

	int final_length = str1.length()+str2.length();
	memo_arr = new int[final_length];

	for (int i = 0; i < final_length; ++i)
	{
		memo_arr[i] = 0;
	}

	memo_arr[0] = Interleaved(string_indices[0],string_indices[1],string_indices[2]);

	return 0;
}