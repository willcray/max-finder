#ifndef MAX_FINDER_H_
#define MAX_FINDER_H_

#include <vector>

using namespace std;

struct ThreadArgs
{
	vector<int> globalNums;
	int l;
	int r;
	ThreadArgs()
	{}
};

vector<int> parse(string file);
void * compare(void * args);
int run(vector<int> * nums);

#endif
