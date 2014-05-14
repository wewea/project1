/*************************************************************************
	> File Name: Init.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月08日 星期四 10时50分35秒
 ************************************************************************/

#ifndef _INIT_H_
#define _INIT_H_

#include <map>
#include <stdexcept>
#include <string>

#include "Config.h"
#include "Logger.h"
#include "noncopyable.h"
class Init : public noncopyable
{
	public:
		Init(const std::string &);
		std::string FindPath(std::string & tag);
		std::string IP();
		std::string Port();
		std::string DictRead();
		std::string DictWrite();
		std::size_t ThreadPool();
		std::string Severity();
		std::size_t	ReturnNum();
		std::string GBK();
		std::string Cache();
	private:
		std::string _tag_ip;
		std::string _tag_port;
		std::string _tag_dict_read;
		std::string _tag_dict_write;
		std::string _tag_thread_pool;
		std::string _tag_log_severity;
		std::string _tag_return_num;
		std::string _tag_gbk;
		std::string _tag_cache;
		std::map<std::string,std::string> _conf_map;	

};

#endif

