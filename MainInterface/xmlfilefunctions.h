/*
 *Copyright@2013 上海青凤致远地球物理地质勘探科技有限公司IT部
 *All Right Reserved
 *
 *简    介：读取数据库配置文件(XML文件)信息功能
 *作    者：
 *完成日期：
 *版 本 号：
 *功 能 类：xmlFileFunctions
 *
 */


#ifndef XMLFILEFUNCTIONS_H
#define XMLFILEFUNCTIONS_H
#include "iostream"
#include "QFile"
#include "QDomDocument"

class xmlFileFunctions
{
public:
    xmlFileFunctions();
    ~xmlFileFunctions();
    void SetFile(QString FileName);                             //设置XML文件
    void SetFile(QString FileName,QString FilePath);            //设置XML文件
    QString GetValueByElementName(QString ElemName, int = 0) const;
    bool OpenFile();                                            //打开XML文件
    bool CloseFile();                                           //关闭XML文件
    struct DBConn
    {
        QString Server;
        QString UserName;
        QString Password;
        QString Database;
        QString Port;
    };
    DBConn GetDBConn() const;                                   //获得XML节点值
    QDomNode GetDBNode(QDomNode InNode) const;
    DBConn GetDBConnByNodeList(QDomNodeList nl,DBConn &result) const;
private:
    QFile * g_File;
};

#endif // XMLFILEFUNCTIONS_H
