#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <stack>
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <sstream>
#include <set>
using namespace std;

/*

Time Complexity: O(n^2)
Recurrence Relation: stepper(i,j):
					 if i + 1 < j:
 					 return (Cost[j] - Cost[i]) +  findMin(stepper(i,k), stepper(k,j))  
 					 where (k > j, k > i)	
*/

typedef struct {

	int length;
	vector<int> cuts;

} XYZ;


int **newmemoArr;
int **memoArr;
string result;
bool yes = true;
string answer;

int findMin(int a, int b)
{
	if(a <= b)
	{
		return a;
	}

	else
		return b;
}

bool Output(int start, int end, XYZ xxx)
{
	if (end <= start+1)
	{
		return false;
	}

	int k = newmemoArr[start][end];
	answer = answer + to_string(xxx.cuts[k]) + " ";

	Output(start,k,xxx);
	Output(k,end,xxx);
}

int stepper(XYZ xxx, int n1, int n2,int start_point, int finish_point)
{ 
	int array_min = 100000;

	if ((finish_point <= start_point + 1) == yes)
	{
		return 0;
	} 

	else 
	{
		int mid_point = start_point+finish_point/2;
		
		int sub_mid = start_point+1;

		while (sub_mid != finish_point)
		{
			int start_min = stepper(xxx,n1,n2,start_point,sub_mid);
			int end_min = stepper(xxx,n1,n2,sub_mid,finish_point);

			if (array_min != findMin(array_min, start_min + end_min))
			{
				newmemoArr[start_point][finish_point] = sub_mid;
				array_min = findMin(array_min, start_min + end_min);
			}

			sub_mid++;
		}

		int n1 = xxx.cuts[start_point];
		int n2 = xxx.cuts[finish_point];
		int cuttings = (n2 - n1) + array_min;
		int memo_val = memoArr[start_point][finish_point];		

		memo_val = cuttings;
		return memo_val;
	} 
}

int main(int argc, char** argv)
{
	XYZ xxx;
	xxx.cuts.push_back(0);

	char* filename = argv[1];
	
	ifstream myFile;
	int m_values;
	string line;

	myFile.open(filename);
	if (!myFile) 
	{
    	cout << "Error! Unable to open the file. \n";
    	return 0;   // call system to stop
	}

	getline(myFile,line);

	string temp1;
	stringstream s1(line);

	s1 >> temp1;
	s1 >> xxx.length;

	getline(myFile,line);

	string temp2;
	stringstream s2(line);

	s2 >> temp2;

	while(!(s2.eof()))
	{
		s2 >> m_values;
		int j = 0; 
		j = m_values;

		xxx.cuts.push_back(j);
	}
	xxx.cuts.push_back(xxx.length);

	int vecsize = xxx.cuts.size();

	newmemoArr = new int*[vecsize];
	memoArr = new int*[vecsize];

	for (int i = 0; i < vecsize; i++)
	{
		memoArr[i] = new int[vecsize];
		newmemoArr[i] = new int[vecsize];
	}

	vecsize -= 1;
	int x,y = 0;

	int result = stepper(xxx,x,y,0,vecsize);
	string ans1 = "Optimal Cut Ordering: ";
	string ans2 = "\nLeast Cost: " + to_string(result);

	Output(0,vecsize,xxx);

	cout << ans1+answer+ans2;

	return 0;
}	

