#ifndef DNDAO_H
#define DNDAO_H
#include <QStringList>
#include <QString>

class DnInterfaceDao
{
public:
    DnInterfaceDao(DnInterfaceDao &other);
    virtual ~DnInterfaceDao()=0;

    virtual DnInterfaceDao& operator=(DnInterfaceDao& right)=0;
    virtual QStringList GetKeyName()=0;
private:
    QString KeyName;
};

class DaoTableStudent:public DnInterfaceDao
{
public:
    ~DaoTableStudent();
private:
    int PK;
    QString Name;
    QString Student;
};

#endif // DNDAO_H
