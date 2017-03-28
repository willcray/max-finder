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

ThreadArgs args;

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
	}
	return nums;
}

void * compare(void * passedArgs)
{

	// compare the two variables
	ThreadArgs * s = (ThreadArgs*)passedArgs;
	int left = s->l;
	int right = s->r;
	// cout << "left index: " << left << "; right index: " << right << endl;
	// check if left index is less than the right index
	if(left >= right)
	{
		cout << "ERROR: compare(): left index is greater than right" << endl;
		exit(1);
	}
	// CRITICAL SECTION
	if(s->globalNums[left] < s->globalNums[right])
	{
		int temp = s->globalNums[left];
		s->globalNums[left] = s->globalNums[right];
		s->globalNums[right] = temp;
	}

	b.barrierPoint();

	// clean up and exit
	pthread_exit(NULL);
}

int run(vector<int> * nums)
{
	// case where it's a size of 1
	if (nums->size() == 1)
	{
		return nums->at(0);
	}

	int numThreads = nums->size() / 2;
	int numRounds = log2(nums->size());

	// set up struct to be passed as thread argument
	copy(nums->begin(), nums->end(), args.globalNums);

	int indexDiff = 1;
	int iterDiff = 2;
	b.init(numThreads);

	while(numRounds > 0)
	{
		// update global information
		// cout << "calling init for " << numThreads << " threads" << endl;

		// set up threading
		pthread_t threads[numThreads];
		int threadIndex = 0;
		// spin threads for this round
		for(int i = 0; i < nums->size(); i = i + iterDiff)
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
				// cout << "left index is " << args.l << "; right index is " << args.r << endl;
			}
			++threadIndex;
		}
		--numRounds;
		indexDiff *= 2;
		iterDiff *= 2;
		numThreads /= 2;

		
		pthread_mutex_lock(&b.d);
		while(b.count < b.n)
		{
			pthread_cond_wait(&b.cv, &b.d);
		}
		b.count = 0;
		b.n = numThreads;
		pthread_mutex_unlock(&b.d);
		
	}
	pthread_mutex_destroy(&b.d);
    pthread_cond_destroy(&b.cv);
	// largest value will be at far left of global vector
	/*
	for(int i = 0; i < 50; ++i)
	{
		cout << args.globalNums[i] << endl;
	}
	*/
	return args.globalNums[0];
}
