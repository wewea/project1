/*************************************************************************
	> File Name: Thread.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 10时52分30秒
 ************************************************************************/

#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

class Thread
{
	public:
		Thread();
		virtual ~Thread();
		void start();
		static void *thread_func(void *arg);
		virtual void run() = 0;
		void join();
	private:
		pthread_t _tid;
		bool _is_started;
};

#endif

