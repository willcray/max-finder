#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <pthread.h>
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
		file.close();
	}/*
	for (auto &ele : nums)
	{
		cout << ele << endl;
	}
	*/
	return nums;
}

void * compare(void * args)
{
	// compare the two variables
	ThreadArgs * s = (ThreadArgs*)args;
	for (auto &ele : s->globalNums)
	{
		cout << ele << endl;
	}
	int left = s->l;
	int right = s->r;

	// cout << "left index: " << left << "; right index: " << right << endl;
	// check if left index is less than the right index
	if(left > right)
	{
		cout << "ERROR: compare(): left index is greater than right" << endl;
		exit(1);
	}
	// compare the two numbers at that index
	// if left is bigger, do nothing
	if(s->globalNums.at(left) > s->globalNums.at(right))
	{
		// b.wait()
	}
	// CRITICAL SECTION - swap the subarrays
	else
	{
		b.barrier_point();
	}

		vector<int> leftCopy(right - left);
		for (int i = 0; i < right; ++i)
		{
			leftCopy.at(i) = s->globalNums.at(i);
		}
		for (int i = 0; i < right; ++i)
		{
			// replace left subarray with right subarray
			s->globalNums.at(i) = s->globalNums.at(i + right);
		}
		for (int i = right; i < s->globalNums.size(); ++i)
		{
			// replace right side with copy of left
			s->globalNums.at(i) = leftCopy.at(i - right);
		}		
}

int run(vector<int> * nums)
{
	cout << "entering run()" << endl;
	// case where it's a size of 1
	if (nums->size() == 1)
	{
		return nums->at(0);
	}

	int numThreads = nums->size() / 2;
	int numRounds = log2(nums->size());

	// set up barrier
	b.init(numThreads);

	// set up struct to be passed as thread argument

	ThreadArgs args;
	args.globalNums = *nums;

	int indexDiff = 1;
	int iterDiff = 2;

	// generate each round of analysis

	while(numRounds > 0)
	{
		// update global information
		b.setThreadNum(numThreads);

		// set up threading
		pthread_t threads[numThreads];
		int threadIndex = 0;
		// spin threads for this round
		for(int i = 0; i < numThreads; i = i + iterDiff)
		{
			// update indices to be checked by this thread
			args.l = i;
			args.r = i + indexDiff;

			pthread_attr_t tattr;
			pthread_attr_init(&tattr);
			pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);
			if(pthread_create(&threads[i], &tattr, compare, &args) < 0)
			{
				cout << "ERROR: run(): pthread_create call unsuccessful" << endl;
				exit(1);
			}
			else
			{
				// cout << "pthread #" << threads[threadIndex] << " created successfully" << endl;
			}
			++threadIndex;
		}
		--numRounds;
		indexDiff *= 2;
		iterDiff *= 2;
	}
	// largest value will be at far left of global vector
	return args.globalNums.at(0);
}
