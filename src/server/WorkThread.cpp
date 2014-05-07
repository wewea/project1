/*************************************************************************
	> File Name: WorkThread.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 11时24分38秒
 ************************************************************************/


#include "ThreadPool.h"
#include "WorkThread.h"

WorkThread::WorkThread()
{
  _client_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(_client_fd == -1)
	{	
		std::runtime_error("socket failed!");
	}
}


void WorkThread::run()
{
	while(1)
	{
		Task task;
		if(!_p_threadpool->get_task(task))
		{
			break;
		}
		exec_task(task);
	}
}

void WorkThread::register_thread(ThreadPool *p)
{
	_p_threadpool = p;
}

void WorkThread::exec_task(Task task)
{
	sendto(_client_fd, "hello", 6, 0, (struct sockaddr*)&task.client, sizeof(task.client));
}


