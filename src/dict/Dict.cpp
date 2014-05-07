/*************************************************************************
	> File Name: Dict.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 15时46分33秒
 ************************************************************************/


#include "Dict.h"
using namespace std;

Dict::Dict(string conf_path, string log_path):_attr_data("DictData"), _attr_dict("DictFile"),_dict_path("")
{
	ifstream input;	
	map<string, string> conf_map;
	//打开日志
	LOGGER_START(Logger::INFO, log_path) 
	//获得Config类的实例，注意引用并不是对象
	char buf[256]="";	
	Config &conf_file = Config::get();	
	if(!open_file(input, conf_path))
	{
		
		sprintf(buf, "FILE:%s LINE:%d\tOpen config file failed!", __FILE__, __LINE__);
		LOGGER_WRITE(Logger::ERROR, buf)
		std::runtime_error("Open config failed");
	}
	else
	{
		sprintf(buf, "FILE:%s LINE:%d\tOpen config file success!", __FILE__, __LINE__);
		LOGGER_WRITE(Logger::INFO, buf)
	}

	
	conf_map = conf_file.parseFile(input);
	sprintf(buf, "FILE:%s LINE:%d\tParse config file finished.", __FILE__, __LINE__);
	LOGGER_WRITE(Logger::INFO, buf)	
	map<string, string>::iterator iter_conf = conf_map.find(_attr_data);

	//读取词典原数据
	try	
	{
	if(iter_conf != conf_map.end())
	{

		sprintf(buf, "FILE:%s LINE:%d\tStart read dict source file.", __FILE__, __LINE__);
		LOGGER_WRITE(Logger::INFO, buf)
		read_file(iter_conf->second);
	}
	else
	{
		throw std::runtime_error("Failed to read dict source file");
	}
	}
	catch(std::runtime_error& e)
	{

		sprintf(buf, "FILE:%s LINE:%d\tFail to read dict source file!", __FILE__, __LINE__);
		LOGGER_WRITE(Logger::INFO, buf)
		cout << e.what() << endl;
	}


	iter_conf = conf_map.find("DictFile");	
	try
	{
	if(iter_conf != conf_map.end())
	{
		sprintf(buf, "FILE:%s LINE:%d\tStart write dict to file.", __FILE__, __LINE__);
		LOGGER_WRITE(Logger::INFO, buf)
		_dict_path = iter_conf->second;
		write_file(iter_conf->second);
	}
	else
	{
		throw std::runtime_error("Could not find DictFile path!");
	}
	}catch(std::runtime_error& e)
	{

		cout << e.what() << endl;
		char buf[256]="";
		sprintf(buf, "FILE:%s LINE:%d\tCould not find DictFile path", __FILE__, __LINE__);
		LOGGER_WRITE(Logger::ERROR, buf)
	}

	

	input.close();
	input.clear();	
}

Dict::~Dict()
{
	LOGGER_WRITE(Logger::END, "Log record end\n\n")
	LOGGER_STOP()
}

ifstream &Dict::open_file(ifstream &is, const string &file)
{
	is.close();
	is.clear();
	is.open(file.c_str());
	return is;
}

ofstream & Dict::output_file(ofstream & out, const string &filename)
{
	out.close();	
	out.clear();
	out.open(filename.c_str());
	return out;
}

void Dict::read_file(const std::string &file_name)
{
	ifstream in;
	char *buf = new char[LINELEN];
	if(!open_file(in, file_name))
	{
		std::runtime_error("open failed!");
	}
	string line;
	while(getline(in, line))
	{
		//strdup()会先用maolloc()配置与参数s 字符串相同的空间大小，然后将参数s 字符串的内容复制到该内存地址，然后把该地址返回。该地址最后可以利用free()来释放。
		buf = strdup(line.c_str());
		getword(buf);
	//	cout << buf << endl;
	//	putchar(10);
	}
	for_each(_dict.begin(), _dict.end(), print);
	cout << "read over" << endl;
	delete[] buf;
	in.close();
	in.clear();

}
void Dict::getword(char *line)
{
	//char buffer[LINELEN];
	char *token;
	char delim[] = "~\t\n!@#$%^&*();:_+[]-={}<>,./?|`1234567890 \" \' \0 \\"; 
		
	for(token=strtok(line, delim);token != NULL; token=strtok(NULL, delim))
	{
		if(strlen(token) == 1)
		{
			continue;
		}
		to_lower(&token);
		pair<map<std::string ,int>::iterator, bool> ret =
			_dict.insert(map<string, int>::value_type(token, 1));
		//注意操作符的使用
			++ret.first->second;
	}
}

void Dict::to_lower(char **src)
{
	for(size_t ix=0; ix!=strlen(*src); ++ix)
	{
		if((*src)[ix] >= 'A' && (*src)[ix] <= 'Z')
		{
			(*src)[ix] += 32;
		}
	}
}


void Dict::print(std::map<std::string, int>::value_type s)
{
	//此处用.操作赋
	cout << s.first << "\t" << s.second << endl;
}

void Dict::write_file(string &dict_file)
{
	ofstream out; 
	char buf[256]="";
	if(!output_file(out, dict_file))
	{
		std::runtime_error("open dict file failed!");
		sprintf(buf, "FILE:%s LINE:%d\tOpen DictFile failed!", __FILE__, __LINE__);
		LOGGER_WRITE(Logger::ERROR, buf)
	}
	map<string, int>::iterator iter = _dict.begin();
	for(; iter!=_dict.end(); ++iter)
	{
		out << iter->first  << "\t" << iter->second << endl;
	}
	std::runtime_error("write dict map to DictFile success");
	sprintf(buf, "FILE:%s LINE:%d\tOpen DictFile failed!", __FILE__, __LINE__);

	out.close();	
	out.clear();
}

std::string Dict::get_dict_path()const
{
	return _dict_path;
}