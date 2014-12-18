#include "basefunctions.h"
#include <unistd.h>
#include <QMessageBox>
#include <string.h>
#include "comdefine.h"

basefunctions::basefunctions()
{
    //do nothing yet;
}

void basefunctions::GetSqlLink(QString FileName, QString ConnName, Connections &Conn)
{

    QString IniFileName = STR_GET_EXECPATH + QString("/") + FileName;
    QFile f;
    f.setFileName(IniFileName);
    if (!f.exists())
        throw "File not exists,pls check it!";

    if (!f.open(QFile::ReadOnly))
        throw "File["+IniFileName+"] not open,pls check the it!";
    f.seek(0);
    char buf[1024];

    qint64 lineLength = f.readLine(buf,sizeof(buf));//first line is Server
    if (lineLength < 0)
        throw "Read Ini file error!";
    if (lineLength > 0)
        Conn.Server = QString::fromLatin1(buf).replace("\n","\0");

    lineLength = f.readLine(buf,sizeof(buf));//second line, UserName
    if (lineLength < 0)
        throw "Read Ini file error!";
    if (lineLength > 0)
        Conn.User = QString::fromLatin1(buf).replace("\n","\0");

    lineLength = f.readLine(buf,sizeof(buf));//third line , Password
    if (lineLength < 0)
        throw "Read Ini file error!";
    if (lineLength > 0)
        Conn.Passwd = QString::fromLatin1(buf).replace("\n","\0");


    lineLength = f.readLine(buf,sizeof(buf));//third line , Database
    if (lineLength < 0)
        throw "Read Ini file error!";
    if (lineLength > 0)
        Conn.Database = QString::fromLatin1(buf).replace("\n","\0");

    f.close();
    int t = rand();

    Conn.ConnName = ConnName;
}

QString basefunctions::GetExePath_Linux()
{
    QString Ret("");
#ifdef liunx
    char buf[1024] = { 0 };
    int n;

    n = readlink("/proc/self/exe" , buf , sizeof(buf));
    std::string t(buf);
    t = t.substr(0,t.find_last_of('/'));
    if( n > 0 && n < sizeof(buf))
        Ret = QString::fromStdString(t);
    else
        throw QString("Get program path error!");
#endif
    return Ret;
}

QString basefunctions::GetExePath_Win32()
{
    QString Ret("");
#ifdef WIN32
    QDir TheDir;
    Ret = TheDir.currentPath();

#endif
    return Ret;
}

