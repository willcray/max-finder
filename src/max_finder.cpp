#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "max_finder.h"
#include "barrier.h"

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
			return (void *)twoNums.at(0);
		}
		else
		{
			return (void *)twoNums.at(1);
		}
	}
}

void *max_wrapper(void *arg);
{
	vector<int> twoNums = *(vector<int> *)arg;
	int max = max(twoNums);
	int *maxVal = malloc(sizeof(int));
	*maxVal = max;
	return maxVal;
}

int recurse(vector<int> nums)
{
	// start recursive method
	int numThreads = nums.size() / 2;

	// BASE CASE: if there's only one number remaining
	if (num.size() == 1)
	{
		return nums.at(0);
	}
	pthread_t threads[numThreads];
	int threadIndex = 0;
	vector<int> newNums;

	init(numThreads);

		for(int i = 0; i < nums.size(); i = i + 2)
		{
			vector<int> twoNums;
			// twoNums.push_back(nums.at(i));
			// twoNums.push_back(nums.at(i + 1));
			// pthread_create(&threads[threadIndex], NULL, max_wrapper, (void *)twoNums);
			// get return value from max, push_back to newNums
			++threadIndex;
		}
	recurse(newNums);
}