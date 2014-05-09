/*************************************************************************
	> File Name: Query.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月06日 星期二 20时48分14秒
 ************************************************************************/

#include <queue>
#include "Query.h"
using namespace std;
Query::Query(int num):_query_word(""), _query_result(""), _result_num(num)
{
}

bool Query::get_query_word(const std::string &request)
{
	string query_word = request;
	if(query_word == "")
	{
		return false;
	}
	else
	{
	for(size_t ix=0; ix != query_word.size(); ++ix)
	{
		if(query_word[ix] >= 'A' && query_word[ix] <= 'Z')
		{
			query_word[ix] += 32;
		}
	}
	char buf[256]="";
	sprintf(buf, "%s: %d\t Start query word [%s]", __FILE__, __LINE__, query_word.c_str());
	LOGGER_WRITE(Logger::INFO, buf)
	_query_word = query_word;
	get_query_result();
	sprintf(buf, "%s: %d\t Return result of [%s]", __FILE__, __LINE__, query_word.c_str());
	LOGGER_WRITE(Logger::INFO, buf)
	return true;
	}
}


void Query::get_dict_map(std::ifstream &in)
{
	string buf;
	int tmp;
	while(!in.eof())
	{
		in >> buf >> tmp;
		_dict_map[buf] = tmp;
	}
}

std::string Query::get_query_result()
{
	std::priority_queue<EditDist> queue;

	int ed;
	std::map<string , int>::iterator iter = Dict::_dict.begin();
	for(; iter != Dict::_dict.end(); ++iter)
	{
		string key = iter->first;
		ed = get_edit_distance(key, _query_word);
		EditDist temp(iter->first, iter->second, ed);
		queue.push(temp);
	}
	int num = _result_num;
	string ret = "";
	while(!queue.empty() && num != 0)
	{ 
		ret += queue.top()._key_word;
		queue.pop();
		ret += " ";
		num --;
	}
	return ret;
}


int Min(int a, int b, int c)
{
	return  a > b ? b : a > c ? c : a;
}

int Query::get_edit_distance(std::string &dict_word, std::string &query_word)
{
	int **arr = new int*[dict_word.size()+1];
	for(size_t ix=0; ix!= dict_word.size()+1; ++ix)
	{
		arr[ix] = new int[query_word.size()+1];
	}
	if(dict_word.size() ==0 && query_word.size() == 0)
	{
		return 0;
	}
	for(size_t ix=0; ix!=dict_word.size()+1; ++ix)
	{
		arr[ix][0] = ix;
	}
	for(size_t iy=0; iy!=query_word.size()+1; ++iy)
	{
		arr[0][iy] = iy;
	}
	for(size_t ix=1; ix!=dict_word.size()+1; ++ix)
	{
		for(size_t iy=1; iy!=query_word.size()+1; ++iy)
		{
			int cost = (dict_word[ix-1] == query_word[iy-1]) ? 0 : 1;
			int substitution = arr[ix-1][iy-1] + cost;
			int insert = arr[ix][iy-1] + 1;
			int deletion = arr[ix-1][iy] + 1;
			arr[ix][iy] = Min(substitution, insert, deletion);
		}
	}
	int ret = arr[dict_word.size()][query_word.size()];
	for(size_t i=0; i!=dict_word.size()+1; ++i)
	{
		delete[] arr[i];
	}
	delete arr;
	arr = NULL;
	return ret;
}

/*bool cmp_ed_map(const PAIR& lhs, const PAIR& rhs)
{
	return lhs.second < rhs.second;
}*/

Query::~Query()
{
	LOGGER_WRITE(Logger::END, "Query end\n\n")
	LOGGER_STOP()
}