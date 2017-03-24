#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "max_finder.h"

using namespace std;

vector<int> parse(string fileName)
{
	vector<int> nums;

	ifstream file;
	file.open(fileName);
	if(!file.is_open())
	{
		cout << "ERROR: file not opened properly" << endl;
		exit(1);
	}
	else
	{
		string strNum;
		// file is opened properly
		while(file.good())
		{
			getline(file, strNum, ' ');
			nums.push_back(stoi(strNum));
		}
		/*
		for(auto &ele : nums)
		{
			cout << ele << endl;
		}
		*/
		file.close();
	}
	return nums;
}

int max(vector<int> twoNums)
{
	if(twoNums.size() != 2)
	{
		cout << "ERROR: max() function not passed vector of size 2" << endl;
		exit(1);
	}
	else
	{
		if(twoNums.at(0) > twoNums.at(1))
		{
			return twoNums.at(0);
		}
		else
		{
			return twoNums.at(1);
		}
	}
}