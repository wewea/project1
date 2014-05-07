#include "Query.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	string conf_path = argv[1];
	string log_path = argv[2];
	Dict dict(conf_path, log_path);
	Query query(dict);
	while(true)
	{
		string result;
		if(query.get_query_word(3))
		{
			result = query.get_query_result();
			cout << result << endl;
		}
		else
		{
			break;
		}
	}
}
