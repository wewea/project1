/*************************************************************************
	> File Name: ThreadPool.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 11时39分17秒
 ************************************************************************/

#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <queue>
#include <vector>
#include "WorkThread.h"
#include "noncopyable.h"
#include "Condition.h"
#include "Task.h"

class ThreadPool : public noncopyable
{
	public:
		 ThreadPool(int num = 12);
		~ThreadPool();
		void start_pool();
		void stop_pool();
		bool add_task(Task task);
		bool get_task(Task &task);

	private:
		std::queue<Task> _queue;
		std::vector<WorkThread>::size_type _max_thread;
		std::vector<WorkThread> _thread_pool;
		bool _on;
		Condition _cond;
		Mutex _lock;
};

#endif

