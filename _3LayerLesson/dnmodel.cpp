#include "dnmodel.h"
#include "QDebug"

DnInterfaceModel::~DnInterfaceModel()
{
    //do nothing , because of c++ inherit system.
}




DnTableModel::DnTableModel(QObject *parent)
{
//
}

void DnTableModel::SetValues(DnInterfaceDao *t)
{
    this->mp_Dao = t;
}


int DnTableModel::rowCount(const QModelIndex &parent) const
{
    return mp_Dao->GetRowCount();
}

int DnTableModel::columnCount(const QModelIndex &parent) const
{
    return mp_Dao->GetColumnCount();
}

QVariant DnTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.column() >= mp_Dao->GetColumnCount())
        return QVariant();
    if (role == Qt::DisplayRole)
        return mp_Dao->GetStr(index.row(),index.column());
    if (role == Qt::CheckStateRole && index.column() == 3)
        return QVariant(mp_Dao->GetSpecValue(index.row(),index.column()));
    return QVariant();
}

QVariant DnTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (section < mp_Dao->GetFieldNames().count())
        return mp_Dao->GetFieldNames().at(section);
    else
        return QString("Column%1").arg(section);
    return QVariant();
}

bool DnTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        return true ;
    }

    return false ;
}

Qt::ItemFlags DnTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable;
}

QStringList DnTableModel::GetKeyName()
{
    QStringList result;
    return result;
}


