/*************************************************************************
	> File Name: Task.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 13时27分38秒
 ************************************************************************/


#ifndef _TASK_H_
#define _TASK_H_
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>

class Task
{
	public:
		struct sockaddr_in client;
		std::string request;
		size_t return_num;

};

#endif

