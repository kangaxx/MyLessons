/**
 * Project Untitled
 */


#include "ILogInfo.h"
#include <QString>

using namespace logfunctions;

/**
 * IReadWriteUserLog implementation
 */
QStringList g_names;


/**
 * 实现IReadWriteUserLog类中initial函数
 * UserLog根据两种方式获取log文件名  文件名外面传过来
 */
void IReadWriteUserLog::Initial(char *path)
{
    QString  pathname(path);
    QDir log_path_dir(pathname);

    //若log文件夹不存在的话，则建立
    if(!log_path_dir.exists())
    {
        QDir dir;
        dir.mkdir(pathname);
    }

    fileName = BaseFunctions::combineFilePath(path,this->getFileName().toStdString());

//    QFile file(QString::fromStdString(fileName));
//    file.open(QIODevice::WriteOnly);
//    file.close();


    //    cout <<"path:"<<path <<endl;
    //    cout <<"fileName:"<<fileName <<endl;

    LiTableName tableName(USERLOG_TABLE_NAME);

    LiField flogID(USERLOG_FIELD_NAME_LOGID);
    flogID.SetLen(8);
    flogID.SetIdentity(true);
    tableName.doAddField(flogID);

    LiField fLogLevel(USERLOG_FIELD_NAME_LOGLEVEL);
    fLogLevel.SetLen(8);
    tableName.doAddField(fLogLevel);

    LiField fjobName(USERLOG_FIELD_NAME_JOBNAME);
    fjobName.SetLen(INT_USERLOG_FIELD_JOBNAME_LENGTH);
    tableName.doAddField(fjobName);

    LiField fproject(USERLOG_FIELD_NAME_PROJECT);
    fproject.SetLen(INT_USERLOG_FIELD_PROJECT_LENGTH);
    tableName.doAddField(fproject);

    LiField fsubmitTime(USERLOG_FIELD_NAME_SUBMITTIME);
    fsubmitTime.SetLen(20);
    tableName.doAddField(fsubmitTime);

    LiField fJobStatus(USERLOG_FIELD_NAME_JOBSTATUS);
    fJobStatus.SetLen(8);
    tableName.doAddField(fJobStatus);

    LiField fpercentage(USERLOG_FIELD_NAME_PERCENTAGE);
    fpercentage.SetLen(8);
    tableName.doAddField(fpercentage);

    LiField fuserName(USERLOG_FIELD_NAME_USERNMAE);
    fuserName.SetLen(INT_USERLOG_FIELD_USERNAME_LENGTH);
    tableName.doAddField(fuserName);

    LiField fuserID(USERLOG_FIELD_NAME_USERID);
    fuserID.SetLen(8);
    tableName.doAddField(fuserID);

    this->m_SqlLink = &(SqlFunctions::Create(BIN_LOG,tableName,QString::fromStdString(fileName),INT_SQL_LOGFILE_TYPE_TABLEABLE_LOG));
}

/**
 * 实现IReadWriteUserLog类中initial函数
 * UserLog根据两种方式获取log文件名  文件名通过工区转换传过来
 */
