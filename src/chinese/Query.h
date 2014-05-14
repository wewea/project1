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
#include "EncodingConverter.h"

class Query
{
	public:
		Query(int num = 5);
		~Query();

		int ED_Uint16(const std::vector<uint16_t> &w1, const std::vector<uint16_t> &w2);
		bool GetQueryWord(const std::string &request);
		void Cut(std::string&, std::vector<uint16_t>&);
		void Enqueue(std::priority_queue<EditDist> &queue, const std::vector<uint16_t> &query_word, 
		const std::set<int> &candicate);
		std::string GetResult();
		std::string SortWord(const std::set<int>& repeat, const std::set<int>& distint,
		const std::vector<uint16_t>&query_word);
		
	private:
		std::string _query_word;
		std::string _query_result;
		size_t _result_num;
		std::map<std::string, int> _dict_map;
};


#endif

