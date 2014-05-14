/*************************************************************************
	> File Name: Logger.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月06日 星期二 14时45分44秒
 ************************************************************************/

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iterator>
#include <queue>
#include <algorithm>
#include <stdexcept>

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "Mutex.h"

#define LOGGER_START(FILE) Logger::Start( FILE);
#define LOGGER_STOP() Logger::Stop();	
#define LOGGER_WRITE(PRIORITY, MESSAGE) Logger::Write(PRIORITY, MESSAGE);
#define LOGGER_SEVERTIY(PRIORITY) Logger::Severity(PRIORITY);

class Logger 
{
public:
	enum Priority
	{
		CONFIG,
		INFO,
		WARNING,
		ERROR,
		DEBUG,
		END,
	};
	
	public:
		static void Start(const std::string &logfile = "");
		static void Stop();
		static void Write(Priority priority, const std::string &message);
		static void Severity(const std::string &min = std::string("[INFO]"));
		static void *thread_func(void *arg);
/*		static Logger& Instance()
		{
			
    		return instance;

		}*/
		void get_time();
	private:
		Logger();
		Logger(const Logger&){}
		Logger& operator= (const Logger &logger){}
		
	
		bool _active;
		pthread_t _tid;
		std::ofstream _file_stream;
		std::string _time;
		std::string _logfile;
		std::queue<std::string> _queue;
		std::string _min_priority;
		static Logger instance;
		static Mutex _mutex;	
		static const std::string PRIORITY_NAMES[];
		
};


#endif


