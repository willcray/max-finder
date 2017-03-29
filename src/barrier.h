#ifndef BARRIER_H_
#define BARRIER_H_

#include <pthread.h>

class Barrier
{
public:
	int count;
	void init(int n);	
	void barrierPoint();
};

extern Barrier b;
extern pthread_mutex_t d;
extern pthread_cond_t cv;

#endif

