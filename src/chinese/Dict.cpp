	/*************************************************************************
	> File Name: Dict.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 15时46分33秒
 ************************************************************************/


#include "Dict.h"
using namespace std;
std::vector<std::pair<std::string, int> > Dict::_dict;
std::map<uint16_t, std::set<int> > Dict::_index;

Dict::Dict(string read_path)
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
	/*try
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
	}*/
}

Dict::~Dict()
{
	LOGGER_WRITE(Logger::INFO, "Dict destroy")
	LOGGER_STOP()
}

bool is_gbk_first_alpha(unsigned char c)
{
	return c >= 0x81 && c <= 0xFE;
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

void print_dict(std::pair<std::string, int> &s)
{
	//此处用.操作赋
	cout << s.first << "\t" << s.second << endl;
}

void print_set(int x)
{
	cout << x << " " ;
}

void print_index(std::map<uint16_t, std::set<int> >::value_type &s)
{
	cout << s.first << "\t\t";
	for_each(s.second.begin(), s.second.end(), print_set);
	cout << "\n\n" << endl;
}

bool Dict::read_file(const std::string &file_name)
{
	ifstream in;
	int sub = 0;
	string line;
	EncodingConverter trans("UTF8", "GBK");
	char *buf = new char[LINELEN];
	if(!open_file(in, file_name))
	{
		return false;
	}

	cout << "Dict loading..." << endl;
	sprintf(buf, "%s: %d\t Start read dict source file.", __FILE__, __LINE__);
	LOGGER_WRITE(Logger::INFO, buf)

	while(!in.eof())
	{
		getline(in, line);
		string ret = trans.utf8_to_gbk(line);
		istringstream ss(ret);
		string key;
		int frequence; 
		ss >> key >> frequence;
		_dict.push_back(make_pair(key, frequence));
		//cout << line << " ";
		//判断首字节是否为汉字,两种判断方法
		//if((unsigned char)key[0] & 0x80) //char 为signed类型是负值
		if(is_gbk_first_alpha(key[0]))
		{
			for(std::string::size_type ix = 0; ix != key.size(); ix += 2)
			{
				unsigned char c1 = key[ix];
				unsigned char c2 = key[ix+1];
				uint16_t tmp = (c1 << 8) + c2;
				_index[tmp].insert(sub);
				//cout << tmp << " ";
			}
		}
		else
		{
			for(int ix = 0; ix != key.size(); ++ix)
			{
				uint16_t tmp = (uint16_t)(unsigned char)(key[ix]);
				_index[tmp].insert(sub);
				//cout << tmp << " ";
			}
		}
		++ sub;
	}
	//for_each(_dict.begin(), _dict.end(), print_dict);//print dict_vector
	//for_each(_index.begin(), _index.end(), print_index);//print _index
	cout << "Dict load over" << endl;
	cout << "sub" << " " << sub << endl;
	delete[] buf;
	in.close();
	in.clear();
	return true;
}

/*
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
}*/

/*void Dict::to_lower(char **src)
{
	for(size_t ix=0; ix!=strlen(*src); ++ix)
	{
		if((*src)[ix] >= 'A' && (*src)[ix] <= 'Z')
		{
			(*src)[ix] += 32;
		}
	}
}
*/
//map词典　打印
/*void Dict::print(std::map<std::string, int>::value_type s)
{
	//此处用.操作赋
	cout << s.first << "\t" << s.second << endl;
}
*/

/*bool Dict::write_file(const std::string &dict_file)
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
*/