void IReadWriteUserLog::Initial(QString projectName)
{
    //cout <<"projectName:"<<projectName.toStdString() <<endl;

    //path路径名通过工区名转换  //通过数据库查询
    char *path = GetPathName(projectName).toLatin1().data();        //QString ==> char*
    fileName = BaseFunctions::combineFilePath(path,this->getFileName().toStdString());

    cout <<"path:"<<path <<endl;
    cout <<"fileName:"<<fileName <<endl;

    LiTableName tableName(USERLOG_TABLE_NAME);

    LiField flogID(USERLOG_FIELD_NAME_LOGID);
    flogID.SetLen(8);
    tableName.doAddField(flogID);

    LiField fLogLevel(USERLOG_FIELD_NAME_LOGLEVEL);
    fLogLevel.SetLen(8);
    tableName.doAddField(fLogLevel);

    LiField fjobName(USERLOG_FIELD_NAME_JOBNAME);
    fjobName.SetLen(INT_USERLOG_FIELD_JOBNAME_LENGTH);
    tableName.doAddField(fjobName);

    LiField fproject(USERLOG_FIELD_NAME_PROJECT);
    fproject.SetLen(INT_USERLOG_FIELD_PROJECT_LENGTH);
    tableName.doAddField(fproject);

    LiField fsubmitTime(USERLOG_FIELD_NAME_SUBMITTIME);
    fsubmitTime.SetLen(20);
    tableName.doAddField(fsubmitTime);

    LiField fJobStatus(USERLOG_FIELD_NAME_JOBSTATUS);
    fJobStatus.SetLen(8);
    tableName.doAddField(fJobStatus);

    LiField fpercentage(USERLOG_FIELD_NAME_PERCENTAGE);
    fpercentage.SetLen(8);
    tableName.doAddField(fpercentage);

    LiField fuserName(USERLOG_FIELD_NAME_USERNMAE);
    fuserName.SetLen(INT_USERLOG_FIELD_USERNAME_LENGTH);
    tableName.doAddField(fuserName);

    LiField fuserID(USERLOG_FIELD_NAME_USERID);
    fuserID.SetLen(8);
    tableName.doAddField(fuserID);

    this->m_SqlLink = &(SqlFunctions::Create(BIN_LOG,tableName,QString::fromStdString(fileName),INT_SQL_LOGFILE_TYPE_TABLEABLE_LOG));

}

/**
 * 实现IReadWriteUserLog类中read函数
 * 一条一条数据实现
 * @return LogInfo *
 */

