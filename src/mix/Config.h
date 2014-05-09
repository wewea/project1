/*************************************************************************
	> File Name: Config.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月05日 星期一 00时25分38秒
 ************************************************************************/

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "Mutex.h"
	class Config
	{
	public:
		static Config* get()
		{
			if(_p_instance == NULL)
			{
				_mutex.lock();
				if(_p_instance == NULL)
				{
					_p_instance = new Config;
				}
			}
				_mutex.unlock();
			return _p_instance;
		}

		std::map<std::string, std::string> parseFile(std::ifstream& in)
		{
			std::string buf1, buf2;
			std::string line;
			while(!in.eof())
			{
				//in >> buf1 >> buf2;
				getline(in, line);
				std::istringstream ss(line);
				if(line[0] != '#')
				{
					
					ss >> buf1 >> buf2;
					_store[buf1] = buf2;
				}
				ss.clear();
			}
			return _store;
		}

	private:
		static Mutex _mutex;
		Config(){};
		Config(const Config&);
		Config& operator=(const Config&);
		static Config *_p_instance;
		std::map<std::string,std::string> _store;
	};

#endif

