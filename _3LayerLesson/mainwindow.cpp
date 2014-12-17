#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DnInterfaceDao *t = new DaoTableStudent();
    QList<QSqlRecord> lRcds;
    for (int i = 0 ; i<3;i++)
    {
        QSqlRecord t;
        QSqlField fId("id",QVariant::Int),fName("Name",QVariant::String)
                ,fAge("Age",QVariant::String);
        fId.setValue(i);
        fName.setValue(QString("name")+QString::number(i));
        fAge.setValue(QString::number(i));
        t.append(fId);
        t.append(fName);
        t.append(fAge);
        lRcds.append(t);
    }
    t->AddRecord(lRcds);
    DnTableModel *m = new DnTableModel;
    m->SetValues(t);
    ui->tvMain->setModel(m);
    //默认显示行头，如果你觉得不美观的话，我们可以将隐藏
    ui->tvMain->verticalHeader()->hide();
    //设置选中时为整行选中
    //    ui->tbNodesList->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置表格的单元为只读属性，即不能编辑
    //    ui->tbNodesList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //如果你用在QTableView中使用右键菜单，需启用该属性
    ui->tvMain->setContextMenuPolicy(Qt::CustomContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}
