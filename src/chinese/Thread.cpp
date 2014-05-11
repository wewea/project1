/*************************************************************************
	> File Name: Thread.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 11时15分22秒
 ************************************************************************/

#include "Thread.h"

Thread::Thread():_tid(0), _is_started(false)
{
	
}

Thread::~Thread()
{
}

void Thread::start()
{
	if(!_is_started)
	{
		pthread_create(&_tid, NULL, thread_func, this);
	}
}

void Thread::join()
{
	pthread_join(_tid, NULL);
}

void* Thread::thread_func(void *arg)
{
	Thread *p = static_cast<Thread*>(arg);
	p->run();
	return NULL;
}


