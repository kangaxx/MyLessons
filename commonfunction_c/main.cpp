#include <iostream>
#include "commonfunction_c.h"
#define STR_INIFILE_NAME "Service.ini"
using namespace std;
using namespace commonfunction_c;
typedef struct ShareMemoryInfos{
    int Mission_Id;
}stc_ShareMemoryInfos;
int main(int argc, char *argv[])
{
    try
    {

        //////////////////////////////////////////////////////////
        /// \brief test getProc
        //////////////////////////////////////////////////////////


        char argvDest[20];
        bool isGetArgv = BaseFunctions::getProcArgv(argc,(const char**)argv,"-l",argvDest);
        if (isGetArgv)
            cout << "get argv dest : " << argvDest << endl;
        else
            cout << "not found argv" << endl;

        /////////////////////////////////////////////////////////////////////
        string wStr = "abc|12345|bbb|111|";
        string wReg = "abc|\\S+|";
        string result = BaseFunctions::cutValue(wStr,wReg);
        cout << "test reg, got: " << result << endl;
        return 0;        int inp=1;
        cin >> inp;
        while(inp>1)
        {
            time_t t =time(NULL);

            string st = BaseFunctions::time2str(t);
            cout << st << endl;
            cin>> inp;
        }
        char eof;
        cin.get(eof);
        cin.sync();
        char gettime[20]={"1970-01-01 00:00:00"};
        cin.getline(gettime,20);
        cout << gettime << endl;
        while(gettime[0] != 'a')
        {
            time_t t_=BaseFunctions::str2time(gettime);
            cout << "t_ is :" << int(t_) <<endl;
            string res = BaseFunctions::time2str(t_);
            cout << res << endl;
            cin.getline(gettime,20);

        }
        char getInt_01[7];
        BaseFunctions::Int2Chars(123456,getInt_01,6);
        cout << "int 1 to char :" << getInt_01<< endl;

        int getChar_01 = BaseFunctions::Chars2Int("123456");
        cout << "char2int \"123456\" :"<< getChar_01 << endl;
        string toInt = "1234";
        int GetStr = BaseFunctions::Str2Int(toInt,1);
        cout <<"get int from string:" << GetStr << endl;
        char wp[DEFAULT_LINUX_PATH_LENGTH];
        if (BaseFunctions::GetWorkPath(wp) > 0)
            cout << wp << endl;
        string filePath;
        filePath = string(wp);

        string fileName = filePath + "/test.ini";
        string paraName = "password";

//        BaseFunctions bf(filePath,fileName);
        string para = BaseFunctions::GetParaByName(fileName,paraName);
        string para2 = BaseFunctions::GetParaByLine(fileName,2);
        cout << "para : [" <<  para << "]" << endl;
        cout << "para2 : [" << para2 << "]" << endl;




        stc_ShareMemoryInfos *ShmInfo;
        stc_ShmInitials shmIni;
        shmIni.ipcKey = 0x200;
        shmIni.path = "/home/gxx/tmp";
        shmIni.size = 1024;

        IShareMemImp<stc_ShareMemoryInfos> *imp = new ShareMemImp_Linux<stc_ShareMemoryInfos>(shmIni);
        IShareMemDerive<stc_ShareMemoryInfos> *der;
        der = new IShareMemDerive<stc_ShareMemoryInfos>(*imp);
        int shmid = der->CreateShmId();
        cout << "shm id is :" << shmid << endl;
        ShmInfo = der->GetShmAddr();
        cout << "ShmInfo is" << ShmInfo;
        ShmInfo->Mission_Id = 1;
        der->DtShm(ShmInfo);
        ShmInfo = der->GetShmAddr();
        cout << "after relink , mission id is : " << ShmInfo->Mission_Id;
        cout << "press any key to clear share memory and end program!";
        int stop;
        cin >> stop;

        der->DtShm(ShmInfo);
        der->ClearShm();

    }
    catch(string err)
    {
        cout <<"err str: "<< err << endl;
    }
    catch(const char* err)
    {
        cout << err << endl;
    }
    return 0;
}

