#ifndef LOGFUNCTIONS_H
#define LOGFUNCTIONS_H
#include <stdio.h>
#include <common.h>
#include <iostream>

using namespace std;

//base class , do
class BinlogBase
{
public:
    BinlogBase(){m_file = NULL;}
    BinlogBase(string fileName){m_file = NULL;setFile(fileName.c_str());}
    BinlogBase(const char *fileName){m_file = NULL;setFile(fileName);}
    ~BinlogBase(){
        if (m_file != NULL){
            fclose(m_file);
            m_file = NULL;
        }
    }

    void setFile(const char *fileName){
        if (m_file != NULL)
            throw "ERROR: can not set file twice!";
        m_file = fopen(fileName,"ab");
    }
    void appendLog(string log){
        if (m_file == NULL)
            throw "ERROR: log file write error , file not exists";
        fwrite(log.c_str(),1,log.size(),m_file);
    }

private:
    FILE *m_file;
};

class logFunctions
{
public:
    logFunctions();
};

#endif // LOGFUNCTIONS_H