ILogInfo * IReadWriteUserLog::ReadLog()
{
    throw QString("Bin Log not support ReadLog function now!");
    LiTable tb;
    ISqlQuery *qry;
    LiDataContext dc;                               //主函数对象，LiDataContext是操作数据库的操作模板

    if(m_SqlLink != NULL)
    {
        qry = m_SqlLink->sqlQryFct();
    }


    m_uinfo = new UserLogInfo;
    //设置欲操作的表名
    dc.SetTableName(USERLOG_TABLE_NAME);

    LiField flogID(QString(USERLOG_FIELD_NAME_LOGID));               //设置字段对象flogID名logID
    LiField fLogLevel(QString(USERLOG_FIELD_NAME_LOGLEVEL));         //设置字段对象fLogLevel名LogLevel
    LiField fjobName(QString(USERLOG_FIELD_NAME_JOBNAME));           //设置字段对象 fjobName名jobName
    LiField fproject(QString(USERLOG_FIELD_NAME_PROJECT));           //设置字段对象fproject名project
    LiField fsubmitTime(QString(USERLOG_FIELD_NAME_SUBMITTIME));     //设置字段对象fsubmitTime名submitTime
    LiField fJobStatus(QString(USERLOG_FIELD_NAME_JOBSTATUS));       //设置字段对象fJobStatus名JobStatus
    LiField fpercentage(QString(USERLOG_FIELD_NAME_PERCENTAGE));     //设置字段对象fpercentage名percentage
    LiField fuserName(QString(USERLOG_FIELD_NAME_USERNMAE));         //设置字段对象fuserName名userName
    LiField fuserID(QString(USERLOG_FIELD_NAME_USERID));             //设置字段对象fuserID名userID

    //将欲操作的字段，需要添加到LiDataContext
    dc.AddField(&flogID);
    dc.AddField(&fLogLevel);
    dc.AddField(&fjobName);
    dc.AddField(&fproject);
    dc.AddField(&fsubmitTime);
    dc.AddField(&fJobStatus);
    dc.AddField(&fpercentage);
    dc.AddField(&fuserName);
    dc.AddField(&fuserID);

    //设置筛选条件
    LiField condition(QString(USERLOG_CONDITION_NAME));
    condition.SetSo(liEqual);                   //条件对象比较关系， 大于，小于，等于
    condition.SetAON(AND);                      //AON , AND OR NOT
    condition.SetValue(QString::number(m_logid)); //条件对象比较值

    //添加筛选条件
    dc.AddCondition(&condition);

    //执行query命令后，数据会被填充到tb对象内
    qry->query(*m_SqlDb,dc, tb);

    int rownum0 = tb.GetRecords().GetCount();                   //get all of cout

    if(rownum0 >0){
        g_names << USERLOG_FIELD_NAME_LOGID <<USERLOG_FIELD_NAME_LOGLEVEL<< USERLOG_FIELD_NAME_JOBNAME<< USERLOG_FIELD_NAME_PROJECT<< USERLOG_FIELD_NAME_SUBMITTIME<< USERLOG_FIELD_NAME_JOBSTATUS<< USERLOG_FIELD_NAME_PERCENTAGE<< USERLOG_FIELD_NAME_USERNMAE << USERLOG_FIELD_NAME_USERID;
        QStringList Values;
        Values = tb.GetRecords().NextFields(g_names);
        int id = Values.at(0).toInt();                          //获得主键

        if(id == m_logid)
        {
            ((UserLogInfo*)m_uinfo)->setLogID(id);                             //获取一条记录中flogID字段的值，并将其设置进logID
            ((UserLogInfo*)m_uinfo)->setJobName(Values.at(2).toStdString());   //获取一条记录中fjobname字段的值，并将其设置成jobname
            ((UserLogInfo*)m_uinfo)->setProject(Values.at(3).toStdString());   //获取一条记录中fproject字段的值，并将其设置成project

            /**
                    解决从数据库中读取时间多“T”的问题
            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            ***********UserlogInfo subtime:2011-11-11T11:11:11****************
            ***********UserlogInfo qstrsubtime: "2011-11-11T11:11:11" ****************

            ***********UserlogInfo leftsubtime: "2011-11-11" ****************

            ***********UserlogInfo rightsubtime: "11:11:11" ****************

            ***********UserlogInfo submittime: "2011-11-11 11:11:11" ****************

            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            time:2011-11-11 11:11:11
            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            */


            QString qstrsubtime = Values.at(4);
            QString leftsubtime = qstrsubtime.left(10);                     //截取前10个字节
            QString rightsubtime = qstrsubtime.right(8);                    //截取后8个字节
            QString submitTime = leftsubtime + " " + rightsubtime;          //合并

            ((UserLogInfo*)m_uinfo)->setSubmitTime(submitTime.toStdString());//获取一条记录中fsubmitTime字段的值，并将其设置成submitTime
            ((UserLogInfo*)m_uinfo)->setPercentage(Values.at(6).toInt());      //获取一条记录中fpercentage字段的值，并将其设置成percentage
            ((UserLogInfo*)m_uinfo)->setUserName(Values.at(7).toStdString());  //获取一条记录中fuserName字段的值，并将其设置成username
            ((UserLogInfo*)m_uinfo)->setUserID(Values.at(8).toInt());          //获取一条记录中fuserID字段的值，并将其设置成userID

            int lev = Values.at(1).toInt();                                     //获取一条记录中fLogLevel字段的值
            LogLevel level = ((UserLogInfo*)m_uinfo)->level_int2enum(lev);     //将数据库取出的整数值转化为对应的枚举数
            ((UserLogInfo*)m_uinfo)->setLevel(level);                          //将其设置成level

            int jobstatus = Values.at(5).toInt();                               //获取一条记录中fJobStatus字段的值
            JobStatus status = ((UserLogInfo*)m_uinfo)->jobstatus_int2enum(jobstatus);//将数据库取出的整数值转化为对应的枚举数
            ((UserLogInfo*)m_uinfo)->setJobStatus(status);                     //将其设置成jobstatus
        }
        else
        {
            cout <<"No Records" <<endl;
        }
    }

    LiTable tb1;
    ISqlQuery *qry1;
    LiDataContext dc1;                               //主函数对象，LiDataContext是操作数据库的操作模板

    if(m_SqlLink != NULL)
    {
        qry1 = m_SqlLink->sqlQryFct();
    }

    //设置欲操作的表名
    dc1.SetTableName(USERLOG_TABLE_NAME);

    LiField flogID1(QString(USERLOG_FIELD_NAME_LOGID));               //设置字段对象flogID名logID
    LiField fLogLevel1(QString(USERLOG_FIELD_NAME_LOGLEVEL));         //设置字段对象fLogLevel名LogLevel
    LiField fjobName1(QString(USERLOG_FIELD_NAME_JOBNAME));           //设置字段对象 fjobName名jobName
    LiField fproject1(QString(USERLOG_FIELD_NAME_PROJECT));           //设置字段对象fproject名project
    LiField fsubmitTime1(QString(USERLOG_FIELD_NAME_SUBMITTIME));     //设置字段对象fsubmitTime名submitTime
    LiField fJobStatus1(QString(USERLOG_FIELD_NAME_JOBSTATUS));       //设置字段对象fJobStatus名JobStatus
    LiField fpercentage1(QString(USERLOG_FIELD_NAME_PERCENTAGE));     //设置字段对象fpercentage名percentage
    LiField fuserName1(QString(USERLOG_FIELD_NAME_USERNMAE));         //设置字段对象fuserName名userName
    LiField fuserID1(QString(USERLOG_FIELD_NAME_USERID));             //设置字段对象fuserID名userID

    //将欲操作的字段，需要添加到LiDataContext
    dc1.AddField(&flogID1);
    dc1.AddField(&fLogLevel1);
    dc1.AddField(&fjobName1);
    dc1.AddField(&fproject1);
    dc1.AddField(&fsubmitTime1);
    dc1.AddField(&fJobStatus1);
    dc1.AddField(&fpercentage1);
    dc1.AddField(&fuserName1);
    dc1.AddField(&fuserID1);


    LiField cond(QString(USERLOG_FIELD_NAME_LOGID));
    cond.SetSo(liBigger);                           //条件对象比较关系， 大于，小于，等于
    cond.SetAON(AND);                               //AON , AND OR NOT
    cond.SetValue(QString::number(m_logid));        //条件对象比较值

    //添加筛选条件
    dc1.AddCondition(&cond);

    //执行query命令后，数据会被填充到tb对象内
    qry1->query(*m_SqlDb, dc1, tb1);

    int rownum1 = tb1.GetRecords().GetCount();      //get all of cout

    if(rownum1 > 0){
        QStringList names;
        names << USERLOG_FIELD_NAME_LOGID <<USERLOG_FIELD_NAME_LOGLEVEL<< USERLOG_FIELD_NAME_JOBNAME<< USERLOG_FIELD_NAME_PROJECT<< USERLOG_FIELD_NAME_SUBMITTIME<< USERLOG_FIELD_NAME_JOBSTATUS<< USERLOG_FIELD_NAME_PERCENTAGE<< USERLOG_FIELD_NAME_USERNMAE << USERLOG_FIELD_NAME_USERID;
        QStringList Value;
        Value = tb1.GetRecords().NextFields(names);
        int ID = Value.at(0).toInt();               //获得主键
        m_logid = ID;
    }
    return m_uinfo;
}


