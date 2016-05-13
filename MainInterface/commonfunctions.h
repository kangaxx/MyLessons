#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H
#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <string>


using namespace std;
extern "C" class CommonFunctions
{

public:
    CommonFunctions();
    int str2int_c(string s);
//    int str2int_c(string s,int iDefault);
//    string char2str_c(char ch);
//    string chars2str_c(char* ch,int iSize);
//    char* str2chars_c(string s);
};

#endif // COMMONFUNCTIONS_H

