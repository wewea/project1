#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "MixSegment.hpp"
#include "EncodingConverter.h"
//#include "MPSegment.hpp"
//#include "HMMSegment.hpp"
//#include "FullSegment.hpp"
//#include "QuerySegment.hpp"

using namespace CppJieba;

const char * const dict_path = "dict/jieba.dict.gbk";
const char * const model_path = "dict/hmm_model.gbk";

const char * const test_lines = "王奶奶给刘奶奶倒牛奶";

int main(int argc, char ** argv) {
	/*segment init may take a few seconds.*/
	MixSegment segment(dict_path, model_path);
	vector<string> words;
/*    segment.cut(test_lines, words);
    print(words);

    fstream infile("in.txt");
    string s;
    words.clear();
    while(getline(infile, s)){
    	segment.cut(s, words);
    	print(words);
    }
*/
	EncodingConverter trans;
	string s = "王奶奶给刘奶奶倒牛奶";	// UTF8
	s = trans.utf8_to_gbk(s);	// UTF8 -> GBK
	segment.cut(s, words);
	for (auto word : words) {	//-std=c++11
		cout << trans.gbk_to_utf8(word) << endl;	// GBK -> UTF8
	}

	return 0;
}
