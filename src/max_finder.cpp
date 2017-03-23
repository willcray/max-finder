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