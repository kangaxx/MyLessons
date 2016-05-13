/**
 * Project Untitled
 */


#include "ILogInfo.h"

/**
 * IReadWriteSystemLog implementation
 */
using namespace logfunctions;

QStringList g_Names;

/**
 * 实现IReadWriteSystemLog类中initial函数
 * @param fileName
 * @param type
 * @param link
 * Initial()完整功能没有完全实现，目前只实现部分功能，前两个参数尚未使用
 */
void IReadWriteSystemLog::Initial(char *)
{
    //确保QM_ROOT下必有log文件夹
    //    QString Path = QApplication::applicationDirPath()+"/";
    QString Path = QApplication::applicationDirPath();
    QString pathname = Path + "../log";
    QDir log_path_dir(pathname);

    //若log文件夹不存在的话，则建立
    if(!log_path_dir.exists())
    {
        QDir dir;
        dir.mkdir(pathname);
    }


    //创建一个路径 + 文件名，路径是环境变量+常量
    //文件名来自函数 getFileName， 该函数还有改进余地。
    char path[DEFAULT_LINUX_PATH_LENGTH];
    if (BaseFunctions::getSystemLogPath(path) == NULL)
        throw QString("ERROR, System log initial fail , cause by log path not exists");
    fileName = BaseFunctions::combineFilePath(path,this->getFileName().toStdString());

    //    QFile file(QString::fromStdString(fileName));
    //    file.open(QIODevice::WriteOnly);
    //    file.close();

    //创建binlog结构 ，此结构与此前mysql表的表结构一致
    LiTableName tn(SYSTEMLOG_TABLE_NAME);

    LiField id(SYSTEMLOG_FIELD_NAME_LOGID);
    id.SetLen(8);
    id.SetIdentity(true);
    tn.doAddField(id);

    LiField name(SYSTEMLOG_FIELD_NAME_USERNAME);
    name.SetLen(INT_SYSTEMLOG_FIELD_USERNAME_LENGTH);
    tn.doAddField(name);

    LiField level(SYSTEMLOG_FIELD_NAME_LOGLEVEL);
    level.SetLen(8);
    tn.doAddField(level);

    LiField project(SYSTEMLOG_FIELD_NAME_PROJECT);
    project.SetLen(INT_SYSTEMLOG_FIELD_PROJECT_LENGTH);
    tn.doAddField(project);

    LiField logTime(SYSTEMLOG_FIELD_NAME_LOGTIME);
    logTime.SetLen(20);
    tn.doAddField(logTime);

    LiField operation(SYSTEMLOG_FIELD_NAME_OPERATION);
    operation.SetLen(INT_SYSTEMLOG_FIELD_OPERATION);
    tn.doAddField(operation);

    LiField msg(SYSTEMLOG_FIELD_NAME_MESSAGE);
    msg.SetLen((INT_ILOG_FIELD_MESSAGE_LENGTH));
    tn.doAddField(msg);

    this->m_SqlLink = &(SqlFunctions::Create(BIN_LOG,tn,QString::fromStdString(fileName),INT_SQL_LOGFILE_TYPE_TABLEABLE_LOG));
}

void IReadWriteSystemLog::Initial(QString projName)
{
    throw "system log only save to QM_ROOT/log";
}

/**
 * 实现IReadWriteSystemLog类中read函数
 * 读一条数据
 * @return LogInfo *
 */

