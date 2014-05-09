/*************************************************************************
	> File Name: WorkThread.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 11时24分38秒
 ************************************************************************/


#include "ThreadPool.h"
#include "WorkThread.h"
#include "json/json.h"
#include "Query.h"
using namespace std;

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


string json_string(const string &s)
{
	//生成json字符串,实例化两个Value型的变量
	Json::Value root ;
	Json::Value arr ;
	istringstream ss(s);
	string buf;

	size_t index = 0;
	while(ss >> buf)
	{
		//定义一个临时变量，elem
		Json::Value elem ;
		char title[128] = "";
		char summary[128]="";
		//用随即数生成两个格式化的字符串
		sprintf(title , "tile_%d", index);
		sprintf(summary, "candicate %d: %s", index,buf.c_str());
		//将两个字符串，赋给elem的两个键
		elem["title"] = title ;
		elem["summary"] = summary ;
		//将elem追加到arr
		arr.append(elem);
		//控制循环变量,递减退出循环
		//size -- ;
		++ index;
	}
	//将arr赋给root的file键
	root["files"]=arr ;
	//实例化两个json类FastWriter 和　StyledWrited 的对象
	Json::FastWriter writer ;//FastWriter return string without Json format
	Json::StyledWriter stlwriter ;
	//用root传参给stlwriter的write方法并返回
	return stlwriter.write(root);	
}



void WorkThread::register_thread(ThreadPool *p)
{
	_p_threadpool = p;
}

void WorkThread::exec_task(Task task)
{
	Query query(5);

	if(!query.get_query_word(task.request))
	{
		sendto(_client_fd, "Please input query word", 24, 0, (struct sockaddr*)&task.client, sizeof(task.client));
	}
	else
	{
		const string word = query.get_query_result();
		string result = json_string(word);
		sendto(_client_fd, result.c_str(), result.size(), 0, (struct sockaddr*)&task.client, sizeof(task.client));

	}
}

