#include <stdlib.h>
#include <semaphore.h>
#include "barrier.h"

// 3 binary mutexes/semaphores
// wait - sent to true once all threads have finished/count reaches 0
// decrement - controls access to decrement the count variable
// handshake

Barrier b;

int Barrier::init(int n)
{
	this->threadsRunning = n;
	this->w = PTHREAD_MUTEX_INITIALIZER;
	this->d = PTHREAD_MUTEX_INITIALIZER;
	this->h = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_init(&cv, NULL);
}

int Barrier::setThreadNum(int n)
{
	this->threadsRunning = n;
}

int Barrier::wait()
{

}

int Barrier::tryWait()
{

}

int Barrier::signal()
{

}

int Barrier::barrier_point(void)
{
	// check for decrement semaphore
	// wait on decrement semaphore
		--threadsRunning;

	if(threadsRunning != 0)
	{
		// wait() on condition variable wait
	}
	else
	{
		// pthread_cond_broadcast();
	}
	return threadsRunning;
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








