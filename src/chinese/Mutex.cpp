/*************************************************************************
	> File Name: Mutex.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 10时41分54秒
 ************************************************************************/

#include "Mutex.h"
using namespace std;

Mutex::Mutex()
{
	pthread_mutex_init(&_mutex, NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&_mutex);
}

void Mutex::lock()
{
	pthread_mutex_lock(&_mutex);
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&_mutex);
}
