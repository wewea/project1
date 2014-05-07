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
#include <unistd.h>


#include "Config.h"
#include "Logger.h"
#define LINELEN 1024*1024

class Dict
{
	public:
		Dict(std::string, std::string);
		~Dict();
		std::ifstream &open_file(std::ifstream &is, const std::string &file);
		std::ofstream &output_file(std::ofstream & out, const std::string &filename);
		void read_file( const std::string &);
		void write_file(std::string &dict_file);
		void getword( char *buf);
		std::string get_dict_path()const;

	    static void print(std::map<std::string, int>::value_type s);
		void to_lower(char **src);
	private:
		std::map<std::string, int> _dict;
		std::string _attr_data;
		std::string _attr_dict;
		std::string _dict_path;

		

};
#endif

