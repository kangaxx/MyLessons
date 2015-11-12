#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include "commonfunction_c.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setDbType(MYSQL);
    m_dbTemplate = QString("<database name=\"%1\">\n%2</database>");
    m_tableTemplate = QString("  <table name=\"%1\">\n    <promptys>\n%2    </promptys>\n  </table>\n");
    m_promTemplate = QString("      <prompty value=\"%1\" type=\"%2\"/>\n");
    this->ui->edtIniFile->setText(BaseFunctions::getConfigPath());
    this->ui->tbMain->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doGenerator()
{
    if (!doCheckOption()){
        QMessageBox::critical(this,QString("Error Message"),QString("Error , can not generator files!"));
        return ;
    }
    switch(m_dbType){
    case MYSQL:
        if (createIniFile()==true)
            QMessageBox::about(this,tr("Create file"), tr("Create file success"));
        else
            QMessageBox::about(this,tr("Create file"), tr("Create file fail"));
        break;
    case XML:
        if (ui->tbMain->currentIndex() == 0){
            if (createIniFile()==true)
                QMessageBox::about(this,tr("Create file"), tr("Create file success"));
            else
                QMessageBox::about(this,tr("Create file"), tr("Create file fail"));
        }
        else{
            if (createXmlFile()==true)
                QMessageBox::about(this,tr("Create file"), tr("Create file success"));
            else
                QMessageBox::about(this,tr("Create file"), tr("Create file fail"));
        }
    }
}

bool MainWindow::doCheckOption()
{

    switch(m_dbType){
    case MYSQL:
        return checkIniParam();
    case XML:
        if (ui->tbMain->currentIndex() == 0)
            return checkIniParam() ;
        else
            return checkXmlParam();
    default:
        qDebug() << "Error : check option get fail dbtype";
        return false;
    }


}

void MainWindow::choiceFilePath(int fileType)
{

    switch(fileType){
    case INT_OPEN_FILEPATH_TYPE_INI:
        setIniFileName();
        break;
    case INT_OPEN_FILEPATH_TYPE_XML:
        setXmlFileName();
        break;
    default:
        qDebug()<< "Error : choice file type error!";
        return;
    }


}

void MainWindow::setXmlFileName()
{
    QStringList sl = QFileDialog::getOpenFileNames(this,QString("Open File"),BaseFunctions::getConfigPath(),tr(".xml"));
    if (sl.count() <= 0){
        return;
    }
    else
    {
        QString fileName = sl.at(0) + QString(".xml");
        ui->edtXmlFile->setText(fileName);
    }
}

void MainWindow::setIniFileName()
{
    QStringList sl = QFileDialog::getOpenFileNames(this,QString("Open File"),BaseFunctions::getConfigPath(),tr(".ini"));
    if (sl.count() <= 0){
        return;
    }
    else
    {
        QString fileName = sl.at(0) + QString(".ini");
        ui->edtIniFile->setText(fileName);
    }
}

bool MainWindow::createXmlFile()
{
    QString str = geneDatabaseString(m_db);
    QFile file(ui->edtXmlFile->text());
    if (file.exists()){
        switch(QMessageBox::question(this,tr("Quest :file exits"),tr("Xml file exits , do you want overwrite it?"),QMessageBox::Yes|QMessageBox::Cancel)){
        case QMessageBox::Yes:
            break;
        case QMessageBox::Cancel:
            return false;
            break;
        default:
            qDebug()<< "warning : create ini file get error msgbox return value!";
            return false;
        }
    }
    if (file.open(QIODevice::ReadWrite))
    {
        file.write(str.toStdString().c_str());
        file.close();
        return true;
    }
    else
        QMessageBox::critical(this,tr("Error"),tr("Error:Ini file write error , open failed!"));
    return false;
}

void MainWindow::insertPromToTable(prompty pty)
{
    m_table.appendPty(pty);
}

void MainWindow::insertTableToDB(table tbl)
{
    m_db.appendTable(tbl);
}

void MainWindow::updateXmlListCtrl()
{
    vector<prompty>::iterator itProm;
    ui->edtPromList->clear();
    for(itProm = m_table.ptyList.begin();itProm != m_table.ptyList.end();itProm++){
        ui->edtPromList->append((*itProm).value +  QString(" {%1}").arg(ui->cboPromType->itemText((*itProm).type)));
    }

    vector<table>::iterator itTbl;
    ui->edtTableList->clear();
    for(itTbl = m_db.tbList.begin();itTbl != m_db.tbList.end();itTbl++){
        ui->edtTableList->append((*itTbl).tableName);
        for(itProm = (*itTbl).ptyList.begin();itProm!=(*itTbl).ptyList.end();itProm++){
            ui->edtTableList->append(QString("...prom:%1").arg((*itProm).value));
        }
    }
}

