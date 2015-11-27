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
public:
    ITemplateFile(){;}

    ITemplateFile(string ){;}
    virtual ~ITemplateFile();
    virtual void initial(string contain,string name,int id) = 0;
    virtual unsigned int getFileLength() = 0;
    virtual char *getFileContain(char *dest) = 0;
    virtual string getFileContain() = 0;
};

class CppTemplateFile:public ITemplateFile
{
public:

    explicit CppTemplateFile(){;}
    explicit CppTemplateFile(string fileName):ITemplateFile(fileName)
    {
        FILE *f;
        f = fopen(fileName.c_str(),"r");
        if (!f)
            throw static_cast<int>(PS_CG_TemplateNoFound);
        this->m_fileContain = new char[INT_MAX_CPPFILETEMPLATELENGTH];
        if (f)
            fclose(f);
    }
    explicit CppTemplateFile(string fileContain,string fileName,int id):ITemplateFile(fileName),m_fileContain(fileContain),m_fileName(fileName),m_fileId(id){}
    ~CppTemplateFile();
    unsigned int getFileLength(){return m_fileContain.size();}
    char *getFileContain(char *dest){strcpy(dest,m_fileContain.c_str());return dest;}
    string getFileContain(){return m_fileContain;}
    void initial(string fileContain,string fileName,int id){
        setFileContain(fileContain);
        setFileName(fileName);
        setFileId(id);
    }
    void setFileName(string fileName){m_fileName = fileName;}
    void setFileId(int id){m_fileId = id;}
    void setFileContain(string text){m_fileContain=text;}
private:
    string m_fileContain;
    string m_fileName;
    int m_fileId;
};

}

#endif // ITEMPLATEFILE_H
