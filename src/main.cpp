#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <pthread.h>
#include <math.h>

using namespace std;

struct ThreadArgs
{
	int l;
	int r;
	ThreadArgs()
	{}
};

ThreadArgs args[2048];
int globalNums[4096];

pthread_mutex_t d;
pthread_cond_t cv;
int threadCount;
int arrIndex;

/////////////////////
/*
BARRIER
*/

void init(int n)
{
	threadCount = n;
}

void barrierPoint()
{
	// check for decrement mutex
	pthread_mutex_lock(&d);

	// wait on increment semaphore
	--threadCount;

	if(threadCount == 0)
	{
		pthread_cond_broadcast(&cv);
	}
	pthread_mutex_unlock(&d);
}
///////////

/*
MAX_FINDER
*/

void parse(string fileName)
{
	arrIndex = 0;

	ifstream file;
	file.open(fileName);
	if(!file.is_open())
	{
		cout << "ERROR: file not opened properly" << endl;
		exit(1);
	}
	else
	{
		string strNum = "";
		// file is opened properly
		while(file.good())
		{
			getline(file, strNum, '\n');
			globalNums[arrIndex] = stoi(strNum);
			++arrIndex;
		}
		file.close();
	}
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
	if(globalNums[left] < globalNums[right])
	{
		int temp = globalNums[left];
		globalNums[left] = globalNums[right];
		globalNums[right] = temp;
	}

	barrierPoint();
	// clean up and exit
	pthread_exit(NULL);
}

int run()
{
	int size = arrIndex + 1;
	// case where it's a size of 1
	if (size == 1)
	{
		return globalNums[0];
	}

	int numThreads = size / 2;
	int numRounds = log2(size);

	// set up struct to be passed as thread argument
	// copy(nums->begin(), numsend(), globalNums);

	int indexDiff = 1;
	int iterDiff = 2;

	// set up barrier
	init(numThreads);
	pthread_mutex_init(&d, NULL);
	pthread_cond_init(&cv, NULL);

	while(numRounds > 0)
	{
		cout << "entering while" << endl;
		// set up threading
		pthread_t threads[numThreads];
		int threadIndex = 0;
		// spin threads for this round
		for(int i = 0; i < size; i = i + iterDiff)
		{
			// update indices to be checked by this thread
			args[i].l = i;
			args[i].r = i + indexDiff;

			pthread_attr_t tattr;
			pthread_attr_init(&tattr);
			pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);
			if(pthread_create(&threads[i], &tattr, compare, &args[i]) < 0)
			{
				cout << "ERROR: run(): pthread_create call unsuccessful" << endl;
				exit(1);
			}

			++threadIndex;
		}
		--numRounds;
		indexDiff *= 2;
		iterDiff *= 2;
		numThreads /= 2;
		
		pthread_mutex_lock(&d);

		while (threadCount != 0)
		{
			pthread_cond_wait(&cv, &d);
		}
		init(numThreads);

		pthread_mutex_unlock(&d);
		
	}
	pthread_mutex_destroy(&d);
    pthread_cond_destroy(&cv);
	return globalNums[0];
}

int main(int argc, char *argv[])
{
	// input sanitization
	if(argc > 2 || argc == 1)
	{
		cout << "ERROR: too many or too few command line params passed" << endl;
		exit(1);
	}

	// get vector of ints from txt file
	parse(argv[1]);
	int max = run();
	cout << "FINISHED: max number is " << max << endl;
	return 0;
}