bool MainWindow::createIniFile()
{
    QFile file(ui->edtIniFile->text());
    if (file.exists()){
        switch(QMessageBox::question(this,tr("Quest :file exits"),tr("Ini file exits , do you want overwrite it?"),QMessageBox::Yes|QMessageBox::Cancel)){
        case QMessageBox::Yes:
            break;
        case QMessageBox::Cancel:
            return false;
            break;
        default:
            qDebug()<< "warning : create ini file get error msgbox return value!";
            return false;
        }
    }
    if (file.open(QIODevice::ReadWrite))
    {
        file.write((m_iniTemplate.arg(ui->edtServerOrFile->text()).arg(ui->edtUser->text())
                   .arg(ui->edtPassWord->text()).arg(ui->edtDatabase->text())).toStdString().c_str());
        file.close();
        return true;
    }
    else
        QMessageBox::critical(this,tr("Error"),tr("Error:Ini file write error , open failed!"));
    return false;
}

bool MainWindow::checkIniParam()
{
    if (ui->edtIniFile->text().trimmed().isEmpty() ||
            ui->edtDatabase->text().trimmed().isEmpty() ||
            ui->edtServerOrFile->text().trimmed().isEmpty() ||
            ui->edtUser->text().trimmed().isEmpty() ||
            ui->edtPassWord->text().trimmed().isEmpty())
        return false;
    else
        return true;
}

bool MainWindow::checkXmlParam()
{
    return true;
}

QString MainWindow::genePromString(table parent)
{
    vector<prompty>::iterator it;
    QString rst;
    for(it=parent.ptyList.begin();it!=parent.ptyList.end();it++){
        rst += m_promTemplate.arg((*it).value).arg(ui->cboPromType->itemText((*it).type));
    }
    qDebug() << "prom str:" << rst;
    return rst;
}

QString MainWindow::geneTableString(table tbl)
{
    QString promStr;
    QString rst = m_tableTemplate;

    promStr += genePromString(tbl);

    rst = rst.arg(tbl.tableName).arg(promStr);
    qDebug()<<"table str:" <<rst;
    return rst;

}

QString MainWindow::geneDatabaseString(database parent)
{
    QString rst,tableStr;
    vector<table>::iterator it;
    for(it=parent.tbList.begin();it!=parent.tbList.end();it++){
        tableStr += geneTableString(*it);
    }
    rst = m_dbTemplate.arg(parent.dbName).arg(tableStr);
    qDebug() << rst;
    return rst;
}

void MainWindow::on_bbMain_clicked(QAbstractButton *button)
{
    if (ui->bbMain->button(QDialogButtonBox::Apply) == button)
        doGenerator();
}

void MainWindow::setDbType(eFctType type)
{
    m_dbType = type;
    switch(type){
    case MYSQL:
        ui->rdbtnMysql->setChecked(true);
        ui->edtXmlFile->setDisabled(true);
        ui->pgXmlFile->setDisabled(true);
        ui->btnXmlFileChoice->setDisabled(true);
        ui->lblServerOrFile->setText(tr("server"));
        m_iniTemplate = QString("server=%1\nusername=%2\npassword=%3\ndatabase=%4");
        break;
    case XML:
        ui->rdbtnXml->setChecked(true);
        ui->pgXmlFile->setDisabled(false);
        ui->edtXmlFile->setDisabled(false);
        ui->btnXmlFileChoice->setDisabled(false);
        ui->lblServerOrFile->setText(tr("file"));
        m_iniTemplate = QString("connname=%1\nusername=%2\npassword=%3\ndatabase=%4");
        break;
    default:
        QMessageBox::critical(this,tr("Error Message"),tr("Error: db type no exits!"));
    }
}


void MainWindow::on_rdbtnMysql_clicked()
{
    setDbType(MYSQL);

}

void MainWindow::on_rdbtnXml_clicked()
{
    setDbType(XML);
}

void MainWindow::on_btnIniFileChoice_clicked()
{
    choiceFilePath(INT_OPEN_FILEPATH_TYPE_INI);
}

void MainWindow::on_btnXmlFileChoice_clicked()
{
    choiceFilePath(INT_OPEN_FILEPATH_TYPE_XML);
}

void MainWindow::on_edtInsertPrompty_clicked()
{
    if (ui->edtPromValue->text().trimmed().isEmpty()){
        QMessageBox::critical(this,tr("Error"),tr("Error, must input valid prompty value!"));
        return;
    }

    prompty pty;
    pty.value= ui->edtPromValue->text().trimmed();
    pty.type = ui->cboPromType->currentIndex();

    insertPromToTable(pty);
    updateXmlListCtrl();
    ui->edtPromValue->clear();
    ui->cboPromType->setCurrentIndex(0);
}

void MainWindow::on_btnInsertTable_clicked()
{
    if (ui->edtTableName->text().trimmed().isEmpty()){
        QMessageBox::critical(this,tr("Error"),tr("Error, must input valid table name!"));
        return;
    }
    m_table.tableName = ui->edtTableName->text().trimmed();
    insertTableToDB(m_table);
    updateXmlListCtrl();
    ui->edtTableName->clear();
    ui->edtPromList->clear();
    m_table.ptyList.clear();
}
