/*************************************************************************
	> File Name: ThreadPool.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 11时46分32秒
 ************************************************************************/

#include "ThreadPool.h"
using namespace std;
ThreadPool::ThreadPool(const std::string &cache_path, int num):_queue(), _max_thread(num),_thread_pool(_max_thread), _on(false),
 _lock(), _cond(_lock), _L2(cache_path)
{

	char buf[256] = "";
	std::vector<WorkThread>::iterator iter = _thread_pool.begin();
	for(; iter!=_thread_pool.end(); ++iter)
	{
		iter->register_thread(this);//初始化工作线程的cache,并让工作线程，注册Cache对象和线程池
	}
	/*_L2(this, cache_path);Cache做为ThreadPool的私有成员，需要在初始化列表初始化，编译通过，
	但链接时会提示没有无参构造函数匹配，因为自定义了有参的构造函数*/

	_L2.ReadCache(this);//注册线程池到Cache
	_L2.start();//启动cache管理类，主要负责轮询线程，并将工作线程更新的cache,追加入文件中
	sprintf(buf, "%s: %d\t ThreadPool Register", __FILE__, __LINE__);
	LOGGER_WRITE(Logger::INFO, buf)

}

ThreadPool::~ThreadPool()
{
	stop_pool();
}

void ThreadPool::start_pool()
{
	char buf[256] = "";
	if(!_on)
	{
		_on = true;
		std::vector<WorkThread>::iterator iter = _thread_pool.begin();
		for(; iter!=_thread_pool.end(); ++iter)
		{
			iter->start();//启动工作线程，工作线程的cache在run函数被线程池cache初始化
		}
	}
	sprintf(buf, "%s: %d\t ThreadPool Start", __FILE__, __LINE__);
	LOGGER_WRITE(Logger::INFO, buf)
}

void ThreadPool::stop_pool()
{
	if(!_on)
	{
		return ;
	}
	_cond.notify_all();
	std::vector<WorkThread>::iterator iter = _thread_pool.begin();
	for(; iter!=_thread_pool.end(); ++iter)
	{
		iter->join();
	}
	while(!_queue.empty())
	{
		_queue.pop();
	}
}

bool ThreadPool::add_task(Task task)
{
	//cout << "add task" << endl;
	MutexGuard mutex(_lock);
	bool ret = false;
	if(_on)
	{
		_queue.push(task);
		_cond.notify();
		ret = true;
		char buf[256] = "";
		sprintf(buf, "%s: %d\t Add Task %s", __FILE__, __LINE__, task.request.c_str());
		LOGGER_WRITE(Logger::INFO, buf)
	}
	//cout << "add task end" << endl;
	return ret;
}

bool ThreadPool::get_task(Task &task)
{
	//cout << "get task" << endl;
	MutexGuard mutex(_lock);
	while(_on && _queue.empty())
	{
		_cond.wait();
	}
	if(!_on)
	{
		_lock.unlock();
		return false;
	}
	task = _queue.front();
	_queue.pop();
	//cout << "get task end" << endl;
	return true;
}

void  ThreadPool::ScanCache()
{
	//cout << "ScanCache" << endl;
	auto iter = _thread_pool.begin();

	for(; iter != _thread_pool.end(); ++iter)
	{

		/*auto iter_ix = (iter->_L1_cache).begin();
		for(; iter_ix != (iter->_L1_cache).end(); ++iter_ix)
		{
			auto iter_iy = L2._cache.find(iter_ix->first);	
			//注意此处的判断条件，找不到是返回end迭代器
			if(iter_iy == L2._cache.end())
			{//插入的是线程的元素,find谁的就插入谁的
				L2._cache.insert(make_pair(iter_ix->first, iter_ix->second));			
			}
		}

		//更新线程池cache
		auto it_a = L2._cache.begin();
		for(; it_a != L2._cache.end(); ++it_a)
		{
			auto it_b = (iter->_L1_cache).find(it_a->first);
			if(it_b == (iter->_L1_cache).end())
			{
				(iter->_L1_cache).insert(make_pair(it_a->first, it_a->second));//找不到才更新Ｌ１
			}
		}*/
		//以上代码进行封装	
		//iter->cache表示工作线程的cache, _pool_cache表示线程池的cache
		UpDate(iter->_cache, _pool_cache);
		UpDate(_pool_cache, iter->_cache);	
	}
}

void ThreadPool::UpDate(std::unordered_map<string, string> &L1,
  std::unordered_map<string, string> &L2)
{
	auto iter_ix = L1.begin();
	for(; iter_ix != L1.end(); ++iter_ix)
	{
		//遍历Ｌ１在Ｌ２中找Ｌ１－＞ｆｉｒｓｔ，找不到则插入Ｌ２
		auto iter_iy = L2.find(iter_ix->first);
		if(iter_iy == L2.end())
		{
			L2.insert(make_pair(iter_ix->first, iter_ix->second));
		}
	}
}
