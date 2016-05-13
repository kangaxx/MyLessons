
/**
 * Project Untitled
 */


#include "ILogInfo.h"
#include <time.h>
#include <string.h>
//#include "commonfunction_c.h"

using namespace logfunctions;

/** UserLogInfo implementation */

/**
 * 实现设置工作名函数,当设置的工作名超过规定时，截取掉超过部分
 * @param name
 */
void UserLogInfo::setJobName(string jobname)
{
    if(jobname != "" && !jobname.empty())
        strncpy(jobName, jobname.c_str(),INT_USERLOG_FIELD_JOBNAME_LENGTH-1);
    else if(jobname == "" || jobname.empty())
    {
        //cout << "jobname不能为空！" << endl;
    }

}

/**
 * 实现设置工区函数,当设置的工区名超过规定时，截取掉超过部分
 * @param project
 */
void UserLogInfo::setProject(string pject)
{
    if(pject != "" && !pject.empty() )
        strncpy(project,pject.c_str(),INT_USERLOG_FIELD_PROJECT_LENGTH-1);
    else if(pject == "" ||  pject.empty())
    {}
}

/**
 * 实现设置提交时间函数
 * @param time
 */
void UserLogInfo::setSubmitTime(string time)
{
    //BaseFunctions time_functions;

    if(time != "" && !time.empty())
    {
        /*限制提交时间范围*/
        //int Time = time_functions.str2time(time);
        int Time = string2time(time);

        if(Time > MIN_SYSTIME && Time < MAX_SYSTIME)
        {
            submitTime = Time;
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
time_t UserLogInfo::string2time(string str)
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
string UserLogInfo::time2string(time_t time)
{
    char buf[DEFAULT_DATETIME_LEN];
    struct tm *tmp = localtime(&time);
    strftime(buf,DEFAULT_DATETIME_LEN,DEFAULT_DATETIME_FMT,tmp);

    string t_ = string(buf);
    return t_;
}



/**
 * 实现设置工作状态函数
 * @param jobStatus
 */
void UserLogInfo::setJobStatus(JobStatus status)
{
    jobStatus = status;
}

/**
 * 实现设置工设置百分比函数,当设置不满足规定要求时，取构造函数默认值
 * @param percentage
 */
void UserLogInfo::setPercentage(int pertage)
{
    if(pertage >= MIN_PERCENTAGE && pertage <= MAX_PERCENTAGE)
    {
        percentage = pertage;
    }
    else if(pertage < MIN_PERCENTAGE)
    {}
    else if(pertage > MAX_PERCENTAGE)
    {
        percentage = ERR_DEFAULT_PERCENTAGE;
    }
}

/**
 * 实现设置用户名函数，当设置的用户名超过规定时，截取掉超过部分
 * @param userName
 */
void UserLogInfo::setUserName(string username)
{
    if(username != "" && !username.empty())
        strncpy(userName, username.c_str(),INT_USERLOG_FIELD_USERNAME_LENGTH-1);
    else if(username == "" || username.empty())
    {
    }

}

/**
 * 实现设置用户ID函数,当设置不满足规定要求时，取构造函数默认值
 * @param UserID
 */
void UserLogInfo::setUserID(int UserID)
{
    if(UserID >= MIN_USERID && UserID <= MAX_USERID)
    {
        userID = UserID;
    }
    else if(UserID < MIN_USERID)
    {}
    else if(UserID > MAX_USERID)
    {}
}

void UserLogInfo::setMessage(string msg)
{
    if(msg != "" && !msg.empty())
        strncpy(message, msg.c_str(), INT_ILOG_FIELD_MESSAGE_LENGTH - 1);
    else if(msg == "" || msg.empty())
    {}
    return ;

    return ;
}

/**
 * 实现获得level函数,当设置不满足规定要求时，取构造函数默认值
 */
void UserLogInfo::setLevel(LogLevel Level)
{
    if(Level == LL_WARNING)
        level = Level;
    else if(Level == LL_ERROR)
        level = Level;
    else if(Level == LL_NORMAL)
        level = Level;
    else if(Level == LL_OTHER)
        level = Level;
}

/**
 * 实现获得注册ID函数,当设置的ID不满足规定要求时，取构造函数默认值
 */
void UserLogInfo::setLogID(int logid)
{

    if(logid >= MIN_LOGID && logid <= MAX_LOGID)
    {
        logID = logid;
    }
    else if(logid < MIN_LOGID){}
    else if(logid > MAX_LOGID){}
}

/**
 *枚举转化为int型函数
*/
int UserLogInfo::level_enum2int(LogLevel level)
{
    int  intlev;
    if(level == LL_NORMAL)
        intlev = ENUM_LL_NORMAL;
    if(level == LL_WARNING)
        intlev = ENUM_LL_WARNING;
    if(level == LL_ERROR)
        intlev = ENUM_LL_ERROR;
    if(level == LL_OTHER)
        intlev = ENUM_LL_OTHER;

    return intlev;
}

/**
 *int型转化为枚举函数
*/
LogLevel UserLogInfo::level_int2enum(int level)
{
    LogLevel  m_level;
    if(ENUM_LL_NORMAL == level)
        m_level = LL_NORMAL;
    if(ENUM_LL_WARNING == level)
        m_level = LL_WARNING;
    if(ENUM_LL_ERROR == level)
        m_level = LL_ERROR;
    if(ENUM_LL_OTHER == level)
        m_level = LL_OTHER;

    return m_level;
}

/**
 *int型转化为枚举函数
*/
JobStatus UserLogInfo::jobstatus_int2enum(int status)
{
    JobStatus Status;
    if(ENUM_JOBSTATUS_JS_RUNNING == status)
        Status = JS_RUNNING;
    if(ENUM_JOBSTATUS_JS_COMPLETED == status)
        Status = JS_COMPLETED;
    if(ENUM_JOBSTATUS_JS_FAILED == status)
        Status = JS_FAILED;
    if(ENUM_JOBSTATUS_JS_WAIT == status)
        Status = JS_WAIT;
    if(ENUM_JOBSTATUS_JS_ERROR == status)
        Status = JS_ERROR;
    if(ENUM_JOBSTATUS_JS_OTHER == status)
        Status = JS_OTHER;

    return Status;
}

/**
 *枚举转化为int型函数
*/
int UserLogInfo::jobstatus_enum2int(JobStatus status)
{
    int intstatus;
    if(status == JS_RUNNING)
        intstatus = ENUM_JOBSTATUS_JS_RUNNING;
    if(status == JS_COMPLETED)
        intstatus = ENUM_JOBSTATUS_JS_COMPLETED;
    if(status == JS_FAILED)
        intstatus = ENUM_JOBSTATUS_JS_FAILED;
    if(status == JS_WAIT)
        intstatus = ENUM_JOBSTATUS_JS_WAIT;
    if(status == JS_ERROR)
        intstatus = ENUM_JOBSTATUS_JS_ERROR;
    if(status == JS_OTHER)
        intstatus = ENUM_JOBSTATUS_JS_OTHER;

    return intstatus;
}


/**
 * 实现获得工作名函数
 * @return string
 */
string UserLogInfo::getJobName()
{
    return jobName;
}

/**
 * 实现获得工区函数
 * @return string
 */
string UserLogInfo::getProject() const
{
    return project;
}

/**
 * 实现获得提交时间函数
 * @return time_t
 */
string UserLogInfo::getSubmitTime()
{
    //    BaseFunctions time_functions;
    //    string time = time_functions.time2str(submitTime);

    string time = time2string(submitTime);

    return time;
}

/**
 * 实现获得工作状态函数
 * @return
 */
JobStatus UserLogInfo::getJobStatus()
{
    return jobStatus;
}

/**
 * 实现获得百分比函数
 * @return int
 */
int UserLogInfo::getPercentage()
{
    return percentage;
}

/**
 * 实现获得用户名函数
 * @return string
 */
string UserLogInfo::getUserName() const
{
    return userName;
}

/**
 * 实现获得用户ID函数
 * @return int
 */
int UserLogInfo::getUserID()
{
    return userID;
}

int UserLogInfo::getLogID()
{
    return logID;
}

LogLevel UserLogInfo::getLevel()
{
    return level;
}

string UserLogInfo::getMessage() const
{
    return string(message);
}

/**
 *测试UserLogInfo成员变量是否完整,有一个false，即为false
 */
bool UserLogInfo::isComplete()
{
    bool returnvalue = true;

    //    if(userName.empty() || userName == "")
    //         returnvalue = false;
    //    if(jobName.empty() || jobName == "")
    //         returnvalue = false;
    //    if(project.empty() || project == "")
    //         returnvalue = false;
    if(userID < MIN_USERID || userID > MAX_USERID)
        returnvalue = false;
    if(percentage < MIN_PERCENTAGE || percentage > MAX_PERCENTAGE)
        returnvalue = false;
    if(submitTime < MIN_SYSTIME || submitTime > MAX_SYSTIME)
        returnvalue = false;
    if(jobStatus == JS_ERROR )
        returnvalue = false;

    return returnvalue;
}
