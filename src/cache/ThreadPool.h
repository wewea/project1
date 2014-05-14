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
#include <unordered_map>
#include "WorkThread.h"
#include "noncopyable.h"
#include "Condition.h"
#include "Task.h"
#include "Cache.h"
class ThreadPool : public noncopyable
{
	friend class Cache;
	friend class WorkThread; //让工作线程访问Cache类
	public:
		 ThreadPool (const std::string &cache_path ,int num = 12);
		~ThreadPool();
		void start_pool();
		void stop_pool();
		bool add_task(Task task);
		bool get_task(Task &task);
		void ScanCache();
		void UpDate(std::unordered_map<std::string, std::string> &L1,
			 std::unordered_map<std::string, std::string> &L2);

	private:
		std::queue<Task> _queue;
		std::vector<WorkThread>::size_type _max_thread;
		std::vector<WorkThread> _thread_pool;
		bool _on;
		Mutex _lock;
		Condition _cond;
		Cache _L2;
		std::unordered_map<std::string, std::string> _pool_cache;

};

#endif

