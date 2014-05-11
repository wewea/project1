/*************************************************************************
	> File Name: ThreadPool.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 11时46分32秒
 ************************************************************************/

#include "ThreadPool.h"
using namespace std;
ThreadPool::ThreadPool(int num):_queue(), _max_thread(num),_thread_pool(_max_thread), _on(false), _lock(), _cond(_lock)
{
	std::vector<WorkThread>::iterator iter = _thread_pool.begin();
	for(; iter!=_thread_pool.end(); ++iter)
	{
		iter->register_thread(this);
	}
}

ThreadPool::~ThreadPool()
{
	stop_pool();
}

void ThreadPool::start_pool()
{
	if(!_on)
	{
		_on = true;
	std::vector<WorkThread>::iterator iter = _thread_pool.begin();
	for(; iter!=_thread_pool.end(); ++iter)
	{
		iter->start();
	}
	}
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

//	_lock.lock();
	MutexGuard mutex(_lock);
	bool ret = false;
	if(_on)
	{
		_queue.push(task);
		_cond.notify();
		ret = true;
	}
	//_lock.unlock();
	return ret;
}

bool ThreadPool::get_task(Task &task)
{
	//_lock.unlock();
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
	//_lock.unlock();
	return true;
}

