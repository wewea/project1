#include "Init.h"
Mutex Config::_mutex;
Config* Config::_p_instance = NULL;

using namespace std;

Init::Init(const string&conf_path):_tag_ip("ServerName"), _tag_port("ServerPort"), _tag_dict_read("DictData"),
_tag_dict_write("DictFile"), _tag_thread_pool("ThreadPool") , _tag_log_severity("Severity"),
_tag_return_num("Return"), _tag_gbk("GBK")
{
	std::ifstream input;
	char buf[256] = "";
	Config *conf_file = Config::get();

	sprintf(buf, "%s: %d\t System Init...", __FILE__, __LINE__);
	LOGGER_WRITE(Logger::INFO, buf)	
	input.open(conf_path.c_str());
	if(!input.is_open())
	{
		sprintf(buf, "%s: %d\t Open config file failed!", __FILE__, __LINE__);
		LOGGER_WRITE(Logger::ERROR, buf)
		std::runtime_error("Open config failed");
	}
	else
	{
		sprintf(buf, "%s: %d\t Open config file success!", __FILE__, __LINE__);
		LOGGER_WRITE(Logger::INFO, buf)
	}


	_conf_map = conf_file->parseFile(input);
	sprintf(buf, "%s: %d\t Parse config file finished.", __FILE__, __LINE__);
	LOGGER_WRITE(Logger::INFO, buf)	

	

	input.close();
	input.clear();	

}

std::string Init::find_path(std::string & tag)
{
	std::map<string, string>::iterator iter_conf = _conf_map.find(tag);
	std::string ret = "";
	if(iter_conf != _conf_map.end())
	{
		ret = iter_conf->second;
	}
	return ret;
}

std::string Init::dict_write()
{
	return find_path(_tag_dict_write);
}

std::string Init::dict_read()
{
	return find_path(_tag_dict_read);
}

std::string Init::ip()
{

	return find_path(_tag_ip);
}

std::string Init::port()
{
	return find_path(_tag_port);	
}

std::size_t Init::thread_pool()
{
//	
	size_t num =  atoi(find_path(_tag_thread_pool).c_str());
	return num;
}

std::string Init::severity()
{
	return find_path(_tag_log_severity);
}

std::size_t Init::return_num()
{
//	
	size_t num =  atoi(find_path(_tag_return_num).c_str());
	return num;
}

std::string Init::gbk()
{
	return find_path(_tag_gbk);
}