#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "max_finder.h"
#include "barrier.h"

using namespace std;

int main(int argc, char *argv[])
{
	// input sanitization
	if(argc > 2 || argc == 1)
	{
		cout << "ERROR: too many or too few command line params passed" << endl;
		return 0;
	}

	// get vector of ints from txt file
	vector<int> nums = parse(argv[1]);

	

	return 0;
}