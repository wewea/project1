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
#include "Socket.h"
#include "ThreadPool.h"
using namespace std;

int main(int argc, char* argv[])
{
	ifstream fin(argv[1]);
	string ip, port;
	fin >> ip >> port;
	cout << ip << " " << port << endl;;
	fin.close();

	ThreadPool pool;
	Socket server(ip, port);

	pool.start_pool();
	int len = 1024*1024;
	char *buf = new char[len];
	while(true)
	{
		Task task;
		server.recv_msg(buf, len);
		task.client = server.get_client();
		task.request = buf;
		pool.add_task(task);
	}
	pool.stop_pool();
}

