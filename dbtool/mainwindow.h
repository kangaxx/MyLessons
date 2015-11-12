#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialogButtonBox>

#include "sqlfunctions.h"
#define INT_OPEN_FILEPATH_TYPE_INI 1
#define INT_OPEN_FILEPATH_TYPE_XML 2
#define INT_PROMPTY_TYPE_IDENT 0
#define INT_PROMPTY_TYPE_UNIQUE 1

namespace Ui {
class MainWindow;
}

struct prompty{
    QString value;
    int type;
};

struct table{
    void appendPty(prompty pty){
        ptyList.push_back(pty);
    }

    QString tableName;
    vector<prompty> ptyList;
};

struct database{
    void appendTable(table tbl){
        tbList.push_back(tbl);
    }

    QString dbName;
    vector<table> tbList;
};



class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void doGenerator();
    bool doCheckOption();

private slots:
    void on_bbMain_clicked(QAbstractButton *button);

    void on_rdbtnMysql_clicked();

    void on_rdbtnXml_clicked();

    void on_btnIniFileChoice_clicked();

    void on_btnXmlFileChoice_clicked();

    void on_edtInsertPrompty_clicked();

    void on_btnInsertTable_clicked();

private:
    void choiceFilePath(int fileType);
    void setXmlFileName();
    void setIniFileName();

    void insertPromToTable(prompty pty); //insert pty value into m_table member
    void insertTableToDB(table tbl); //insert value to member
    void updateXmlListCtrl();  //update edtPromList and edtTableList controls text
    bool createIniFile();
    bool createXmlFile();
    bool checkIniParam();
    bool checkXmlParam();
    QString genePromString(table parent);
    QString geneTableString(table tbl);
    QString geneDatabaseString(database parent);
    eFctType readDbType() const {return m_dbType;}
    void setDbType(eFctType type);
    Ui::MainWindow *ui;
    eFctType m_dbType;
    QString m_iniTemplate;
    QString m_dbTemplate;
    QString m_tableTemplate;
    QString m_promTemplate;
    table m_table;
    database m_db;
};

#endif // MAINWINDOW_H
