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

WorkThread::WorkThread():_p_threadpool(NULL),_tid(0)
{
  _client_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(_client_fd == -1)
	{	
		std::runtime_error("socket failed!");
	}
}


void WorkThread::run()
{
	_cache = _p_threadpool->_pool_cache;//线程开始执行，使用线程池cache初始化,工作线程
	while(1)
	{
		Task task;
		if(!_p_threadpool->get_task(task))
		{
			break;
		}
		char buf[256] = "";
		_tid = pthread_self();
		sprintf(buf, "%s: %d\t %lu Get Task %s", __FILE__, __LINE__, _tid,
		task.request.c_str());
		LOGGER_WRITE(Logger::INFO, buf)
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

	size_t index = 1;
	while(ss >> buf)
	{
		//定义一个临时变量，elem
		Json::Value elem ;
		char title[128] = "";
		char summary[128]="";
		//用随即数生成两个格式化的字符串
		sprintf(title , "tile_%d", index);
		sprintf(summary, "%d: %s", index,buf.c_str());
		//将两个字符串，赋给elem的两个键
		elem["title"] = title ;
		elem["candicate"] = summary ;
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
	_p_threadpool = p;//注册线程池
}


void  Trim(string &s)
{
	istringstream ss(s);			
	string buf;
	string ret;
	s.clear();
	while(ss >> buf)
	{
		s.append(buf);
	}
	ss.clear();

	for(auto &x : s)
	{
		if(isupper(x))
		{
			x += 32;
		}
	}
}

void WorkThread::exec_task(Task task)
{
	cout << "exec_task" << endl;
	Query query(5);
	string data;
	string trim_word = "";
	char buf[256] = "";
	Trim(task.request);	
	query.GetQueryWord(task.request);
		//去空格处理
	
	
	cout << "trim : " << task.request << endl;

	auto iter = _cache.find(task.request);	
	if(iter != _cache.end())
	{
		sprintf(buf, "%s: %d\t Find the [%s] in cache.", __FILE__, __LINE__, iter->first.c_str());
		LOGGER_WRITE(Logger::INFO, buf)

			data = _cache[iter->first];//当在cache中找到查询词的key时,返回其data

			sprintf(buf, "%s: %d\t Cache Candicate :[%s]", __FILE__, __LINE__, data.c_str());
			LOGGER_WRITE(Logger::INFO, buf)

			cout << "found in cache print work cache" << endl;
			for(auto x = _cache.begin(); x != _cache.end(); ++x )
			{
				cout << "workcache " << x->first << " " << x->second << endl;
			}
		}
		else
		{
			sprintf(buf, "%s: %d\t Could not find [%s] in cache.", __FILE__, __LINE__, (task.request).c_str());
			LOGGER_WRITE(Logger::INFO, buf)

			data = query.GetResult(); 

			_cache.insert(make_pair(task.request, data));//当在cache中找不到时,再到索引中查询,并更新cache

			_p_threadpool->_L2._cache.insert(make_pair(task.request, data));

			cout << "no found in cache print work cache" << endl;
			for(auto x = _cache.begin(); x != _cache.end(); ++x )
			{
				cout << "workcache " << x->first << " " << x->second << endl;
			}
		}
		string result = json_string(data);//将结果格式化为json字符串,返回前台
		cout << "Before send word" << endl;
		sendto(_client_fd, result.c_str(), result.size(), 0, (struct sockaddr*)&task.client, sizeof(task.client));
		

		//cout << "exec_task end" << endl;//测试,此函数内段错误
	}

