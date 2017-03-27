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

	int max = recurse(nums);
	cout << "FINISHED: max number is " << max << endl;
	


	return 0;
}