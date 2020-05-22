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

/*

Time Complexity: O(n)
Recurrence Relation: Base case: if(start+1 > end) then return 0
					 Recurrence = Bestcost = (mark[end] - mark[start]) + min(mincost(start,i),mincost[i,end])

*/

using namespace std;

struct revenueArrays{

	int* revenue_high;
	int* revenue_low;

};

int revenue_count = 0;

int stepper(int indexer,int* memo_array,int* temp,int checker,revenueArrays arrs)
{
	if(memo_array[indexer] != checker)
	{
		return memo_array[indexer];
	}
	else
	{
		int diff_two = stepper(indexer-2,memo_array,temp,checker,arrs);
		int diff_one = stepper(indexer-1,memo_array,temp,checker,arrs);

		int xyz = 0;

		if(indexer > 1)
		{
			xyz = arrs.revenue_high[indexer]+diff_two;
		}
		else
		{
			xyz = arrs.revenue_high[indexer];
		}

		int abc = arrs.revenue_low[indexer]+diff_one;

		if(xyz < abc)
		{
			memo_array[indexer] = abc;
			temp[indexer] = INT8_MIN;
		}
		else
		{
			memo_array[indexer] = xyz;
			temp[indexer] = INT8_MAX;
		}

		return memo_array[indexer];
	}
}

int main(int argc, char** argv)
{
	// string ans = "";
	// ans+="Week 1 : Priming\n";
	// ans+="Week 2 : High 1\n";
	// ans+="Week 3 : Priming\n";
	// ans+="Week 4 : Low 6\n";
	// ans+="Total Revenue : 7\n";	
	// cout<<ans;

	char* filename = argv[1];

    string line;
    int *memo_array;
	int* temp;

    int weeks_count;
    revenueArrays arrs;

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
    s0 >> weeks_count;

    getline(myFile,line);

    stringstream s1(line);
    string temp1;
    s1 >> temp1;

    arrs.revenue_high = new int[weeks_count];
    arrs.revenue_low = new int[weeks_count];
    memo_array = new int[weeks_count];

    for(int i = 0; i < weeks_count; i++)
    {
    	int j = 0;
    	s1 >> j;

    	arrs.revenue_high[i] = j;
    }

    getline(myFile,line);

    stringstream s2(line);
    string temp2;
    s2 >> temp2;

    for(int i = 0; i < weeks_count; i++)
    {
    	int j = 0;
    	s2 >> j;

    	arrs.revenue_low[i] = j;
    }

	int first_rh = arrs.revenue_high[0];
	int first_rl = arrs.revenue_low[0];

	temp = new int[weeks_count];

	for(int i = 0; i < weeks_count; i++)
	{
		memo_array[i] = -1;
		temp[i] = 0;
	}

	int vecsize = weeks_count-1;

	int first_memo_array = memo_array[0];
	int first_temp = temp[0];

	if(first_rh > first_rl)
	{
		first_memo_array = first_rh;
		first_temp = INT8_MAX; 
	}
	else
	{
		first_memo_array = first_rl;
		first_temp = INT8_MIN; 
	}

	revenue_count = stepper(vecsize,memo_array,temp,-1,arrs);
	int checker = -1;
	int iter1,iter2 = 0;

	while(iter1 < weeks_count)
	{
		if(temp[iter1] == INT8_MAX)
		{
			temp[iter1-1] = checker;
		}

		iter1++;
	}

	string high_low_prime = "";

	for(int i = 0; i < weeks_count; i++)
	{
		high_low_prime += "Week " + to_string(i+1) + ": ";

		if(temp[i] == INT8_MAX)
		{
			high_low_prime += "High " + to_string(arrs.revenue_high[i]) + "\n";
		}
		else if(temp[i] == INT8_MIN)
		{
			high_low_prime += "Low " + to_string(arrs.revenue_low[i]) + "\n";
		}
		else
		{
			high_low_prime += "Priming\n";
		}
	}

	string final_result;
	final_result = high_low_prime + "Total Revenue: " + to_string(revenue_count) + "\n";

	cout << final_result;

	return 0;
}