/**
 * 实现IReadWriteUserLog类中ReadALL函数
 * 读全部数据，返回总数
 * @param number
 * @return LogInfo *
 */
ILogInfo * IReadWriteUserLog::ReadAllLog(int *number)
{
    QFile file(QString::fromStdString(fileName));
    if(!file.exists())
    {
        return NULL;
    }


    ISqlQuery *qry;
    LiDataContext dc;                               //主函数对象，LiDataContext是操作数据库的操作模板
    LiTable tb;


    if(m_SqlLink != NULL){
        qry = this->m_SqlLink->sqlQryFct();
    }

    //设置欲操作的表名
    dc.SetTableName(USERLOG_TABLE_NAME);

    LiField flogID(QString(USERLOG_FIELD_NAME_LOGID));               //设置字段对象flogID名logID
    LiField fLogLevel(QString(USERLOG_FIELD_NAME_LOGLEVEL));         //设置字段对象fLogLevel名LogLevel
    LiField fjobName(QString(USERLOG_FIELD_NAME_JOBNAME));           //设置字段对象 fjobName名jobName
    LiField fproject(QString(USERLOG_FIELD_NAME_PROJECT));           //设置字段对象fproject名project
    LiField fsubmitTime(QString(USERLOG_FIELD_NAME_SUBMITTIME));     //设置字段对象fsubmitTime名submitTime
    LiField fJobStatus(QString(USERLOG_FIELD_NAME_JOBSTATUS));       //设置字段对象fJobStatus名JobStatus
    LiField fpercentage(QString(USERLOG_FIELD_NAME_PERCENTAGE));     //设置字段对象fpercentage名percentage
    LiField fuserName(QString(USERLOG_FIELD_NAME_USERNMAE));         //设置字段对象fuserName名userName
    LiField fuserID(QString(USERLOG_FIELD_NAME_USERID));             //设置字段对象fuserID名userID

    //将欲操作的字段，需要添加到LiDataContext
    dc.AddField(&flogID);
    dc.AddField(&fLogLevel);
    dc.AddField(&fjobName);
    dc.AddField(&fproject);
    dc.AddField(&fsubmitTime);
    dc.AddField(&fJobStatus);
    dc.AddField(&fpercentage);
    dc.AddField(&fuserName);
    dc.AddField(&fuserID);

    //执行query命令后，数据会被填充到tb对象内
    qry->query(dc, tb);

    *number = tb.GetRecords().GetCount();
    int rowum  = *number;

    m_uinfo_array = new UserLogInfo[rowum];


    for(int i = 0; i < rowum; i++)
    {
        g_names << USERLOG_FIELD_NAME_LOGID <<USERLOG_FIELD_NAME_LOGLEVEL<< USERLOG_FIELD_NAME_JOBNAME<< USERLOG_FIELD_NAME_PROJECT<< USERLOG_FIELD_NAME_SUBMITTIME<< USERLOG_FIELD_NAME_JOBSTATUS<< USERLOG_FIELD_NAME_PERCENTAGE<< USERLOG_FIELD_NAME_USERNMAE << USERLOG_FIELD_NAME_USERID;
        QStringList Values;
        Values = tb.GetRecords().NextFields(g_names);                       //得到一条记录的所有字段的值
        ((UserLogInfo*)m_uinfo_array)[i].setLogID(Values.at(0).toInt());           //获取一条记录中flogID字段的值，并将其设置进logID
        ((UserLogInfo*)m_uinfo_array)[i].setJobName(Values.at(2).toStdString());   //获取一条记录中fjobname字段的值，并将其设置成jobname
        ((UserLogInfo*)m_uinfo_array)[i].setProject(Values.at(3).toStdString());   //获取一条记录中fproject字段的值，并将其设置成project


        QString qstrsubtime = Values.at(4);
        QString leftsubtime = qstrsubtime.left(10);                     //截取前10个字节
        QString rightsubtime = qstrsubtime.right(8);                    //截取后8个字节
        QString submitTime = leftsubtime + " " + rightsubtime;          //合并

        ((UserLogInfo*)m_uinfo_array)[i].setSubmitTime(submitTime.toStdString());//获取一条记录中fsubmitTime字段的值，并将其设置成submitTime
        //        ((UserLogInfo*)m_uinfo_array)[i].setSubmitTime(Values.at(4).toStdString());//获取一条记录中fsubmitTime字段的值，并将其设置成submitTime
        ((UserLogInfo*)m_uinfo_array)[i].setPercentage(Values.at(6).toInt());      //获取一条记录中fpercentage字段的值，并将其设置成percentage
        ((UserLogInfo*)m_uinfo_array)[i].setUserName(Values.at(7).toStdString());  //获取一条记录中fuserName字段的值，并将其设置成username
        ((UserLogInfo*)m_uinfo_array)[i].setUserID(Values.at(8).toInt());          //获取一条记录中fuserID字段的值，并将其设置成userID

        int lev = Values.at(1).toInt();                                     //获取一条记录中fLogLevel字段的值
        LogLevel level = ((UserLogInfo*)m_uinfo_array)[i].level_int2enum(lev);     //将数据库取出的整数值转化为对应的枚举数
        ((UserLogInfo*)m_uinfo_array)[i].setLevel(level);                          //将其设置成level

        int jobstatus = Values.at(5).toInt();                               //获取一条记录中fJobStatus字段的值
        JobStatus status = ((UserLogInfo*)m_uinfo_array)[i].jobstatus_int2enum(jobstatus);//将数据库取出的整数值转化为对应的枚举数
        ((UserLogInfo*)m_uinfo_array)[i].setJobStatus(status);                     //将其设置成jobstatus
    }

    delete m_SqlLink;
    return m_uinfo_array;
}


