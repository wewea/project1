/*************************************************************************
	> File Name: Mutex.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 10时39分22秒
 ************************************************************************/



#ifndef _MUTEX_H_
#define _MUTEX_H_
#include <pthread.h>

class Condition;

class Mutex
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


#endif