ILogInfo * IReadWriteSystemLog::ReadLog()
{
    throw QString("Bin Log not support ReadLog function now!");
    LiTable tb;                             //数据表类对象
    ISqlQuery *qry ;                         // ISqlQuery类是我们进行数据库操作的基本类，所有操作都通过它的对象来完成
    LiDataContext dc;                       //主函数对象，LiDataContext是操作数据库的操作模板，之后的操作信息都需要添加到其中。
    LiField flogID,fLogLevel,fuserName,fproject,flogTime, foperation,fdMessage;    //设置数据表字段对象

    flogID.SetName(SYSTEMLOG_FIELD_NAME_LOGID);                //设置字段对象flogID名logID
    flogID.SetAON(AND);

    fLogLevel.SetName(SYSTEMLOG_FIELD_NAME_LOGLEVEL);          //设置字段对象fLogLevel名LogLevel
    fLogLevel.SetAON(AND);

    fuserName.SetName(SYSTEMLOG_FIELD_NAME_USERNAME);          //设置字段对象fuserName名serName
    fuserName.SetAON(AND);

    fproject.SetName(SYSTEMLOG_FIELD_NAME_PROJECT);            //设置字段对象fproject名project
    fproject.SetAON(AND);

    flogTime.SetName(SYSTEMLOG_FIELD_NAME_LOGTIME);            //设置字段对象flogTime名logTime
    flogTime.SetAON(AND);

    foperation.SetName(SYSTEMLOG_FIELD_NAME_OPERATION);        //设置字段对象foperation名为operation
    foperation.SetAON(AND);

    fdMessage.SetName(SYSTEMLOG_FIELD_NAME_MESSAGE);
    fdMessage.SetAON(AND);

    LiField cond(QString(SYSTEMLOG_FIELD_NAME_LOGID));         //设置筛选对象
    cond.SetSo(liEqual);
    cond.SetAON(AND);
    cond.SetValue(QString::number(m_logid));  //条件对象比较值

    //设置欲操作的表名
    tb.SetName(SYSTEMLOG_TABLE_NAME);
    dc.SetTableName(SYSTEMLOG_TABLE_NAME);

    //将欲操作的字段，需要添加到LiDataContext
    dc.AddField(&flogID);
    dc.AddField(&fLogLevel);
    dc.AddField(&fuserName);
    dc.AddField(&fproject);
    dc.AddField(&flogTime);
    dc.AddField(&foperation);
    dc.AddField(&fdMessage);
    dc.AddCondition(&cond);                 //添加筛选条件

    if(m_SqlLink != NULL)
    {
        qry = m_SqlLink->sqlQryFct();
    }


    m_info = new SystemLogInfo;

    //执行query命令后，数据会被填充到tb对象内
    qry->query(*m_SqlDb, dc, tb);

    int rownum0 = tb.GetRecords().GetCount();

    if(rownum0 > 0){
        QSqlRecord rd = tb.GetRecords().Next();
        int id  = rd.field(SYSTEMLOG_FIELD_NAME_LOGID).value().toInt();                                    //获取一条记录中flogID字段的值

        if(id == m_logid)
        {
            int level = rd.field(SYSTEMLOG_FIELD_NAME_LOGLEVEL).value().toInt();                           //获取一条记录中fLogLevel字段的值
            string userName = rd.field(SYSTEMLOG_FIELD_NAME_USERNAME).value().toString().toStdString();    //获取一条记录中fuserName字段的值
            string project = rd.field(SYSTEMLOG_FIELD_NAME_PROJECT).value().toString().toStdString();      //获取一条记录中fproject字段的值
            string logTime = rd.field(SYSTEMLOG_FIELD_NAME_LOGTIME).value().toString().toStdString();      //获取一条记录中flogTime字段的值
            string operation = rd.field(SYSTEMLOG_FIELD_NAME_OPERATION).value().toString().toStdString();  //获取一条记录中foperation字段的值
            string message = rd.field(SYSTEMLOG_FIELD_NAME_MESSAGE).value().toString().toStdString();       //获取message字段数据

            QString logtime = QString::fromStdString(logTime);
            QString leftlogtime = logtime.left(10);                     //截取前10个字节
            QString rightlogtime = logtime.right(8);                    //截取后8个字节
            QString LogTime = leftlogtime + " " + rightlogtime;          //合并
            string string_logtime = LogTime.toStdString();


            ((SystemLogInfo*)m_info)->setLogID(id);
            LogLevel Level = ((SystemLogInfo*)m_info)->level_int2enum(level);
            ((SystemLogInfo*)m_info)->setLevel(Level);
            ((SystemLogInfo*)m_info)->setUserName(userName);
            ((SystemLogInfo*)m_info)->setProject(project);                                                  //将获取的fproject字段值其设置成project
            ((SystemLogInfo*)m_info)->setLogTime(string_logtime);
            ((SystemLogInfo*)m_info)->setOperation(operation);
            ((SystemLogInfo*)m_info)->setMessage(message);

        }
        else{
            cout <<"No Records" <<endl;
        }
    }

    LiTable tb1;                                                //数据表类对象
    ISqlQuery *qry1;                                            // ISqlQuery类是我们进行数据库操作的基本类，所有操作都通过它的对象来完成
    LiDataContext dc1;                                          //主函数对象，LiDataContext是操作数据库的操作模板，之后的操作信息都需要添加到其中。
    LiField flogID1,fLogLevel1,fuserName1,fproject1,flogTime1, foperation1,fdMessage1;    //设置数据表字段对象

    flogID1.SetName(SYSTEMLOG_FIELD_NAME_LOGID);                //设置字段对象flogID名logID
    flogID1.SetAON(AND);

    fLogLevel1.SetName(SYSTEMLOG_FIELD_NAME_LOGLEVEL);          //设置字段对象fLogLevel名LogLevel
    fLogLevel1.SetAON(AND);

    fuserName1.SetName(SYSTEMLOG_FIELD_NAME_USERNAME);          //设置字段对象fuserName名serName
    fuserName1.SetAON(AND);

    fproject1.SetName(SYSTEMLOG_FIELD_NAME_PROJECT);            //设置字段对象fproject名project
    fproject1.SetAON(AND);

    flogTime1.SetName(SYSTEMLOG_FIELD_NAME_LOGTIME);            //设置字段对象flogTime名logTime
    flogTime1.SetAON(AND);

    foperation1.SetName(SYSTEMLOG_FIELD_NAME_OPERATION);        //设置字段对象foperation名为operation
    foperation1.SetAON(AND);

    fdMessage1.SetName(SYSTEMLOG_FIELD_NAME_MESSAGE);
    fdMessage1.SetAON(AND);

    LiField condition(QString(SYSTEMLOG_FIELD_NAME_LOGID));     //设置筛选对象
    condition.SetSo(liBigger);
    condition.SetAON(AND);
    condition.SetValue(QString::number(m_logid));               //条件对象比较值

    //设置欲操作的表名
    tb1.SetName(SYSTEMLOG_TABLE_NAME);
    dc1.SetTableName(SYSTEMLOG_TABLE_NAME);

    //将欲操作的字段，需要添加到LiDataContext
    dc1.AddField(&flogID1);
    dc1.AddField(&fLogLevel1);
    dc1.AddField(&fuserName1);
    dc1.AddField(&fproject1);
    dc1.AddField(&flogTime1);
    dc1.AddField(&foperation1);
    dc1.AddField(&fdMessage1);
    dc1.AddCondition(&condition);                 //添加筛选条件

    if(m_SqlLink != NULL)
    {
        qry1 = m_SqlLink->sqlQryFct();
    }

    //执行query命令后，数据会被填充到tb对象内
    qry1->query(*m_SqlDb, dc1, tb1);

    int rownum = tb1.GetRecords().GetCount();    //get all of cout
    if(rownum > 0){
        QSqlRecord rd1 = tb1.GetRecords().Next();
        int ID  = rd1.field(SYSTEMLOG_FIELD_NAME_LOGID).value().toInt();
        m_logid = ID;
    }

    return m_info;
}


