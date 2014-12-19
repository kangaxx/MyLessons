#ifndef DNSERVER_H
#define DNSERVER_H
#include <QtSql/QSqlRecord>
#include <QList>
#include <dndao.h>
#include <dnserver.h>
#include <qmessagebox.h>

#include <sqlfunctions.h>
class DnInterfaceServer
{
public:
    DnInterfaceServer();
    virtual ~DnInterfaceServer()=0;
    virtual bool AppendRecord(DnInterfaceDao *dao)=0;

};

class DnStudentServer:public DnInterfaceServer
{
public:
    DnStudentServer(FSqlFactory *f);
    ~DnStudentServer();
    bool AppendRecord(DnInterfaceDao *dao);
private:
    QList<QSqlRecord> m_Records;
    void GetData();
    FSqlFactory *m_pSqlfct=0;
};

#endif // DNSERVER_H
