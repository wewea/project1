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

	class Config
	{
	public:
		static Config& get()
		{
			static Config _instance;
			return _instance;
		}
		std::map<std::string, std::string> parseFile(std::ifstream& in)
		{
			std::string buf1, buf2;
			while(!in.eof())
			{
				in >> buf1 >> buf2;
				if(buf1[0] != '#')
				{
					store[buf1] = buf2;
				}
			}
			return store;
		}

	private:
		Config(){};
		
		Config(const Config&);
		Config& operator=(const Config&);
		std::map<std::string,std::string> store;
	};

#endif