/**
 * 实现IReadWriteUserLog类中insert函数
 * @param *newLog
 * @return bool
 */
bool IReadWriteUserLog::InsertLog(ILogInfo *newLog)
{
    //设置数据表字段对象
    LiField flogID,fLogLevel,fjobName, fproject,fsubmitTime,fJobStatus, fpercentage,fuserName,fuserID;

    LiDataContext dc;
    ISqlQuery *qry;     // ISqlQuery类是我们进行数据库操作的基本类，所有操作都通过它的对象来完成

    if(m_SqlLink != NULL)
    {
        qry = m_SqlLink->sqlQryFct();
    }

    //获得插入函数输入值
    int logID = ((UserLogInfo*)newLog)->getLogID();
    int LogLevel = ((UserLogInfo*)newLog)->getLevel();
    string jobname = ((UserLogInfo*)newLog)->getJobName();
    string project = ((UserLogInfo*)newLog)->getProject();
    string submitTime = ((UserLogInfo*)newLog)->getSubmitTime();
    JobStatus jobstatus  = ((UserLogInfo*)newLog)->getJobStatus();
    int percentage = ((UserLogInfo*)newLog)->getPercentage();
    string userName = ((UserLogInfo*)newLog)->getUserName();
    int userID = ((UserLogInfo*)newLog)->getUserID();

    //设置各字段对象的名及对应值
//    flogID.SetName(USERLOG_FIELD_NAME_LOGID );
//    flogID.SetValue(QString::number(logID));

    fLogLevel.SetName(USERLOG_FIELD_NAME_LOGLEVEL);
    fLogLevel.SetValue(QString::number(LogLevel));

    fjobName.SetName(USERLOG_FIELD_NAME_JOBNAME);
    fjobName.SetValue(QString::fromStdString(jobname));

    fproject.SetName(USERLOG_FIELD_NAME_PROJECT);
    fproject.SetValue(QString::fromStdString(project));

    fsubmitTime.SetName(USERLOG_FIELD_NAME_SUBMITTIME);
    fsubmitTime.SetValue(QString::fromStdString(submitTime));

    fJobStatus.SetName(USERLOG_FIELD_NAME_JOBSTATUS);
    fJobStatus.SetValue(QString::number(jobstatus));

    fpercentage.SetName(USERLOG_FIELD_NAME_PERCENTAGE);
    fpercentage.SetValue(QString::number(percentage));

    fuserName.SetName(USERLOG_FIELD_NAME_USERNMAE);
    fuserName.SetValue(QString::fromStdString(userName));

    fuserID.SetName(USERLOG_FIELD_NAME_USERID);
    fuserID.SetValue(QString::number(userID));

    //设置欲操作的表名
    dc.SetTableName(USERLOG_TABLE_NAME);

    //将设置插入的数据字段值，添加到LiDataContext
//    dc.AddField(&flogID);
    dc.AddField(&fLogLevel);
    dc.AddField(&fjobName);
    dc.AddField(&fproject);
    dc.AddField(&fsubmitTime);
    dc.AddField(&fJobStatus);
    dc.AddField(&fpercentage);
    dc.AddField(&fuserName);
    dc.AddField(&fuserID);

    //当插入正确时返回true，插入失败时返回false
    bool ok = false;
    if((qry->DoInsert(dc)) > 0)
    {
        ok = true;
    }

    delete m_SqlLink;
    return ok;
}



