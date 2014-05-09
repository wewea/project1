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
#include "Thread.h"
#include "Task.h"
#include "Dict.h"
#include "Query.h"
#include "json/json.h"
class ThreadPool;

class WorkThread : public Thread
{
	public:
		WorkThread();
		void run();
		void register_thread(ThreadPool *p);
		friend std::string json_string(const std::string &s);
		void exec_task(Task task);

	private:
		ThreadPool *_p_threadpool;
		int _client_fd;
};

#endif

