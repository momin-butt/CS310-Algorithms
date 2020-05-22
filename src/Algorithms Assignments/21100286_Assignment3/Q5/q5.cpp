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

int count1 = 0;
int count2 = 0;
bool spot = true;
const int divider = 2;
const int array_start_index = 0;

int decode(int photo1, int photo2)
{
	if(photo1 == photo2)
	{
		return 1;
	}
	else
		return 0;
}

int comparePhotos(int cnt1, int cnt2, int arr1, int arr2)
{
	if(cnt1 > cnt2)
	{
		// cout << count1;
		spot = true;
		return 1;		
	}

	else
	{	
		spot = false;
		// cout << count2;
		return 0;		
	}
}

int checker(int* specie_arr, int first_p, int last_p)
{
	int temp1 = 0;
	int temp2 = 0;

	int size_of_photos = last_p-1;

	if(first_p == size_of_photos)
	{
		int ret_photo = specie_arr[first_p];
		return ret_photo;
	}
	
	int center = (first_p+last_p)/divider;

	int subarr1 = checker(specie_arr, first_p, center);
	int subarr2 = checker(specie_arr, center, last_p);


	for(int i = first_p; i < last_p; i++)
	{
		if(decode(specie_arr[i], subarr1) == true)
		{
			temp1++;
		}

		else
		{
			continue;
		}
	}

	for(int i = first_p; i < last_p; i++)
	{

		if(decode(specie_arr[i], subarr2) == true)
		{
			temp2++;
		}

		else
		{
			continue;
		}
	}

	count1 = temp1;
	count2 = temp2;

	if(comparePhotos(temp1,temp2,subarr1,subarr2) == 1)
	{
		return subarr1;
	}

	else

		return subarr2;

}


int main(int argc, char** argv)
{

	char* filename = argv[1];

    string line;
    int photos,species = 0;

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
    s0 >> photos;

    getline(myFile,line);

    stringstream s1(line);

    string temp1;
    s1 >> temp1;
    s1 >> species;

    getline(myFile,line);

    int len = line.length();

    stringstream s2(line);

    int* specie_arr;
    specie_arr = new int[photos];

    for(int i = 0; i < photos; i++)
    {
    	int val = 0;
    	s2 >> val;
    	specie_arr[i] = val;
    	// cout << specie_arr[i] << " ";
    }

    int algo = checker(specie_arr,array_start_index,photos);

    string ans2;

    if(spot == true)

    	ans2 = "Dominant Species Count " + to_string(count1);

   	else

   		ans2 = "Dominant Species Count " + to_string(count2);

	int counter = 0;
	string indices;

	for(int i = 0; i < photos; i++)
	{
		if(decode(specie_arr[i], algo) == 1)
		{
			indices = indices + to_string(i) + " ";
			counter++;				
		}

	}

	indices = indices.substr(0,indices.length()-1);

	string ans3 = "Dominant Species Indices " + indices;

	string ans1;

	if(counter > (photos)/2.0)
	{
		ans1 = "Success";
	}
	else
		ans1 = "Failure";

	string ans4;

	if(ans1 == "Failure")
	{
		ans4 = ans1 + "\n";
		cout << ans4;
	}

	else

	{
		ans4 = ans1 + "\n" + ans2 + "\n" + ans3 + "\n";
		cout << ans4;
	}

	return 0;
}
