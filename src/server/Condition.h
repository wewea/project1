/*************************************************************************
	> File Name: Condition.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 10时45分06秒
 ************************************************************************/


#ifndef _CONDITION_H_
#define _CONDITION_H_

#include "Mutex.h"
class Condition
{
	public:
		Condition(Mutex &lock);
		~Condition();
		void wait();
		void notify();
		void notify_all();

	private:
		pthread_cond_t _cond;
		Mutex &_lock;
};

#endif

