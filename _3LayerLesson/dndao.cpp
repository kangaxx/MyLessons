#include "dndao.h"
DnInterfaceDao::~DnInterfaceDao()
{
    //do nothing
}


DnInterfaceDao &DnInterfaceDao::operator=(DnInterfaceDao &right)
{
    if (this == &right)
        return *this;
}


DnInterfaceDao::DnInterfaceDao(DnInterfaceDao &other)
{
    //do nothing yet
}

DnInterfaceDao::DnInterfaceDao()
{
    // do nothing yet
}

DaoTableStudent::~DaoTableStudent()
{
    //do nothing yet
}

DaoTableStudent::DaoTableStudent()
{

}

DnInterfaceDao &DaoTableStudent::operator=(DnInterfaceDao &right)
{
    if (this == &right)
        return *this;
}

QStringList DaoTableStudent::GetKeyName()
{
    QStringList result;
    result << "Id";
    return result;
}

QStringList DaoTableStudent::GetFieldNames()
{
    QStringList result;
    result << "Id" << "Name" << "Age";
    return result;
}

int DaoTableStudent::GetRowCount()
{
    return this->m_Data.size();
}

int DaoTableStudent::GetColumnCount()
{
    return mc_ColumnCount;
}

QString DaoTableStudent::GetStr(int r, int c)
{
    switch(c)
    {
    case 0:
        return QString::number(m_Data[r].Id);
    case 1:
        return m_Data[r].Name;
    case 2:
        return m_Data[r].Age;
    default:
        return QString("");
        break;
    }
}

QVariant DaoTableStudent::GetSpecValue(int r, int c)
{
    Qt::CheckState t;
    if (c == 3) return QVariant(t);
    else return QVariant();
}

void DaoTableStudent::AddRecord(QList<QSqlRecord> &rcd)
{
    for(int i = 0;i<rcd.count();i++)
    {
        stc_Student t;
        t.Id = rcd[i].field("id").value().toInt();
        t.Name = rcd[i].field("name").value().toString();
        t.Age = rcd[i].field("age").value().toString();
        this->m_Data.push_back(t);
    }
}



