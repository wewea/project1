/*************************************************************************
	> File Name: Query.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月06日 星期二 20时27分56秒
 ************************************************************************/


#ifndef _QUERY_H_
#define _QUERY_H_

#include <map>  
#include <string>  
#include <iostream> 
#include <algorithm> 
#include <vector>

#include "Dict.h"
#include "PriorityQueue.h"

class Query
{
	public:
		Query(int num = 5);
		~Query();
		int get_edit_distance(std::string &dict_word, std::string &query);
		void get_dict_map(std::ifstream&);
		bool get_query_word(const std::string &request);
		std::string get_query_result();
	private:
		std::string _query_word;
		std::string _query_result;
		size_t _result_num;
		std::map<std::string, int> _dict_map;

};


#endif

