#ifndef MAX_FINDER_H_
#define MAX_FINDER_H_

#include <vector>

using namespace std;

struct ThreadArgs
{
	int globalNums[4096];
	int l;
	int r;
	ThreadArgs()
	{}
};

extern ThreadArgs args;

vector<int> parse(string file);
void * compare(void * args);
int run(vector<int> * nums);

#endif
