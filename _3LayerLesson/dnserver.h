#ifndef DNSERVER_H
#define DNSERVER_H
#include <QtSql/QSqlRecord>

class DnInterfaceServer
{
public:
    DnInterfaceServer();
    virtual AppendRecord(List<QSqlRecord> &rcd);
};

#endif // DNSERVER_H
