/*************************************************************************
	> File Name: Logger.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月06日 星期二 15时19分53秒
 ************************************************************************/

#include "Logger.h"

using namespace std;

//attention:initialization
Logger Logger::instance;
Mutex Logger::_mutex;
Logger::Logger():_active(false), _tid(0), _time(""), _logfile(""), _min_priority(""){
	
}

const std::string Logger::PRIORITY_NAMES[] = {
	"[CONFIG]",
	"[INFO]",
	"[WARNING]",
	"[ERROR]",
	"[DEBUG]",
	"[END]",

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

void Logger::Start(const std::string &logfile)
{
	instance._logfile = logfile;//must before pthread start
	pthread_create(&instance._tid, NULL, thread_func, NULL);
}

void Logger::Severity(const std::string &min)
{
	instance._min_priority = min;
}

void Logger::Stop()
{
	instance._active = false;
	if(instance._file_stream.is_open())
	{
		instance._file_stream.close();
	}
	pthread_join(instance._tid, NULL);
}

void Logger::Write(Priority priority, const std::string &message)
{
	MutexGuard lock(_mutex);
	if(instance._active)
	{
		instance.get_time();
		string buf;
		ostringstream ss;
		ss  <<PRIORITY_NAMES[priority]
			<< ": "
			<< instance._time + '\t'
			<< message
			<< endl;

		instance._queue.push(ss.str());
		ss.clear();
	}
}


void* Logger::thread_func(void *arg)
{

	instance._active = true;
	
	//string min_priority = instance._min_priority;
	//cout << min_priority << endl;

	if(instance._logfile != "")
	{
	instance._file_stream.open(instance._logfile.c_str(), ios::app|ios::out);
	instance.get_time();
	instance._file_stream << "Start write "+ instance._time << '\n'
		<< "===============================" << endl;
	 while(instance._active)
	 {
		while(!instance._queue.empty())	
		{
			string input = instance._queue.front();
			std::size_t found = input.find_first_of(":");
			string pri = input.substr(0, found);
			 if(distance(find(PRIORITY_NAMES, PRIORITY_NAMES+6,instance._min_priority),
			 	find(PRIORITY_NAMES, PRIORITY_NAMES+6,  pri)) >= 0)
			{
				instance._file_stream << input;
			}
			instance._queue.pop();
		}
	 }
}
	else
	{
		throw std::runtime_error("logfile invalid!");
	}
}


