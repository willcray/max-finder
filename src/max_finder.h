#ifndef MAX_FINDER_H_
#define MAX_FINDER_H_

using namespace std;

vector<int> parse(string file);
int max(vector<int> twoNums);
void *max_wrapper(void *arg);
void recurse(vector<int> nums);

#endif
