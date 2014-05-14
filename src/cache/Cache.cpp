#include "Cache.h"
#include "ThreadPool.h"
#include "SetTimer.hpp"
using namespace std;

Cache::Cache(const std::string &cache_path):_p_thread_pool(NULL), _cache_path("")
{
	_cache_path = cache_path;
		
	//ReadCache();//此处初始化的是线程池的cache,而Cache的cache是空的,该函数放在此处会出现段错误，应该放在
	//线程池的构造函数中
}

Cache::~Cache()
{

}

void Cache::run()
{
	struct timeval start;
	struct timeval end;
	SetTimer t;

	t.SetTime(start, 10);//记录当前时间和间隔时间
	while(1)
	{
		_p_thread_pool->ScanCache();//扫描工作线程,更新L2cache
		//轮训工作线程,更新L1_cache
		//每隔10分钟写一次文件
		if(t.CheckTime(start, 10) == 1)
		{
			WriteCache();
		}
	}
}	

void Cache::ReadCache(ThreadPool *p)
{
	string hash_key;
	string hash_value;
	string line;
	ifstream fin;
	char buf[256] = "";
	_p_thread_pool = p;

	fin.open(_cache_path.c_str());
	if(!fin.is_open())
	{
		sprintf(buf, "%s: %d\t Open cache file failed!", __FILE__, __LINE__);
		LOGGER_WRITE(Logger::ERROR, buf)
		throw runtime_error("Open cache file failed!");
	}

	sprintf(buf, "%s: %d\t Open cache file success", __FILE__, __LINE__);
	LOGGER_WRITE(Logger::INFO, buf)

	while(getline(fin,line))
	{
		int pos = line.find_first_of('\t');	
		hash_key = line.substr(0, pos);
		// int end = line.find_first_of('\n');//getline返回的string对象没有换行符,end=-1
		// hash_value = line.substr(pos+1, end-pos);//end作为参数时，表示字符串长度

		int len = line.size();
		hash_value = line.substr(pos+1, len-pos-1);
		cout << "key" << hash_key << " value" << hash_value << endl;;

		if(hash_key.size() != 0)
		{
			(_p_thread_pool->_pool_cache).insert(make_pair(hash_key, hash_value));
		}
	}

	sprintf(buf, "%s: %d\t Read cache file finished!", __FILE__, __LINE__);
	LOGGER_WRITE(Logger::INFO, buf)	
	
	fin.close();
	fin.clear();
}

void Cache::WriteCache()
{
	cout << "L2 size "<< this->_cache.size() << endl;
	// for(auto x = _cache.begin();  x != _cache.end(); ++x)		
	// {
	// 		cout << x->first << "\t";//打印cache,检查是否有更新
	// 		cout << x->second << endl;
	// 	}
		char buf[256] = "";	
		sprintf(buf, "%s: %d\t Write cache file ", __FILE__, __LINE__);
		LOGGER_WRITE(Logger::INFO, buf)	
		ofstream out(_cache_path, ios::app);
		if(out.is_open() && !_cache.empty())
		{
			for(auto x = _cache.begin();  x != _cache.end(); ++x)		
			{
				out << x->first << "\t" << x->second  << '\n';//getline识别
				cout << x->first << "\t" << x->second << endl;//打印cache,检查是否有更新
			}	
		}
	_cache.clear();//每次写完清空，保证下次追加的是工作线程中新插入的
	cout << "Write to cache file over" << endl;
	out.close();
	out.clear();
}