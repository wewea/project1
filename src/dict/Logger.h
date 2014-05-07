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
#include <iostream>

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define LOGGER_START(MIN_PRIORITY, FILE) Logger::Start(MIN_PRIORITY, FILE);
#define LOGGER_STOP() Logger::Stop();
#define LOGGER_WRITE(PRIORITY, MESSAGE) Logger::Write(PRIORITY, MESSAGE);

class Logger
{
public:
	enum Priority
	{
		INFO,
		WARNING,
		ERROR,
		DEBUG,
		CONFIG,
		END,
	};
	
	public:
		static void Start(Priority min_priority, const std::string &logfile);
		static void Stop();
		static void Write(Priority priority, const std::string &message);
		void get_time();
	private:
		Logger();
		Logger(const Logger&){}
		Logger& operator= (const Logger &logger){}
	
		bool _active;
		std::ofstream _file_stream;
		Priority _min_priority;
		std::string _time;

		static const std::string PRIORITY_NAMES[];
		static Logger instance;

};


#endif


