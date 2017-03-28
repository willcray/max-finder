#ifndef MAX_FINDER_H_
#define MAX_FINDER_H_

#include <vector>

using namespace std;

struct ThreadArgs
{
	int l;
	int r;
	ThreadArgs()
	{}
};

extern int globalNums[4096];
extern ThreadArgs args[2048];

vector<int> parse(string file);
void * compare(void * args);
int run(vector<int> * nums);

#endif
