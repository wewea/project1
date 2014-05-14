/*************************************************************************
	> File Name: WorkThread.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 11时22分11秒
 ************************************************************************/


#ifndef _WORKTHREAD_H_
#define _WORKTHREAD_H_

#include <stdexcept>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unordered_map>
#include "Thread.h"
#include "Task.h"
#include "Dict.h"
#include "Query.h"
#include "json/json.h"
class ThreadPool;

class WorkThread : public Thread
{
	friend class ThreadPool;//轮询线程时,需要访问_L2_cache
	friend class Cache;
	public:
		WorkThread();
		void run();
		void register_thread(ThreadPool *p);
		friend std::string json_string(const std::string &s);
		void exec_task(Task task);

	private:
		ThreadPool *_p_threadpool;
		int _client_fd;
		pthread_t _tid;
		std::unordered_map<std::string, std::string> _cache;
};

#endif

