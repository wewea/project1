#include "Query.h"
#include "Init.h"
#include "Logger.h"
#include <iostream>
using namespace std;

/*
all:
	g++ -g Init.cpp Dict.cpp Logger.cpp Query.cpp test_query.cpp Mutex.cpp -o query -lpthread 
	exec ./exec_task.sh
	*/
int main(int argc, char *argv[])
{
	string conf_path = argv[1];
	string log_path = argv[2];
	Logger::Start(log_path);
	Init init(conf_path);
	Logger::Severity(init.severity());
	Dict dict(init.gbk());
	Query query;
	while(true)
	{
		string result;
		string query_word;
		cin >> query_word;
		if(query.GetQueryWord(query_word))
		{
			result = query.GetResult();
			cout << result << endl;
		}
		else
		{
			break;
		}
	}
}
