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

bool Query::GetQueryWord(const std::string &request)
{
	EncodingConverter trans("UTF8", "GBK");
	if(request == "")
	{
		return false;
	}
	else {

	/*for(string::size_type ix=0; ix != ret.size(); ++ix)
	{
		if(ret[ix] >= 'A' && ret[ix] <= 'Z' && !((unsigned char )ret[ix]))
		{
			ret[ix] += 32;
		}
	}*/

	string ret = trans.utf8_to_gbk(request);
	_query_word = ret;
	char buf[256]="";
	sprintf(buf, "%s: %d\t Start query word [%s]", __FILE__, __LINE__, request.c_str());
	LOGGER_WRITE(Logger::INFO, buf)
	return true;
	}
}


std::string Query::GetResult()
{
	map<uint16_t, set<int> > candicate;
	char buf[256]="";
	EncodingConverter trans("GBK", "UTF8");
	std::vector<uint16_t> split_word;//切成单个字符,将每个字符转为16位,存入vector
	string tmp = _query_word;
	Cut(tmp, split_word);	

	vector<uint16_t>::iterator iter = split_word.begin();

	//取得候选词集,由于使用map容器所以,查询词若有重复字符,则重复的可能被排除,减少候选词的数量和查询时间
	for(; iter != split_word.end(); ++iter)
	{
		//value值是set不能用等与号运算符,map和set的兼容操作只有insert, 该方式是 map.insert(iter1, iter2);
		//类似不同容器间可以用迭代器复制
		candicate[*iter].insert(Dict::_index[*iter].begin(), Dict::_index[*iter].end());
	}

	//遍历查询词每个字符的候选词集set, 计算查询词和候选词的编辑距离, 存入优先级队列
	map<uint16_t, set<int> >::iterator iter_candicate = candicate.begin();
	set<int> all_word;
	set<int> repeat_word;
	set<int> distint_word;
	//EncodingConverter trans("GBK", "UTF8");//for test printf set repeat and distint
	for(; iter_candicate != candicate.end(); ++iter_candicate)
	{
		set<int>::iterator iter_ix = (iter_candicate->second).begin();
		vector<uint16_t> candicate_word;
		for(; iter_ix != (iter_candicate->second).end(); ++iter_ix)
		{
			pair<set<int>::iterator , bool> ret =
			 all_word.insert(*iter_ix);
			if(ret.second == false)//取得查询词每个字符有交集的候选词
			{
				repeat_word.insert(*iter_ix);
			}
		}
	}

	set<int>temp = repeat_word;
	//取得查询词间每个字符没有交集的候选词	
	set<int>::iterator iter_iy = all_word.begin();	
	for(; iter_iy != all_word.end(); ++iter_iy)
	{
		pair<set<int>::iterator, bool> ret = 
		temp.insert(*iter_iy);
		if(ret.second == true)
		{
			distint_word.insert(*iter_iy);	
		}
	}

	//根据候选词集编辑距离和词频,先返回有交集的集合, 若返回结果不够, 再返回非交集的集合
	string ret = SortWord(repeat_word, distint_word, split_word);

	sprintf(buf, "%s: %d\t Return result of [%s]", __FILE__, __LINE__, ret.c_str());
	LOGGER_WRITE(Logger::INFO, buf)
	return ret;
}

string Query::SortWord(const set<int>& repeat, const set<int>& distint,
	const vector<uint16_t>&query_word)
{
	std::priority_queue<EditDist> queue_repeat;
	std::priority_queue<EditDist> queue_distint;
	EncodingConverter trans("GBK", "UTF8");//trans ret

	Enqueue(queue_repeat, query_word, repeat);
	//根据设定的返回个数,组合前N个候选词,因优先级队列定义为按最大值(自定义为先比较编辑距离,再比较词频)优先排序
	int num = _result_num;
	string ret = "";
	while(!queue_repeat.empty() && num != 0)
	{
		ret += queue_repeat.top()._key_word;	
		ret += " ";
		queue_repeat.pop();
		--num;
	}

	if(num != 0)
	{
		Enqueue(queue_distint, query_word, distint);
		while(!queue_distint.empty() && num != 0)
		{
			ret += queue_distint.top()._key_word;
			ret += " ";
			queue_distint.pop();
			--num;
		}
	}

	string result = trans.gbk_to_utf8(ret);
	return result;
}


void Query::Enqueue(priority_queue<EditDist> &queue, const vector<uint16_t> &query_word, 
	const set<int> &index) 
{
	EncodingConverter trans("GBK", "UTF8");
	vector<uint16_t> candicate_word;
	pair<string, int>word;
	string cmp_word;
	set<int>::iterator iter = index.begin();
	for(; iter != index.end(); ++iter)
	{
		word = Dict::_dict[*iter];
		cmp_word = word.first;
		Cut(cmp_word, candicate_word);
		int ed =ED_Uint16(query_word, candicate_word);
		EditDist temp(word.first, word.second, ed);//利用优先级队列的自定义排序,实现现比较编辑距离,再比较词频的功能
		queue.push(temp);
	}
}


bool is_gbk_alpha(unsigned char c)
{
	return c >= 0x81 && c <= 0xFE;
}

void Query::Cut(std::string &buf, std::vector<uint16_t>&w)
{
	w.clear();
	for(std::string::size_type ix = 0; ix != buf.size(); ++ix)
	{
		if(is_gbk_alpha(buf[ix]))	
		{
		if(ix+1 == buf.size())
		{
			throw runtime_error("invalid gbk string");
		}
			unsigned char c1 = buf[ix];
			unsigned char c2 = buf[ix+1];
			uint16_t t = (c1 << 8) + c2;
			w.push_back(t);
			++ix;
		}
		else
		{
			w.push_back((uint16_t)(unsigned char) buf[ix]);
		}
	}
}

int Min(int a, int b, int c)
{
	return  a > b ? b : a > c ? c : a;
}


int Query::ED_Uint16(const vector<uint16_t> &w1, const vector<uint16_t> &w2)
{

	int len_a = w1.size();
	int len_b = w2.size();
	int memo[100][100];
	memset(memo, 0x00, 100*100*sizeof(int));
	if(w1.size() == 0)
	{
		return 0;
	}
	for(int ix = 0; ix <= len_a; ++ix)
	{
		memo[ix][0] = ix;
	}
	for(int iy = 0; iy <= len_b; ++iy)
	{
		memo[0][iy] = iy;
	}

	for(int ix = 1; ix <= len_a; ++ix)
	{
		for(int iy = 1; iy <= len_b; ++iy)
		{
			int cost = (w1[ix-1] == w2[iy-1]) ? 0 : 1;
			int substitution = memo[ix-1][iy-1] + cost;
			int insertion = memo[ix][iy-1] + 1;
			int deletion = memo[ix-1][iy] + 1;
			memo[ix][iy] = Min(substitution, insertion, deletion);
		}
	}
	return memo[len_a][len_b];
}


Query::~Query()
{
	LOGGER_WRITE(Logger::END, "Query end\n\n")
	LOGGER_STOP()
}
