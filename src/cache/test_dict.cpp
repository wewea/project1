/*************************************************************************
	> File Name: test_dict.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 16时57分50秒
 ************************************************************************/

#include <iostream>
#include "Dict.h"
#include "Init.h"

using namespace std;

int main(int argc, char *argv[])
{
	Init init(argv[1]);
	Dict dict(init.gbk());
	return 0;	
}

