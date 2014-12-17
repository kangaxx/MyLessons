#ifndef DNDAO_H
#define DNDAO_H
#include <vector>

#include <QStringList>
#include <QString>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
using namespace std;

class DnInterfaceDao
{
public:
    DnInterfaceDao(DnInterfaceDao &other);
    DnInterfaceDao();
    virtual ~DnInterfaceDao()=0;

    virtual DnInterfaceDao& operator=(DnInterfaceDao& right)=0;
    virtual QStringList GetKeyName()=0;
    virtual QStringList GetFieldNames()=0;
    virtual int GetRowCount() = 0;
    virtual int GetColumnCount() = 0;
    virtual QString GetStr(int r,int c) = 0;
    virtual QVariant GetSpecValue(int r, int c) = 0;
    virtual void AddRecord(QList<QSqlRecord> &rcd) = 0;


};

class DaoTableStudent:public DnInterfaceDao
{
public:
    ~DaoTableStudent();
    DaoTableStudent();
    DnInterfaceDao& operator=(DnInterfaceDao& right);
    QStringList GetKeyName();
    QStringList GetFieldNames();
    int GetRowCount();
    int GetColumnCount();
    QString GetStr(int r, int c);
    QVariant GetSpecValue(int r, int c);
    void AddRecord(QList<QSqlRecord> &rcd);
private:
    int PK;
    QString KeyName;
    struct stc_Student{
        int Id;
        QString Name;
        QString Age;
    };
    vector<stc_Student> m_Data;
    static const int mc_ColumnCount = 4;// Carefully!
};

#endif // DNDAO_H
