/*********************************************************************/
//         this is an binary log codes demo
//              create by gxx 2015.11.4
//
//
//
//
//
//
//
//
/*********************************************************************/
#include "logfunctions.h"



int main()
{
    try
    {
        BinlogBase bin(CHARS_BIN_LOG_DEMO_FILE_NAME);
        string log = "test log";
        bin.appendLog(log);
        return 0;
    }
    catch(const char* err)
    {
        cout << "ERROR:"<< err << endl;
    }
}

