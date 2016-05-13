/**
 * Project Untitled
 */


#include "ILogInfo.h"
#include <time.h>
#include <string.h>





/**
 * SystemLogInfo implementation
 */

using namespace logfunctions;
/**
 * 实现设置注册时间函数
 * @param time
 */


ILogInfo::~ILogInfo()
{
    // do nothing;
}


void SystemLogInfo::setLogTime(string time)
{
    //BaseFunctions time_functions;

    if(time != "" && !time.empty())
    {
        //int Time = time_functions.str2time(time);
        int Time = string2time(time);

        /*限制注册时间范围*/
        if(Time > MIN_SYSTIME && Time < MAX_SYSTIME)
        {
            logTime = Time;
        }
        else if(Time < MIN_SYSTIME || Time < MAX_SYSTIME)
        {}
    }
    else if(time == "" && time.empty())
    {}
}

/**
 * 时间格式转化函数字符串格式转化为整型
*/
time_t SystemLogInfo::string2time(string str)
{
    tm tm_;
    int year, month, day, hour, minute,second;
    sscanf(str.c_str(),"%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    tm_.tm_year  = year-1900;
    tm_.tm_mon   = month-1;
    tm_.tm_mday  = day;
    tm_.tm_hour  = hour;
    tm_.tm_min   = minute;
    tm_.tm_sec   = second;
    tm_.tm_isdst = 0;

    time_t t_ = mktime(&tm_); //已经减了8个时区
    return t_; //秒时间
}

/**
 * 时间格式转化函数整型格式转化为字符串格式
*/
string SystemLogInfo::time2string(time_t time)
{
    char buf[DEFAULT_DATETIME_LEN];
    struct tm *tmp = localtime(&time);
    strftime(buf,DEFAULT_DATETIME_LEN,DEFAULT_DATETIME_FMT,tmp);

    string t_ = string(buf);
    return t_;
}


/**
 * 实现设置用户名函数，当设置的用户名超过规定时，截取掉超过部分
 * @param user
 */
void SystemLogInfo::setUserName(string username) 
{
    if(username != "" && !username.empty())
        strncpy(userName, username.c_str(), INT_SYSTEMLOG_FIELD_USERNAME_LENGTH-1);
    else if(username == "" || username.empty())
    {
        //cout << "username不能为空！" << endl;
    }
}
/**
 * 实现设置工区函数,当设置的工区名超过规定时，截取掉超过部分
 * @param project
 */
void SystemLogInfo::setProject(string pject) 
{
    if(pject != "" && !pject.empty() )
        strncpy(project,pject.c_str(),INT_SYSTEMLOG_FIELD_PROJECT_LENGTH-1);
    else if(pject == "" ||  pject.empty())
    {
        //cout << "project不能为空!" << endl;
    }
}
/**
 * 实现设置操作函数
 * @param operation
 */
void SystemLogInfo::setOperation(string oprtion) 
{
    if(oprtion != "" && !oprtion.empty())
        strncpy(operation, oprtion.c_str(), INT_SYSTEMLOG_FIELD_OPERATION - 1);
    else if(oprtion == "" || oprtion.empty())
    {}
}

void SystemLogInfo::setMessage(string msg)
{
    if(msg != "" && !msg.empty())
        strncpy(message, msg.c_str(), INT_ILOG_FIELD_MESSAGE_LENGTH - 1);
    else if(msg == "" || msg.empty())
    {}
    return ;
}

/**
 *实现获得level函数,当设置不满足规定要求时，取构造函数默认值
 */
void SystemLogInfo::setLevel(LogLevel Level)
{
    level = Level;
}

/**
 *实现获得注册ID函数,当设置的ID不满足规定要求时，取构造函数默认值
 */
void SystemLogInfo::setLogID(int logid)
{
    if(logid >= MIN_LOGID && logid <= MAX_LOGID)
    {
        logID = logid;
    }
    else if(logid < MIN_LOGID){}
    else if(logid > MAX_LOGID){}
}


/**
 * 实现获得注册时间函数
 * @return time_t
 */

string SystemLogInfo::getLogTime()
{
    //    BaseFunctions time_functions;
    //    string time = time_functions.time2str(logTime);

    string time =  time2string(logTime);

    return time;
}
/**
 * 实现获得用户名函数
 * @return string
 */

string SystemLogInfo::getUserName() const
{
    return userName;
}
/**
 * 实现获得工区函数
 * @return string
 */
string SystemLogInfo::getProject() const
{
    return project;
}

/**
 * 实现获得操作函数
 * @return string
 */
string SystemLogInfo::getOperation() const
{
    return operation;
}

int SystemLogInfo::getLogID()
{
    return logID;
}

LogLevel SystemLogInfo::getLevel()
{
    return level;
}

string SystemLogInfo::getMessage() const
{
    return message;
}


/**
 *枚举转化为int型函数
*/
int SystemLogInfo::level_enum2int(LogLevel level)
{
    int  m_level;
    if(level == LL_NORMAL)
        m_level = ENUM_LL_NORMAL;
    if(level == LL_WARNING)
        m_level = ENUM_LL_WARNING;
    if(level == LL_ERROR)
        m_level = ENUM_LL_ERROR;
    if(level == LL_OTHER)
        m_level = ENUM_LL_OTHER;

    return m_level;
}

/**
 *int型转化为枚举函数
*/
LogLevel SystemLogInfo::level_int2enum(int level)
{
    LogLevel  m_level;
    if(level == ENUM_LL_NORMAL)
        m_level = LL_NORMAL;
    if(level == ENUM_LL_WARNING)
        m_level = LL_WARNING;
    if(level == ENUM_LL_ERROR)
        m_level = LL_ERROR;
    if(level == ENUM_LL_OTHER)
        m_level = LL_OTHER;

    return m_level;
}

/**
 *测试SestemLogInfo成员变量是否完整,有一个false，即为false
 */
bool SystemLogInfo::isComplete()
{
    bool results = true;

    //    if(userName == "" || userName.empty())
    //        results = false;
    //    if(project =="" || project.empty())
    //        results = false;
    //    if(operation =="" || operation.empty())
    //        results = false;
    if(logTime > MAX_SYSTIME || logTime < MIN_SYSTIME)
        results = false;

    return results;
}

