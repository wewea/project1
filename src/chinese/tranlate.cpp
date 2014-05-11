#include "translate.h"
 
 #define MAX_LEN 200
 
 size_t TranslateSP::translate(char *src, size_t srcLen, char *desc, size_t descLen)
 {
     char **inbuf = &src;
     char **outbuf = &desc;
     memset(desc, 0, descLen);
     return iconv(i_cd, inbuf, &srcLen, outbuf, &descLen);
 }
 
 size_t TranslateSP::convert(const char *from_charset, const char *to_charset, 
         char *src, size_t srcLen, char *desc, size_t descLen)
 {
     char **inbuf = &src;
     char **outbuf = &desc;
     iconv_t cd = iconv_open(to_charset, from_charset);
     if ((iconv_t)-1 == cd) return (size_t)-1;
     memset(desc, 0, descLen);
     size_t n = iconv(cd, inbuf, &srcLen, outbuf, &descLen);
     iconv_close(cd);
     return n;
 }
 
 int main(int argc, char *argv[])
 {
     char *str = "我爱zhong国! ％＃＠＃";
     char *str1 = "i大量需要转换的编码";
     char *str2 = "函数就是用于将hello进行转换";
     char newstr[MAX_LEN];
     TranslateSP tsp;
     tsp.convert("utf-8", "gbk", str, strlen(str), newstr, MAX_LEN);
     printf("%s\n", newstr);
     TranslateSP newtsp("UTF-8", "GBK");
     newtsp.translate(str1, strlen(str1), newstr, MAX_LEN);
     printf("%s\n", newstr);
     newtsp.translate(str2, strlen(str2), newstr, MAX_LEN);
     printf("%s\n", newstr);
     return 0;
 }