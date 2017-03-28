#ifndef BARRIER_H_
#define BARRIER_H_

#include <pthread.h>

class Barrier
{
public:
	pthread_mutex_t w;
	pthread_mutex_t d;
	pthread_mutex_t h;
	pthread_cond_t cv;
	int threadsRunning;

	int init(int n);
	int setThreadNum(int n);
	int wait();
	int tryWait();
	int signal();
	int barrier_point(void);
};

extern Barrier b;

#endif

