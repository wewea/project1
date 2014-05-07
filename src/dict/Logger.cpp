/*************************************************************************
	> File Name: Logger.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月06日 星期二 15时19分53秒
 ************************************************************************/

#include "Logger.h"

using namespace std;

//initialization
Logger Logger::instance;
Logger::Logger():_active(false){}

const std::string Logger::PRIORITY_NAMES[] = {
	"[INFO]",
	"[WARNING]",
	"[ERROR]",
	"[DEBUG]",
	"[CONFIG]",
	"[END]"
};

void Logger::get_time()
{
	time_t nowtime;
	nowtime = time(NULL);	

	struct tm *local;
	local = localtime(&nowtime);
	char buf[80];
	strftime(buf, 80, "%Y-%m-%d %H:%M:%S", local);
	instance._time = buf;
}

void Logger::Start(Priority priority, const std::string &logfile)
{
	instance._active = true;
	instance._min_priority = priority;	
	if(logfile != "")
	{
	instance._file_stream.open(logfile.c_str(), ios::app|ios::out);
	instance.get_time();
	instance._file_stream << "Start write "+ instance._time << '\n'
		<< "===============================" << endl;
	}
}
void Logger::Stop()
{
	instance._active = false;
	if(instance._file_stream.is_open())
	{
		instance._file_stream.close();
	}
}

void Logger::Write(Priority priority, const std::string &message)
{
	if(instance._active && priority >= instance._min_priority)
	{
		std::ostream &stream= instance._file_stream.is_open() ? instance._file_stream : std::cout ;
		stream << PRIORITY_NAMES[priority]
			<< ": "
			<< instance._time + '\t'
			<< message
			<< endl;
	}
}
