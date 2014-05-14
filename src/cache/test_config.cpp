/*************************************************************************
	> File Name: Config.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月05日 星期一 00时28分07秒
 ************************************************************************/


#include "Config.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <map>
#include <algorithm>
using namespace std;
//Config& Config::_instance;

void print(std::map<std::string, std::string>::value_type &s)
{
	cout << "addr:" << s.first << " path:" << s.second << endl;
}

int main(int argc, char *argv[])
{
	std::ifstream input;
	map<string, string> conf_map;	
	Config& conf = Config::get();
	if(conf.open_file(input, argv[1]))
	{
		std::runtime_error("open config failed!");
	}
	conf_map = conf.parseFile(input);
	for_each(conf_map.begin(), conf_map.end(),print);

	
}
