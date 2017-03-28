#ifndef BARRIER_H_
#define BARRIER_H_

#include <pthread.h>

class Barrier
{
public:
	pthread_mutex_t d;
	pthread_cond_t cv;
	int count;
	int n;
	void init(int n);	
	void barrierPoint();
};

extern Barrier b;

#endif

