#include "clscli.h"
#include "strstream"
#include "sstream"

CCLI::CCLI(string &CMD)
{
    string c_sDefault = "";
    SetNum(1);
    SetRepeat(1);
    SetFileName(c_sDefault);
    SetAlgoName(c_sDefault);
    SetOutputPath(c_sDefault);
    InitialWithCMD(CMD);
}

CCLI::~CCLI()
{
    //do nothing yet;
}

void CCLI::Debug()
{
    cout << "path is:" << this->m_ExePath << endl;
    cout << "FileName is : " << this->m_FileName << endl;
    cout << "Num is : " << this->m_Num << endl;
    cout << "Repeat is : " << this->m_Repeat << endl;
    cout << "output is : " << this->m_OutputPath << endl;
    cout << "AlgoName is :" << this->m_AlgoName << endl;

}

void CCLI::SetFileName(string &FileName)
{
    m_FileName = FileName;
}

void CCLI::SetNum(int Num)
{
    m_Num = Num;
}

void CCLI::SetRepeat(int Repeat)
{
    m_Repeat = Repeat;
}

void CCLI::SetOutputPath(string &OutputPath)
{
    m_OutputPath = OutputPath;
}

void CCLI::SetAlgoName(string &AlgoName)
{
    m_AlgoName = AlgoName;
}


void CCLI::SetExePath(string &ExePath)
{
    m_ExePath = ExePath;
}

string &CCLI::GetFileName()
{
    return m_FileName;
}

int CCLI::GetNum()
{
    return m_Num;
}

int CCLI::GetRepeat()
{
    return m_Repeat;
}

string &CCLI::GetOutputPath()
{
    return m_OutputPath;
}

string &CCLI::GetAlgoName()
{
    return m_AlgoName;
}

string &CCLI::GetExePath()
{
    return m_ExePath;
}

void CCLI::InitialWithCMD(string &CMD)
{
    m_CMD = CMD;
    string t;
    stringstream ss;
    int Num = 0;
    int Repeat = 0;
    //call all find functions to setup Params.
    string Path;
    Path = CMD.substr(0,Path.find_first_of(' '));
    int LastSlash = Path.find_last_of('/');
    if (LastSlash >= 0)
        Path = Path.substr(0,LastSlash);
    else
        Path = "";

    SetExePath(Path);
    SetAlgoName(FindAlgoName(CMD,m_AlgoName));
    SetFileName(FindFileName(CMD,m_FileName));
    setUserName(findUserName(CMD,m_userName));
    SetOutputPath(FindOutputPath(CMD,m_OutputPath));
    setNetMessage(findNetMessage(CMD,m_netMessage));
    SetCstParam(FindCstPara(CMD,m_CstParam));
    SetArithParam(FindArithPara(CMD,m_ArithParam));
    FindNum(CMD,t);
    ss << t << endl;
    FindRepeat(CMD,t);
    ss << t << endl;
    ss >> Num >> Repeat;
    SetNum(Num);
    SetRepeat(Repeat);
}

string &CCLI::FindParaByName(string &CMD, string *pParamList[], string &dest, string Default)
{
    string *result = &dest;
    ECLIParaStatus ParamStatus = ParamAnalysis(CMD,pParamList,2,*result);
    if (ParamStatus == ParamRepeated)
        throw "Command params error , too many param for name.press -h to get help.";
    else if (ParamStatus == NoPara)
        *result  = Default;
    else if (ParamStatus == NoCLIError)
        return *result;
    return *result;
}


//参数算法名称  命令行表示 -nXXXX 或者 name=XXXXX
string &CCLI::FindAlgoName(string &CMD, string &Dest)
{
    string * result = &Dest;
    string *pParamList[2] = {new string(" -n"),new string(" name=")};//参数前面必然有空格
    FindParaByName(CMD,pParamList,*result,string(""));
    return *result;

}

//参数 原始文件名 中间文件和处理文件都会和原始文件名有一定的相关性 命令行表示 -sXXXX 或者source=
string& CCLI::FindFileName(string& CMD,string& Dest)
{
    string * result = &Dest;
    string *pParamList[2] = {new string(" -s"),new string(" source=")};//参数前面必然有空格
    FindParaByName(CMD,pParamList,*result,string(""));
    return *result;
}

