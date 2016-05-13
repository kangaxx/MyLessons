/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ModuleInfo_t {
    QByteArrayData data[1];
    char stringdata[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModuleInfo_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModuleInfo_t qt_meta_stringdata_ModuleInfo = {
    {
QT_MOC_LITERAL(0, 0, 10) // "ModuleInfo"

    },
    "ModuleInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModuleInfo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ModuleInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ModuleInfo::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ModuleInfo.data,
      qt_meta_data_ModuleInfo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ModuleInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModuleInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ModuleInfo.stringdata))
        return static_cast<void*>(const_cast< ModuleInfo*>(this));
    return QObject::qt_metacast(_clname);
}

int ModuleInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[34];
    char stringdata[659];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 26), // "signals_project_id_changed"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 9), // "ProjectID"
QT_MOC_LITERAL(4, 49, 27), // "slot_close_New2DNameAndPath"
QT_MOC_LITERAL(5, 77, 25), // "slot_new_New2DNameAndPath"
QT_MOC_LITERAL(6, 103, 32), // "slot_projectmanager_close_window"
QT_MOC_LITERAL(7, 136, 30), // "slot_projectmanager_new_window"
QT_MOC_LITERAL(8, 167, 26), // "slot_get_projectmanager_id"
QT_MOC_LITERAL(9, 194, 20), // "slot_getProj_changed"
QT_MOC_LITERAL(10, 215, 6), // "projId"
QT_MOC_LITERAL(11, 222, 23), // "slot_getIndexID_changed"
QT_MOC_LITERAL(12, 246, 7), // "indexID"
QT_MOC_LITERAL(13, 254, 17), // "RunUnitByFileName"
QT_MOC_LITERAL(14, 272, 2), // "id"
QT_MOC_LITERAL(15, 275, 20), // "slot_PushButton_Open"
QT_MOC_LITERAL(16, 296, 29), // "slot_Project_Menu_Open_Recent"
QT_MOC_LITERAL(17, 326, 22), // "slot_Project_Menu_Exit"
QT_MOC_LITERAL(18, 349, 26), // "slot_PushButton_NewProject"
QT_MOC_LITERAL(19, 376, 27), // "slot_PushButton_EditProject"
QT_MOC_LITERAL(20, 404, 29), // "slot_PushButton_DeleteProject"
QT_MOC_LITERAL(21, 434, 11), // "slot_new_2d"
QT_MOC_LITERAL(22, 446, 11), // "slot_new_3d"
QT_MOC_LITERAL(23, 458, 23), // "slot_PushButton_EditJob"
QT_MOC_LITERAL(24, 482, 24), // "slot_PushButton_CheckJob"
QT_MOC_LITERAL(25, 507, 25), // "slot_PushButton_SerialJob"
QT_MOC_LITERAL(26, 533, 27), // "slot_PushButton_ParallelJob"
QT_MOC_LITERAL(27, 561, 25), // "slot_PushButton_DeleteJob"
QT_MOC_LITERAL(28, 587, 15), // "showDynIconMenu"
QT_MOC_LITERAL(29, 603, 12), // "showUnitDesc"
QT_MOC_LITERAL(30, 616, 4), // "desc"
QT_MOC_LITERAL(31, 621, 12), // "showUnitHelp"
QT_MOC_LITERAL(32, 634, 6), // "utName"
QT_MOC_LITERAL(33, 641, 17) // "showQModelingHelp"

    },
    "MainWindow\0signals_project_id_changed\0"
    "\0ProjectID\0slot_close_New2DNameAndPath\0"
    "slot_new_New2DNameAndPath\0"
    "slot_projectmanager_close_window\0"
    "slot_projectmanager_new_window\0"
    "slot_get_projectmanager_id\0"
    "slot_getProj_changed\0projId\0"
    "slot_getIndexID_changed\0indexID\0"
    "RunUnitByFileName\0id\0slot_PushButton_Open\0"
    "slot_Project_Menu_Open_Recent\0"
    "slot_Project_Menu_Exit\0"
    "slot_PushButton_NewProject\0"
    "slot_PushButton_EditProject\0"
    "slot_PushButton_DeleteProject\0slot_new_2d\0"
    "slot_new_3d\0slot_PushButton_EditJob\0"
    "slot_PushButton_CheckJob\0"
    "slot_PushButton_SerialJob\0"
    "slot_PushButton_ParallelJob\0"
    "slot_PushButton_DeleteJob\0showDynIconMenu\0"
    "showUnitDesc\0desc\0showUnitHelp\0utName\0"
    "showQModelingHelp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  144,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  147,    2, 0x0a /* Public */,
       5,    0,  148,    2, 0x0a /* Public */,
       6,    0,  149,    2, 0x0a /* Public */,
       7,    0,  150,    2, 0x0a /* Public */,
       8,    1,  151,    2, 0x0a /* Public */,
       9,    1,  154,    2, 0x08 /* Private */,
      11,    1,  157,    2, 0x08 /* Private */,
      13,    1,  160,    2, 0x08 /* Private */,
      15,    0,  163,    2, 0x08 /* Private */,
      16,    0,  164,    2, 0x08 /* Private */,
      17,    0,  165,    2, 0x08 /* Private */,
      18,    0,  166,    2, 0x08 /* Private */,
      19,    0,  167,    2, 0x08 /* Private */,
      20,    0,  168,    2, 0x08 /* Private */,
      21,    0,  169,    2, 0x08 /* Private */,
      22,    0,  170,    2, 0x08 /* Private */,
      23,    0,  171,    2, 0x08 /* Private */,
      24,    0,  172,    2, 0x08 /* Private */,
      25,    0,  173,    2, 0x08 /* Private */,
      26,    0,  174,    2, 0x08 /* Private */,
      27,    0,  175,    2, 0x08 /* Private */,
      28,    1,  176,    2, 0x08 /* Private */,
      29,    1,  179,    2, 0x08 /* Private */,
      31,    1,  182,    2, 0x08 /* Private */,
      33,    0,  185,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QObjectStar,    2,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->signals_project_id_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_close_New2DNameAndPath(); break;
        case 2: _t->slot_new_New2DNameAndPath(); break;
        case 3: _t->slot_projectmanager_close_window(); break;
        case 4: _t->slot_projectmanager_new_window(); break;
        case 5: _t->slot_get_projectmanager_id((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_getProj_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slot_getIndexID_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->RunUnitByFileName((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slot_PushButton_Open(); break;
        case 10: _t->slot_Project_Menu_Open_Recent(); break;
        case 11: _t->slot_Project_Menu_Exit(); break;
        case 12: _t->slot_PushButton_NewProject(); break;
        case 13: _t->slot_PushButton_EditProject(); break;
        case 14: _t->slot_PushButton_DeleteProject(); break;
        case 15: _t->slot_new_2d(); break;
        case 16: _t->slot_new_3d(); break;
        case 17: _t->slot_PushButton_EditJob(); break;
        case 18: _t->slot_PushButton_CheckJob(); break;
        case 19: _t->slot_PushButton_SerialJob(); break;
        case 20: _t->slot_PushButton_ParallelJob(); break;
        case 21: _t->slot_PushButton_DeleteJob(); break;
        case 22: _t->showDynIconMenu((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 23: _t->showUnitDesc((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: _t->showUnitHelp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 25: _t->showQModelingHelp(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::signals_project_id_changed)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::signals_project_id_changed(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
