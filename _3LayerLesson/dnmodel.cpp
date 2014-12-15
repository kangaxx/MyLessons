#include "dnmodel.h"
DnInterfaceModel::~DnInterfaceModel()
{
    //do nothing , because of c++ inherit system.
}


void DnTableModel::SetValues(DnInterfaceDao *t)
{
    this->mp_Dao = t;
}

void DnTableModel::SetHeaders()
{
    //    do nothing , yet!
}

int DnTableModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int DnTableModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant DnTableModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QVariant DnTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

bool DnTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
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