//参数 编号    命令行表示 -iXXXX 或者 num=XXXX 默认为 1
string &CCLI::FindNum(string& CMD, string &Dest)
{
    string * result = &Dest;
    string *pParamList[2] = {new string(" -i"),new string(" num=")};//参数前面必然有空格
    FindParaByName(CMD,pParamList,*result,string("1"));
    return *result;
}

//参数 强制指定输出路径 -oXXXX 或者 out=XXXX 不指定的话就使用资源文件缩在路径作为输出路径
string &CCLI::FindOutputPath(string &CMD, string &Dest)
{
    string * result = &Dest;
    string *pParamList[2] = {new string(" -o"),new string(" out=")};//参数前面必然有空格
    FindParaByName(CMD,pParamList,*result,string(""));
    return *result;
}

//参数 计算任务所属用户，影响启动计算进程的参数 -uXXXX 或者 username=XXXX
string &CCLI::findUserName(string &CMD, string &Dest)
{
    string * result = &Dest;
    string *pParamList[2] = {new string(" -u"),new string(" username=")};//参数前面必然有空格
    FindParaByName(CMD,pParamList,*result,string(""));
    return *result;
}
//参数 获取前端发送来的NetMessage对象字符 -pXXXX 或者 ppm=XXXX
string &CCLI::findNetMessage(string &CMD, string &Dest)
{
    string * result = &Dest;
    string *pParamList[2] = {new string(" -p"),new string(" ppm=")};//参数前面必然有空格
    FindParaByName(CMD,pParamList,*result,string(""));
    return *result;
}

//参数 重复次数 命令行表示 -rXXXX 或者 rep=XXXX 默认为 1
string &CCLI::FindRepeat(string &CMD, string &Dest)
{
    string * result = &Dest;
    string *pParamList[2] = {new string(" -r"),new string(" rep=")};//参数前面必然有空格
    FindParaByName(CMD,pParamList,*result,string("1"));
    return *result;
}

//参数 算法相关参数 -aXXXX 或者 ari = XXXXX
string &CCLI::FindArithPara(string &CMD, string &Dest)
{
    string * result = &Dest;
    string *pParamList[2] = {new string(" -a"),new string(" Arith=")};//参数前面必然有空格
    FindParaByName(CMD,pParamList,*result,string("1"));
    return *result;
}

//参数 自定义参数 -c 或者 cst = XXX
string &CCLI::FindCstPara(string &CMD, string &Dest)
{
    string * result = &Dest;
    string *pParamList[2] = {new string(" -c"),new string(" cst=")};//参数前面必然有空格
    FindParaByName(CMD,pParamList,*result,string("1"));
    return *result;
}
//

ECLIParaStatus CCLI::ParamAnalysis(string &CMD, string *ParamFlags[],int Len, string &Dest)
{
    ECLIParaStatus result = NoCLIError;
    int Count = CountParamTime(CMD,ParamFlags,Len);
    if (Count > 1) //param repeated
    {
        result = ParamRepeated;
        return result;
    }

    if (Count < 1)
    {
        result = NoPara;
    }
    else
    {
        int Pos = 0;
        int PosEnd = 0;
        for (int i = 0; i < Len; ++i) {
            Pos = CMD.find(*ParamFlags[i]);
            if (Pos>=0)
            {
                PosEnd = CMD.find(" ",Pos+1);
                if (PosEnd >= 0)
                    Dest = CMD.substr(Pos+(*ParamFlags[i]).length(),PosEnd-Pos-(*ParamFlags[i]).length());
                else
                    Dest = CMD.substr(Pos+(*ParamFlags[i]).length());
                return result;  //Carefully, we get first param.
            }
        }
    }
    return result;
}

int CCLI::CountParamTime(string &CMD, string *ParamFlags[],int Len)
{
    int result = 0;
    for (int i=0 ;i<Len;i++)
    {
        string::size_type Pos;
        Pos = CMD.find(*ParamFlags[i]);
        while(Pos != CMD.npos)
        {
            result ++ ;
            Pos = CMD.find(*ParamFlags[i],Pos+1);
        }
    }

    return result;
}
