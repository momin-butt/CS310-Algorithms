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
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

struct racks {

	float rat;
	float prob;
	float len;
	int index;

};

int char_to_int(int c){

	return c - '0';
}

int compare(racks xxx, racks zzz)
{
	if(xxx.rat > zzz.rat)
	{
		return 1;
	}

	else

		return 0;
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

	string temp0;
	s0 >> temp0;
	s0 >> size;

	getline(myFile,line);

	vector<float> lengths;

	stringstream s1(line);

	string temp1;
	s1 >> temp1;


	for(int i = 0; i < size; i++)
	{
		float l = 0;
		s1 >> l;
		lengths.push_back(l);
	}

	getline(myFile,line);

	vector<float> probabilities;

	stringstream s2(line);

	string temp2;
	s2 >> temp2;

	for(int i = 0; i < size; i++)
	{	
		float p = 0;
		s2 >> p;
		probabilities.push_back(p);
	}

	vector<float> ratios;

	for(int k = 0; k < size; k++)
	{
		float r = 0;
		r = (lengths[k])/(probabilities[k]);
		ratios.push_back(r);
	}

	vector <racks> boxes;

	for(int i = 0; i < size; i++)
	{
		racks xyz;

		xyz.len = lengths[i];
		xyz.prob = probabilities[i];
		xyz.rat = ratios[i];
		xyz.index = i+1;

		boxes.push_back(xyz);
	}

	sort(boxes.rbegin(),boxes.rend(),compare);

    float sum;
    float exp_time;
    string answer;

	for(int j = 0; j < size; j++) 	
	{
		sum += boxes[j].len;
		exp_time += boxes[j].prob * sum;

		answer = answer + to_string(boxes[j].index) + " ";
	}

	answer = answer + "\n" + "Expected time: ";
	cout << answer << exp_time << endl;

	return 0;
}