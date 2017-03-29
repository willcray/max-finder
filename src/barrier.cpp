#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include "barrier.h"

// 3 binary mutexes/semaphores
// wait - sent to true once all threads have finished/count reaches 0
// decrement - controls access to decrement the count variable

Barrier b;
pthread_mutex_t d;
pthread_cond_t cv;

void Barrier::init(int n)
{
	this->count = n;
	pthread_mutex_init(&d, NULL);
	pthread_cond_init(&cv, NULL);
}

void Barrier::barrierPoint()
{
	// check for decrement mutex
	pthread_mutex_lock(&d);

	// wait on increment semaphore
	--this->count;

	if(this->count == 0)
	{
		pthread_cond_broadcast(&cv);
	}
	else
	{
		pthread_cond_wait(&cv, &d);
	}
	pthread_mutex_unlock(&d);

	/*
	The barrier can be implemented in such a way that it is shared by all rounds of
	comparisons via passing a value to it indicating the number of threads running concurrently for a
	particular round. 

	When a thread finishes its job, it issues a call to the barrier and the barrier
	checks to see if the thread needs to wait (What the barrier does here is to decrement the value
	passed to it. If the value after decrement is nonzero, then the thread calling the barrier is blocked
	on the condition variable. Otherwise, the barrier will release all threads from the condition
	variable via invoking the pthread_cond_broadcast() function).
	*/
}






