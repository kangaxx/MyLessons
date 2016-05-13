#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "logshmcontrol.h"

#define MAXFILE 65535
#define CHAR_INITIAL_FILENAME "server_db.ini"
#define CHAR_INI_LOG_KEYPATH "systemlogkey"
#define INT_SLEEP_TIME_IN_BLOCKSCAN 5
using namespace std;
LogShmCreator *g_shmlogCreator = NULL;
string getKeyPath(){
    const char* path;
    path = BaseFunctions::getConfigPath(BaseFunctions::FPM_SYSENV);
    string configFileName = BaseFunctions::combineFilePath(path,CHAR_INITIAL_FILENAME);
    return BaseFunctions::GetParaByName(configFileName,CHAR_INI_LOG_KEYPATH);
}

void createShm(){
    g_shmlogCreator = new LogShmCreator;
    if (g_shmlogCreator->begin(getKeyPath().c_str()) == false){
        perror("ERROR: log run manager start fail ,cause by can not create share memory");
        exit(1);
    }
}

void destoryShm(){
    if (g_shmlogCreator)
        delete g_shmlogCreator;
}

bool writeLog(SystemLogInfo log){
    IReadWriteSystemLog ioLog;
    ioLog.Initial();
    return ioLog.InsertLog(&log);
}

int main()
{
    pid_t pc;


    pc = fork();  //step 1 , create child pc
    if (pc <0){
        cout << "ERROR: log manager fork failed!" << endl;
        exit(1);
    }
    else if (pc > 0){
        cout << "Log manager running in deamon , pid:" << pc << endl;
        exit(0);
    }

    setsid(); //step 2 , detach proc group
    chdir("/") ; //step 3 , clear work path
//    umask(0);//umask set file mask code(complement type)
    for (int i=0; i<MAXFILE; i++)
        close(i);

    createShm();
    while(true){
        g_shmlogCreator->writeLog(writeLog);
        sleep(INT_SLEEP_TIME_IN_BLOCKSCAN);
    }
    destoryShm();
    cout << "Log manager stop ..." << endl;
    return 0;
}

