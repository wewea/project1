/*
 * EncodingConverter.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: haha
 */

#include "EncodingConverter.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

const int MAX_SIZE = 1000;

using namespace std;

EncodingConverter::EncodingConverter(const char* from, const char* to){
	_cd  = iconv_open(to, from);
	if((iconv_t)-1 == _cd)
	{
		throw std::runtime_error("open　iconv falied!");
	}
}

EncodingConverter::~EncodingConverter() {
	if(_cd)
	{
		iconv_close(_cd);
	}
}


std::string EncodingConverter::utf8_to_gbk(const std::string &s) {
	char *from = new char[s.size() + 1];
	std::strcpy(from, s.c_str());
	char *to = new char[MAX_SIZE];
	int from_len = strlen(from);
	int to_len = MAX_SIZE;
	//code_convert("utf-8", "gbk", from, from_len, to, to_len);
	translate(from, s.size()+1, to, MAX_SIZE);
	string ret(to);
	delete[] from;
	delete[] to;
	return ret;
}


std::string EncodingConverter::gbk_to_utf8(const std::string &s) {
	char *from = new char[s.size() + 1];
	std::strcpy(from, s.c_str());
	char *to = new char[MAX_SIZE];
	int from_len = strlen(from);
	int to_len = MAX_SIZE;
	translate(from, s.size()+1, to, MAX_SIZE);
	string ret(to);
	delete[] from;
	delete[] to;
	return ret;
}

size_t EncodingConverter::translate(char *src, size_t srclen, char *dest, size_t destlen )
{
	char ** inbuf = &src;
	char ** outbuf = &dest;
	memset(dest, 0, destlen);
	return iconv(_cd, inbuf, &srclen, outbuf, &destlen);
}

/*
 int main(int argc, char *argv[])
 {
 	
     string str = "我爱zhong国! ％＃＠＃";
     string str1 = "i大量需要转换的编码";
     string str2 = "函数就是用于将hello进行转换";
     
     EncodingConverter newtsp("UTF-8", "GBK");
     //以下内容重定向输出到1.txt是乱码，可通过命令iconv -f GBK -t UTF8 1.txt 输出1.txt的内容
     cout << newtsp.utf8_to_gbk(str) << endl;
     cout << newtsp.utf8_to_gbk(str1) << endl;
     cout << newtsp.utf8_to_gbk(str2) << endl;
  	

     //从gbk编码的文件读取内容转换位utf8后输出到终端
     ifstream fin(argv[1]);
     EncodingConverter trans("GBK", "UTF8");
     if(!fin.is_open())
     {
     	throw std::runtime_error("open input file falied!");
     }
     string line;
     while(!fin.eof())
     {
     	getline(fin, line);
     	cout <<	trans.gbk_to_utf8(line) << endl;
     }
     return 0;
 }*/