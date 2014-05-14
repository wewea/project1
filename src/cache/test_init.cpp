/*************************************************************************
	> File Name: test_init.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月08日 星期四 13时52分54秒
 ************************************************************************/

#include <iostream>

#include "Init.h"
using namespace std;

int main(int argc, char* argv[])
{
	string conf_path = argv[1];
	string log_path = argv[2];

	Init in(conf_path);
	string ip = in.ip();
	string dict_data = in.dict_read();
	string dict_file = in.dict_write();
	string port = in.port();
	
	cout << dict_data << endl;
	cout << dict_file << endl;
	cout << ip << endl;
	cout << port << endl;;

}