/**
 * 实现IReadWriteSystemLog类中ReadALL函数
 * 读全部数据，返回总数
 * @param number
 * @return LogInfo *
 */
ILogInfo * IReadWriteSystemLog::ReadAllLog(int *num)
{

    QFile file(QString::fromStdString(fileName));
    if(!file.exists())
    {
        return NULL;
    }

    LiTable tb;
    ISqlQuery *qry;
    LiDataContext dc;

    if(m_SqlLink != NULL)
        qry = m_SqlLink->sqlQryFct();

    //设置欲操作的表名
    dc.SetTableName(SYSTEMLOG_TABLE_NAME);

    LiField flogID(QString(SYSTEMLOG_FIELD_NAME_LOGID));           //设置字段对象flogID名logID
    LiField fLogLevel(QString(SYSTEMLOG_FIELD_NAME_LOGLEVEL));     //设置字段对象fLogLevel名LogLevel
    LiField fuserName(QString(SYSTEMLOG_FIELD_NAME_USERNAME));     //设置字段对象fuserName名userName
    LiField fproject(QString(SYSTEMLOG_FIELD_NAME_PROJECT));       //设置字段对象fproject名project
    LiField flogTime(QString(SYSTEMLOG_FIELD_NAME_LOGTIME));       //设置字段对象fsubmitTime名fsubmitTime
    LiField foperation(QString(SYSTEMLOG_FIELD_NAME_OPERATION));   //设置字段对象foperation名foperation
    LiField fdMessage(QString(SYSTEMLOG_FIELD_NAME_MESSAGE));

    //将欲操作的字段，需要添加到LiDataContext
    dc.AddField(&flogID);
    dc.AddField(&fLogLevel);
    dc.AddField(&fuserName);
    dc.AddField(&fproject);
    dc.AddField(&flogTime);
    dc.AddField(&foperation);
    dc.AddField(&fdMessage);

    //执行query命令后，数据会被填充到tb对象内
    qry->query(dc, tb);

    //获得数据库表中总数
    *num = tb.GetRecords().GetCount();                   //get all of cout
    int Num  = *num;

    m_info_arry = new SystemLogInfo[Num];

    for(int i = 0; i < Num; i++)
    {
        g_Names << SYSTEMLOG_FIELD_NAME_LOGID << SYSTEMLOG_FIELD_NAME_LOGLEVEL << SYSTEMLOG_FIELD_NAME_USERNAME << SYSTEMLOG_FIELD_NAME_PROJECT
                <<SYSTEMLOG_FIELD_NAME_LOGTIME <<SYSTEMLOG_FIELD_NAME_OPERATION << SYSTEMLOG_FIELD_NAME_MESSAGE;
        QStringList Values;
        Values = tb.GetRecords().NextFields(g_Names);                       //得到一条记录的所有字段的值,Vaules链表的值每次循环是变化的,NextFiled syns with m_info_arry[i],

        ((SystemLogInfo*)m_info_arry)[i].setLogID(Values.at(0).toInt());         //获取一条记录中flogID字段的值，并将其设置进logID

        int lev = Values.at(1).toInt();                                     //获取一条记录中fLogLevel字段的值
        LogLevel level = ((SystemLogInfo*)m_info_arry)[i].level_int2enum(lev);   //将数据库取出的整数值转化为对应的枚举数
        ((SystemLogInfo*)m_info_arry)[i].setLevel(level);                        //将其设置成level

        ((SystemLogInfo*)m_info_arry)[i].setUserName(Values.at(2).toStdString());//获取一条记录中fuserName字段的值，并将其设置成username
        ((SystemLogInfo*)m_info_arry)[i].setProject(Values.at(3).toStdString()); //获取一条记录中fproject字段的值，并将其设置成project

        /*去掉***********SyslogInfo logtime: "2000-02-02T11:11:11" “T”**************** */
        QString logtime = Values.at(4);
        QString leftlogtime = logtime.left(10);                     //截取前10个字节
        QString rightlogtime = logtime.right(8);                    //截取后8个字节
        QString LogTime = leftlogtime + " " + rightlogtime;          //合并
        string string_logtime = LogTime.toStdString();

        ((SystemLogInfo*)m_info_arry)[i].setLogTime(string_logtime); //获取一条记录中flogTime字段的值，并将其设置成logTime
        ((SystemLogInfo*)m_info_arry)[i].setOperation(Values.at(5).toStdString());//获取一条记录中foperation字段的值，并将其设置成operation
        ((SystemLogInfo*)m_info_arry)[i].setMessage(Values.at(6).toStdString());
    }


    delete m_SqlLink;

    return m_info_arry;
}




