/*************************************************************************
	> File Name: Condition.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 10时47分37秒
 ************************************************************************/

#include "Condition.h"
#include "Mutex.h"
using namespace std;

Condition::Condition(Mutex &lock):_lock(lock)
{
	pthread_cond_init(&_cond, NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(&_cond);
}

void Condition::wait()
{
	pthread_cond_wait(&_cond, &_lock._mutex);
}

void Condition::notify()
{
	pthread_cond_signal(&_cond);
}

void Condition::notify_all()
{
	pthread_cond_broadcast(&_cond);
}