/**
 * 实现IReadWriteUserLog类中update函数
 * @param *newLog
 * @param logID
 * @return bool
 */
bool IReadWriteUserLog::UpdateLog(ILogInfo  *newLog, int logid)
{
    throw QString("Bin Log not support UpdateLog function now!");
    //设置数据表字段对象
    LiField fLogLevel,fjobName, fproject,fsubmitTime,fJobStatus, fpercentage,fuserName,fuserID;  //更新的字段及值
    LiField fdCond;   //更新的筛选条件

    LiDataContext dc;
    ISqlQuery *qry;

    if(m_SqlLink != NULL)
    {
        qry = m_SqlLink->sqlQryFct();
    }

    //获得update函数输入值
    int LogLevel = ((UserLogInfo*)newLog)->getLevel();
    string jobname = ((UserLogInfo*)newLog)->getJobName();
    string project = ((UserLogInfo*)newLog)->getProject();
    string submitTime = ((UserLogInfo*)newLog)->getSubmitTime();
    JobStatus jobstatus  = ((UserLogInfo*)newLog)->getJobStatus();
    int percentage = ((UserLogInfo*)newLog)->getPercentage();
    string userName = ((UserLogInfo*)newLog)->getUserName();
    int userID = ((UserLogInfo*)newLog)->getUserID();

    //设置各字段对象的名及对应值
    fLogLevel.SetName(USERLOG_FIELD_NAME_LOGLEVEL);
    fLogLevel.SetValue(QString::number(LogLevel));

    fjobName.SetName(USERLOG_FIELD_NAME_JOBNAME);
    fjobName.SetValue(QString::fromStdString(jobname));

    fproject.SetName(USERLOG_FIELD_NAME_PROJECT);
    fproject.SetValue(QString::fromStdString(project));

    fsubmitTime.SetName(USERLOG_FIELD_NAME_SUBMITTIME);
    fsubmitTime.SetValue(QString::fromStdString(submitTime));

    fJobStatus.SetName(USERLOG_FIELD_NAME_JOBSTATUS);
    fJobStatus.SetValue(QString::number(jobstatus));

    fpercentage.SetName(USERLOG_FIELD_NAME_PERCENTAGE);
    fpercentage.SetValue(QString::number(percentage));

    fuserName.SetName(USERLOG_FIELD_NAME_USERNMAE);
    fuserName.SetValue(QString::fromStdString(userName));

    fuserID.SetName(USERLOG_FIELD_NAME_USERID);
    fuserID.SetValue(QString::number(userID));

    //设置欲操作的表名
    dc.SetTableName(USERLOG_TABLE_NAME);

    //增加筛选条件
    fdCond.SetName(USERLOG_FIELD_NAME_LOGID);
    fdCond.SetValue(QString::number(logid));
    fdCond.SetAON(AND);         // AON , AND OR NOT
    fdCond.SetSo(liEqual);      // 条件对象比较关系， 大于，小于，等于
    //condition虽然也是LiField，不过作为查询条件的条件语句时，除了字段名外需要设定字段的布尔运算关系(AON),以及布尔运算的计算值

    //添加筛选条件
    dc.AddCondition(&fdCond);
    //将设置更新的数据字段值，添加到LiDataContext
    dc.AddField(&fLogLevel);
    dc.AddField(&fjobName);
    dc.AddField(&fproject);
    dc.AddField(&fsubmitTime);
    dc.AddField(&fJobStatus);
    dc.AddField(&fpercentage);
    dc.AddField(&fuserName);
    dc.AddField(&fuserID);

    bool ok = false;

    //当update正确时返回true，插入失败时返回false
    if((qry->DoUpdate(*m_SqlDb, dc))  > 0)
    {
        ok = true;
    }


    return ok;
}