/**
 * 实现IReadWriteSystemLog类中insert函数
 * @param *newLog
  * @return bool
 */

bool IReadWriteSystemLog::InsertLog(ILogInfo *newLog)
{

    //设置数据表字段对象
    LiField fLogLevel,fuserName,fproject,flogTime, foperation,fdMessage;

    LiDataContext dc;
    ISqlQuery *qry ;                                                        // ISqlQuery类是我们进行数据库操作的基本类，所有操作都通过它的对象来完成

    if(m_SqlLink != NULL)
    {
        qry = m_SqlLink->sqlQryFct();
    }

    //获得插入函数输入值
    int logID = ((SystemLogInfo*)newLog)->getLogID();
    int Loglevel = ((SystemLogInfo*)newLog)->getLogID();
    string username= ((SystemLogInfo*)newLog)->getUserName();
    string project = ((SystemLogInfo*)newLog)->getProject();
    string logtime = ((SystemLogInfo*)newLog)->getLogTime();
    string operation = ((SystemLogInfo*)newLog)->getOperation();
    string message = ((SystemLogInfo*)newLog)->getMessage();

    //设置欲操作的表名
    dc.SetTableName(SYSTEMLOG_TABLE_NAME);


    //    //设置各字段对象的名及对应值
    //    flogID.SetName(SYSTEMLOG_FIELD_NAME_LOGID);
    //    flogID.SetValue(QString::number(logID));

    fLogLevel.SetName(SYSTEMLOG_FIELD_NAME_LOGLEVEL);
    fLogLevel.SetValue(QString::number(Loglevel));

    fuserName.SetName(SYSTEMLOG_FIELD_NAME_USERNAME);
    fuserName.SetValue(QString::fromStdString(username));

    fproject.SetName(SYSTEMLOG_FIELD_NAME_PROJECT);
    fproject.SetValue(QString::fromStdString(project));

    flogTime.SetName(SYSTEMLOG_FIELD_NAME_LOGTIME);
    flogTime.SetValue(QString::fromStdString(logtime));

    foperation.SetName(SYSTEMLOG_FIELD_NAME_OPERATION);
    foperation.SetValue(QString::fromStdString(operation));

    fdMessage.SetName(SYSTEMLOG_FIELD_NAME_MESSAGE);
    fdMessage.SetValue(QString::fromStdString(message));



    //添加到LiDataContext
    //    dc.AddField(&flogID);
    dc.AddField(&fLogLevel);
    dc.AddField(&fuserName);
    dc.AddField(&fproject);
    dc.AddField(&flogTime);
    dc.AddField(&foperation);
    dc.AddField(&fdMessage);

    //当插入正确时返回true，插入失败时返回false
    bool ok = false;
    if((qry->DoInsert(dc)) > 0){
        ok = true;
    }

    delete m_SqlLink;
    return ok;
}




