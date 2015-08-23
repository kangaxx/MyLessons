#ifndef ITEMPLATEFILE_H
#define ITEMPLATEFILE_H
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "common.h"
using namespace std;
namespace lcg{
class ITemplateFile
{
protected:
    ITemplateFile(){;}
public:
    ITemplateFile(string ){;}
    virtual ~ITemplateFile();
    virtual int getFileLength() = 0;
    virtual char *getFileContain(char *dest) = 0;
};

class CppTemplateFile:public ITemplateFile
{
protected:
    CppTemplateFile(){;}
public:
    explicit CppTemplateFile(string fileName);
    ~CppTemplateFile();
    int getFileLength(){return m_fileLength;}
    char *getFileContain(char *dest){strncpy(dest,m_fileContain,m_fileLength);return dest;}
private:
    char *m_fileContain;
    int m_fileLength;
};

}

#endif // ITEMPLATEFILE_H
