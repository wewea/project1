/*
 * EncodingConverter.h
 *
 *  Created on: Apr 4, 2014
 *      Author: haha
 */

#ifndef ENCODINGCONVERTER_H_
#define ENCODINGCONVERTER_H_

#include "iconv.h"
#include <string>
#include <stdexcept>
#include <cstring>
#include <stdlib.h>
#include <string.h>


#define OUTLEN 255

 class EncodingConverter
 {
 public:
 	EncodingConverter():_cd(0){}
 	EncodingConverter(const char* from, const char *dest);
 	virtual ~EncodingConverter();
 	size_t translate(char *src, size_t srclen, char *dest, size_t destlen);
 	std::string utf8_to_gbk(const std::string&);
 	std::string gbk_to_utf8(const std::string&);


 private:

 	iconv_t _cd;
 };

#endif /* ENCODINGCONVERTER_H_ */
