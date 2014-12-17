#ifndef DNMODEL_H
#define DNMODEL_H
#include <QAbstractTableModel>

#include "dndao.h"

class DnInterfaceModel
{
public:
    virtual ~DnInterfaceModel()=0;
    virtual QStringList GetKeyName()=0;
};


class DnTableModel :public DnInterfaceModel ,public QAbstractTableModel
{
public:
    DnTableModel(QObject *parent=0);
    void SetValues(DnInterfaceDao *t);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QStringList GetKeyName();
private:
    DnInterfaceDao * mp_Dao;
    QStringList m_HeaderList;
    QString GetStrValue(int,int) const;
};

#endif // DNMODEL_H
