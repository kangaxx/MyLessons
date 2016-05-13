#include <iostream>
#include "logshmcontrol.h"

#define CHR_UT_SHM_PATH "/home/gxx"
#define CHR_UT_SHM_PID_MACRO 111
using namespace std;

bool ut_writeLog(const SystemLogInfo log)
{

    cout << "LSS_WAIT_WRITE LOG, log.msg:" << log.getMessage() << endl;
//         << " log.operation:" << log->getOperation()
//         << " log.username:" << log->getUserName() << endl;
    return true;
}

int main()
{
    try
    {
        LogShmCreator creator;
        if (creator.begin(CHR_UT_SHM_PATH))
            cout << "begin success" << endl;
        else
            cout << "begin failed" << endl;
        creator.justForUnitTest_01();
        creator.justForUnitTest_02();


        LogShmUser user;
        if (user.begin(CHR_UT_SHM_PATH,CHR_UT_SHM_PID_MACRO))
            cout << "user begin success" << endl;
        else
            cout << "user begin failed" << endl;
        SystemLogInfo test;
        test.setMessage(string("test msg 1"));
        test.setOperation(string("test op"));
        test.setUserName(string("Tom"));
        user.insertNewLog(test);
        test.setMessage(string("test msg 2"));
        test.setUserName(string("Jerry"));
        user.insertNewLog(test);
        test.setMessage(string("test msg 3"));
        test.setUserName(string("Ace"));
        user.insertNewLog(test);
        test.setMessage(string("test msg 4"));
        test.setUserName(string("Bill"));
        user.insertNewLog(test);
        test.setMessage(string("test msg 5"));
        test.setUserName(string("Cici"));
        user.insertNewLog(test);
        user.justForUnitTest_01();
        user.justForUnitTest_02();

/************************** test log creator write log ***************************/
        cout << endl << endl << ".............write test................" << endl << endl;
        creator.writeLog(ut_writeLog);
        user.justForUnitTest_02();
/************************** test multi-proc ***************************/
//        if (user2.begin(CHR_UT_SHM_PATH,CHR_UT_SHM_PID_MACRO+1))
//            cout << "user2 begin success" << endl;
//        else
//            cout << "user2 begin failed" << endl;
//        user2.justForUnitTest_01();
//        user2.justForUnitTest_02();
        int w;
        cin >> w;
    }

    catch (const char *err)
    {
        cout << "error: "<< err << endl;
    }
    catch (logic_error err)
    {
        cout << "logic err:" << err.what() << endl;
    }

    return 0;
}

