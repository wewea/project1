#ifndef _CACHE_H_
#define _CACHE_H_

#include <fstream>
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <set>
#include <pthread.h>
//#include "SetTimer.hpp"
#include "Logger.h"
#include "Thread.h"
class ThreadPool;
class Cache : public Thread
{
	friend class ThreadPool;
	friend class WorkThread;//让工作线程访问该类对象的_cache, 以便出事化工作线程cache, 及
	//在插入新查询词时，更新L2 chche,每次,因此L2只插入新的查询词，追加写入cache文件后，清空cache，
	//这样就能保证每次追加的内容都是最新的．
public:
	Cache(const std::string &cache_path);
	~Cache();
	void ReadCache(ThreadPool *p);
	void WriteCache();
	void run();
private:
	pthread_t _tid;
	ThreadPool *_p_thread_pool;
	std::string _cache_path;
	std::unordered_map<std::string, std::string> _cache; 
};

#endif