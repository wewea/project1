	/*************************************************************************
	> File Name: Dict.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 15时46分33秒
 ************************************************************************/


#include "Dict.h"
using namespace std;
std::map<std::string, int> Dict::_dict;

Dict::Dict(string read_path, string write_path)
{
	char buf[256]="";		
	try	
	{
	if(!read_file(read_path))
	{
		throw std::runtime_error("Failed to read dict source file");
	}
	}catch(std::runtime_error& e)
	{
		cout << e.what() << endl;
		sprintf(buf, "%s: %d\t Fail to read dict source file!", __FILE__, __LINE__);
		LOGGER_WRITE(Logger::INFO, buf)
		cout << e.what() << endl;
	}

	//
	try
	{
	if(!write_file(write_path))
	{
		throw std::runtime_error("Could not find DictFile path!");
	}
	}catch(std::runtime_error& e)
	{

		cout << e.what() << endl;
		char buf[256]="";
		sprintf(buf, "%s: %d\t Could not find DictFile path", __FILE__, __LINE__);
		LOGGER_WRITE(Logger::ERROR, buf)
	}
}

Dict::~Dict()
{
	LOGGER_WRITE(Logger::INFO, "Dict destroy")
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

bool Dict::read_file(const std::string &file_name)
{
	ifstream in;
	char *buf = new char[LINELEN];
	if(!open_file(in, file_name))
	{
		return false;
	}

	cout << "Dict loading..." << endl;
	sprintf(buf, "%s: %d\t Start read dict source file.", __FILE__, __LINE__);
	LOGGER_WRITE(Logger::INFO, buf)

	string line;
	while(getline(in, line))
	{
		//strdup()会先用maolloc()配置与参数s 字符串相同的空间大小，然后将参数s 字符串的内容复制到该内存地址，然后把该地址返回。该地址最后可以利用free()来释放。
		buf = strdup(line.c_str());
		getword(buf);
	}

	//for_each(_dict.begin(), _dict.end(), print);//print dict_map
	cout << "Dict load over" << endl;
	delete[] buf;
	in.close();
	in.clear();
	return true;
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

bool Dict::write_file(const std::string &dict_file)
{
	ofstream out; 
	char buf[256]="";
	if(!output_file(out, dict_file))
	{
		return false;
	}
	sprintf(buf, "%s: %d\t Start write dict to file.", __FILE__, __LINE__);
	LOGGER_WRITE(Logger::INFO, buf)
	map<string, int>::iterator iter = _dict.begin();
	for(; iter!=_dict.end(); ++iter)
	{
		out << iter->first  << "\t" << iter->second << endl;
	}
	std::runtime_error("write dict map to DictFile success");
	sprintf(buf, "%s: %d\t Open DictFile failed!", __FILE__, __LINE__);

	out.close();	
	out.clear();
	return true;
}
