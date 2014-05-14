/*************************************************************************
	> File Name: test_server.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 14时08分42秒
 ************************************************************************/

#include <string>
#include <iostream>
#include <fstream>
#include "Task.h"
#include "json/json.h"
#include "WorkThread.h"
#include "Socket.h"
#include "ThreadPool.h"
#include "Init.h"
using namespace std;



int main(int argc, char* argv[])
{
	string log_path = argv[2];
	Init init(argv[1]);
	LOGGER_SEVERTIY(init.Severity());
	LOGGER_START(log_path);
	//min_priority default Logger::INFO



	

	ThreadPool pool(init.Cache(), init.ThreadPool());

	Dict dict(init.GBK());
	Socket server(init.IP(),init.Port());
	
	pool.start_pool();
	int len = 1024*1024;
	char *buf = new char[len]	;
	//cout << "test" << endl;
	while(true)
	{
		Task task;
		server.recv_msg(buf, len);
		task.client = server.get_client();
		task.request = buf;
		task.return_num = init.ReturnNum();
		cout << task.return_num << endl;
		pool.add_task(task);
	}
	pool.stop_pool();
}