/**
 * 实现IReadWriteUserLog类中delete函数
 * @param logID
 * @return bool
 */

bool IReadWriteUserLog::DelLog(int logid)
{
    throw QString("Bin Log not support DelLog function now!");
    LiDataContext dc;
    ISqlQuery *qry;
    LiField fdCond;                 //筛选删除数据的条件

    if(m_SqlLink != NULL)
    {
        qry = m_SqlLink->sqlQryFct();
    }

    //设置删除条件
    fdCond.SetName(USERLOG_CONDITION_NAME);
    fdCond.SetValue(QString::number(logid));
    fdCond.SetAON(AND);
    fdCond.SetSo(liEqual);

    dc.SetTableName(USERLOG_TABLE_NAME); //设置欲操作的表名
    dc.AddCondition(&fdCond);       //设置筛选删除数据的条件

    //当delete正确时返回true，插入失败时返回false
    bool ok = false;
    if((qry->DoDel(*m_SqlDb,dc)) > 0)
    {
        ok = true;
    }


    return ok;
}

QString IReadWriteUserLog::getFileName()
{
    return QString("UserLog_Testing.log");
}

//通过数据库查询，获取路径
QString IReadWriteUserLog::GetPathName(QString projectName)
{
    FSqlFactory *sqlfct;

    sqlfct = &(SqlFunctions::Create(MYSQL,QString::fromLatin1(CHARS_UNIT_TEST_INIFILE),
                                    QString::fromStdString(BaseFunctions::getConfigPath())));
    cout <<"projectName2:"<<projectName.toStdString() <<endl;


    //    LiConditionList condition;
    //    condition << PROJECT_FIELD_NAME_PROJECTNAME << projectName << AND<<liEqual;

    //    LiTableName tableName(PROJECTLIST_TABLE_NAEM);

    //    LiResultList rst = sqlfct->sqlQryFct()->query(fields,LiTableName(PROJECTLIST_TABLE_NAEM),&condition);

    //    int i = 0;
    //    QString proName("");
    //    for(; i < rst.getCount(); i++)
    //    {
    //        proName = rst.at(i,QString::fromLatin1(PROJECT_FIELD_NAME_DATAPATH));
    //    }
    //    if (i == 0)
    //        qDebug() << QString("warning: no record!");


    //---------------------------------------------------
    LiTable tb;
    ISqlQuery *qry;
    LiDataContext dc;                               //主函数对象，LiDataContext是操作数据库的操作模板

    //设置欲操作的表名
    dc.SetTableName(PROJECTLIST_TABLE_NAEM);

    LiField fdata(QString(PROJECT_FIELD_NAME_DATAPATH));               //设置字段对象flogID名logID

    LiField cond(QString(PROJECT_FIELD_NAME_PROJECTNAME));
    cond.SetSo(liEqual);
    cond.SetAON(AND);
    cond.SetValue(projectName);


    //将欲操作的字段，需要添加到LiDataContext
    dc.AddField(&fdata);
    dc.AddCondition(&cond);


    if(sqlfct != NULL)
        qry = sqlfct->sqlQryFct();
    //执行query命令后，数据会被填充到tb对象内
    qry->query(dc, tb);

    int rowum = tb.GetRecords().GetCount();

    QString proName("");
    for(int i = 0; i < rowum; i++)
    {
        g_names <<  PROJECT_FIELD_NAME_DATAPATH;
        QStringList Values;
        Values = tb.GetRecords().NextFields(g_names);                       //得到一条记录的所有字段的值
        proName = Values.at(0);
    }

    delete sqlfct;
    return proName;
}