/**
 * 实现IReadWriteSystemLog类中update函数
 * @param *newLog
 * @param logID
 * @return bool
 */
bool IReadWriteSystemLog::UpdateLog(ILogInfo *newLog, int logID)
{
    throw QString("Bin Log not support upd function now!");
    //设置数据表字段对象
    LiField fLogLevel,fuserName,fproject,flogTime, foperation,fdMessage;
    LiField fdCond;     //更新的筛选条件

    LiDataContext dc;
    ISqlQuery *qry ;

    if(m_SqlLink != NULL)
    {
        qry = m_SqlLink->sqlQryFct();
    }

    //获得update函数输入值
    int Loglevel = ((SystemLogInfo*)newLog)->getLevel();
    string username= ((SystemLogInfo*)newLog)->getUserName();
    string project = ((SystemLogInfo*)newLog)->getProject();
    string logtime = ((SystemLogInfo*)newLog)->getLogTime();
    string operation = ((SystemLogInfo*)newLog)->getOperation();
    string message = ((SystemLogInfo*)newLog)->getMessage();

    //设置各字段对象的名及对应值
    fLogLevel.SetName(SYSTEMLOG_FIELD_NAME_LOGLEVEL);
    fLogLevel.SetValue(QString::number(Loglevel));

    fuserName.SetName(SYSTEMLOG_FIELD_NAME_USERNAME);
    fuserName.SetValue(QString::fromStdString(username));

    fproject.SetName(SYSTEMLOG_FIELD_NAME_PROJECT);
    fproject.SetValue(QString::fromStdString(project));

    flogTime.SetName(SYSTEMLOG_FIELD_NAME_LOGTIME);
    flogTime.SetValue(QString::fromStdString(logtime));

    foperation.SetName(SYSTEMLOG_FIELD_NAME_OPERATION);
    foperation.SetValue(QString::fromStdString(operation));

    fdMessage.SetName(SYSTEMLOG_FIELD_NAME_MESSAGE);
    fdMessage.SetValue(QString::fromStdString(message));

    //设置欲操作的表名
    dc.SetTableName(SYSTEMLOG_TABLE_NAME);

    fdCond.SetName(SYSTEMLOG_FIELD_NAME_LOGID);
    fdCond.SetValue(QString::number(logID));
    fdCond.SetAON(AND);         // AON , AND OR NOT
    fdCond.SetSo(liEqual);      // 条件对象比较关系， 大于，小于，等于
    //condition虽然也是LiField，不过作为查询条件的条件语句时，除了字段名外需要设定字段的布尔运算关系(AON),以及布尔运算的计算值

    //添加到LiDataContext
    dc.AddCondition(&fdCond);
    dc.AddField(&fLogLevel);
    dc.AddField(&fuserName);
    dc.AddField(&fproject);
    dc.AddField(&flogTime);
    dc.AddField(&foperation);
    dc.AddField(&fdMessage);

    //当update正确时返回true，插入失败时返回false
    bool ok = false;
    if((qry->DoUpdate(*m_SqlDb, dc)) > 0)
    {
        ok = true;
    }



    return ok;
}

/**
 * 实现IReadWriteSystemLog类中delete函数
 * @param logID
 * @return bool
 */
bool IReadWriteSystemLog::DelLog(int logID)
{
    throw QString("Bin Log not support del function now!");
    LiDataContext dc;
    ISqlQuery *qry ;
    LiField fdCond;                         //筛选删除数据的条件

    if(m_SqlLink != NULL)
    {
        qry = m_SqlLink->sqlQryFct();
    }

    //设置删除条件
    fdCond.SetName(SYSTEMLOG_FIELD_NAME_LOGID);
    fdCond.SetValue(QString::number(logID));
    fdCond.SetAON(AND);
    fdCond.SetSo(liEqual);

    dc.SetTableName(SYSTEMLOG_TABLE_NAME);       //设置欲操作的表名
    dc.AddCondition(&fdCond);               //设置筛选删除数据的条件

    bool ok = false;
    //当delete正确时返回true，插入失败时返回false
    if((qry->DoDel(*m_SqlDb, dc))>0)
    {
        ok = true;
    }

    return ok;
}

QString IReadWriteSystemLog::getFileName()
{


    return QString("SystemLog_Test.log");
}

