#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <pthread.h>
#include "max_finder.h"
#include "barrier.h"

using namespace std;

int main(int argc, char *argv[])
{
	// input sanitization
	if(argc > 2 || argc == 1)
	{
		cout << "ERROR: too many or too few command line params passed" << endl;
		exit(1);
	}

	// get vector of ints from txt file
	vector<int> nums = parse(argv[1]);

	bool notFound = true;
	int numThreads = nums.size() / 2;
	while(notFound)
	{
		pthread_t threads[numThreads];
		vector<int> twoNums;
		int threadCount = 0;
		for(int i = 0; i < nums.size(); i = i + 2)
		{
			// pthread_create(&threads[threadCount], NULL, max, (void *) twoNums);
		}
		// update number of threads to be created
		numThreads /= 2;
	}


	return 0;
}