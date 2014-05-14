/*************************************************************************
	> File Name: Dict.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 16时37分05秒
 ************************************************************************/


#ifndef _DICT_H_
#define _DICT_H_


#include <fstream>
#include <sstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <set>
#include <map>

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>


#include "Config.h"
#include "Logger.h"
#include "EncodingConverter.h"

#define LINELEN 1024*1024
class Query;
class Dict
{
	friend class Query;
	public:
		Dict(const std::string&);
		~Dict();
		std::ifstream &open_file(std::ifstream &is, const std::string &file);
		std::ofstream &output_file(std::ofstream & out, const std::string &filename);
		bool read_file(const std::string &);

	private:
		static std::vector<std::pair<std::string, int> > _dict;
		static std::map<uint16_t, std::set<int> > _index;

};
#endif

