/*************************************************************************
	> File Name: Mutex.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 10时39分22秒
 ************************************************************************/



#ifndef _MUTEX_H_
#define _MUTEX_H_
#include <pthread.h>
#include "noncopyable.h"

class Condition;

class Mutex : public noncopyable
{
	friend class Condition;

	public:
		Mutex();
		~Mutex();
		void lock();
		void unlock();
	private:
		pthread_mutex_t _mutex;
};

class MutexGuard : public noncopyable
{
	public:
		explicit MutexGuard(Mutex& lock):_mutex(lock) {
		_mutex.lock();
	}
		~MutexGuard()
		{
			_mutex.unlock();
		}
	private:
		Mutex & _mutex;
};

#endif


