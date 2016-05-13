/*
 *Copyright@2013 上海青凤致远地球物理地质勘探科技有限公司
 *All Right Reserved
 *
 *简    介：QModeling程序主界面，基本窗体模块，程序绝大部功能都在此实现（通过直接的代码或者调用其他功能库函数）
 *作    者：GXX
 *完成日期：2013.11.06
 *功能类：
 *          1.MainWindow:QModeling程序主界面类
 *          2.ModuleInfo:收集管理模块信息的类
 *
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"


/********************************************
    Function: MainWindow(QWidget *parent = 0);
    Description: MainInterface的构造函数,实现QModeling软件主界面的显示和初始化,包括1.初始化软件主界面菜单以及tab界面软件模块
                 2.加载内嵌在软件主界面中的窗体 3.初始化工具栏图幅菜单 4.初始化数据库以及相关变量
    Input:None
    Output:None
    Return:None
    Calls:
        1.LoadMenuAndTab();
        2.LoadEmbedWin();
        3.InitialToolBar();
    Called By:None
********************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    try
    {
        m_moduleId = 0;
        pSqlfct = 0;
        xmlFileFunctions xmlFunc;
        xmlFunc.SetFile("../config/system.xml",QCoreApplication::applicationDirPath());
        xmlFunc.OpenFile();
        connstr = xmlFunc.GetDBConn(); // must get xml nodes value before create sql link;
        CreateSqlLink();
        xmlFunc.CloseFile();
        g_Mapper = new QSignalMapper(this);
        ui->setupUi(this);
        m_count = 0;
        m_ProId = -1;                   //initial -1 for all int type globe info
        m_GatId = -1;                   //initial -1 for all int type globe info
        m_sigConn.setOwner(this);       //set this UI to base widget, for all signals cent.


        m_MaxModuleCount = 0;
        m_ModuleCount = 0;
        m_MigrationModuleCount = 0;
        LoadMenuAndTab();               //初始化软件主界面菜单以及tab界面软件模块
        LoadEmbedWin();                 //加载内嵌在软件主界面中的窗体
        InitialToolBar();               //初始化工具栏图幅菜单
    }
    catch (const char* exception)
    {
        QMessageBox::critical(NULL,"System Error",exception);
    }
    catch (const QString exception)
    {
        QMessageBox::critical(NULL,"System Error",exception);
    }
}


/********************************************
    Function:MainWindow::~MainWindow()
    Description:MainInterface的析构函数,处理主窗体关闭时的相关工作
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
MainWindow::~MainWindow()
{
    for (int i = 0; i < lc.count();i++){
        lc.at(i)->m_mmDlg->QMEvent(QM_EVENT_SYSTEM_CLOSE);
    }

    try{
        if (g_Mapper)
            delete g_Mapper;
        if (pSqlfct)
            delete pSqlfct;
        if (m_eDlg)
            delete m_eDlg;
    }
    catch (const char* exception)
    {
        QMessageBox::critical(NULL,"System Error",exception);
    }
    catch (const QString exception)
    {
        QMessageBox::critical(NULL,"System Error",exception);
    }
    catch(...)
    {

    }
}


/********************************************
    Function:void QM_SLOT(int moduleId, int event)
    Description:跨模块信号通信槽, 类似Qt槽函数，用来接收QModeling软件的信号并做处理
    Input:
            1.moduleId：模块编号
            2.event:具体的事件
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::QM_SLOT(int moduleId, int event)
{
    //QM_SLOT same as Qt slot , can connected to QM_Signal (QMDelegate)
    switch (event){
    case QM_EVENT_MODULE_CLOSED:
        for(int i = 0; i < lc.count(); i++){
            if (lc.at(i)->m_mmDlg->GetParamValue(string("moduleid")) == moduleId){
                lc.removeAt(i);
                return;
            }
        }
        qDebug() << "ERROR : QM_SLOT get closed module which not in list , moduleid :" << moduleId;
        break;
    case QM_EVENT_MODULE_PROJECT_CHANGED:

        for (int i= 0; i < lc.count(); i++){
            lc.at(i)->m_mmDlg->QMEvent(QEvent::Type(event));
        }
        break;
    case QM_EVENT_MODULE_SGYDATA_CHANGED:

        for (int i= 0; i < lc.count(); i++){
            lc.at(i)->m_mmDlg->QMEvent(QEvent::Type(event));
        }
        break;
    default:
        qDebug()<< "QM_SLOT switch event is : " << event;
    }

}

/********************************************
    Function:void QM_SLOT_ARGU_1_INT(int , int event, int value)
    Description:跨模块信号通信，带一个整型参数,可以随事件发布可控参数类似Qt槽函数, 用来接收
                QModeling软件的信号并做处理,涉及到工区发生改变时，和数据发生改变时触发
    Input:
    Output:
    Return:
    Calls:
    Called By: 1.slot_getProj_changed(int projId)
               2.slot_getIndexID_changed(int indexID)
********************************************/
void MainWindow::QM_SLOT_ARGU_1_INT(int , int event, int value)
{
    //QM_SLOT same as Qt slot , can connected to QM_Signal (QMDelegate)
    switch (event){
    case QM_EVENT_MODULE_PROJECT_CHANGED:
        setMainTitle(value);
        for (int i= 0; i < lc.count(); i++){
            lc.at(i)->m_mmDlg->QMEvent(QEvent::Type(event),value);
        }
        m_eDlg->GetProjectIDFromMainInterface(value);                 //在其他模块工区发生改变时，影响SideBar
        break;
    case QM_EVENT_MODULE_SGYDATA_CHANGED:
        for (int i= 0; i < lc.count(); i++){
            lc.at(i)->m_mmDlg->QMEvent(QEvent::Type(event),value);
        }

        break;
    default:
        qDebug()<< "QM_SLOT switch event is : " << event;
    }
}

/********************************************
    Function: InitialToolBar()
    Description: 初始化工具栏图幅菜单
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:构造函数
********************************************/
void  MainWindow::InitialToolBar()
{
    m_NewProjectButton = new ButtonThreeStatus;       //新建工区按钮
    m_OpenProjectButton = new ButtonThreeStatus;      //编辑工区按钮
    m_DeleteProjectButton = new ButtonThreeStatus;    //删除工区按钮

    //处理图片路径问题
    QString Path = QApplication::applicationDirPath()+"/";

    //设置按钮图标
    m_NewProjectButton->SetButtonIncons(QIcon(Path+SET_NEWPROJECT_ICON_NORMAL),
                                        QIcon(Path+SET_NEWPROJECT_ICON_NORMAL),
                                        QIcon(Path+SET_NEWPROJECT_ICON_NORMAL));

    m_OpenProjectButton->SetButtonIncons(QIcon(Path+SET_EDITPROJECT_ICON_NORMAL),
                                         QIcon(Path+SET_EDITPROJECT_ICON_FOCUS),
                                         QIcon(Path+SET_EDITPROJECT_ICON_CLICKED));

    m_DeleteProjectButton->SetButtonIncons(QIcon(Path+SET_DELETEPROJECT_ICON_NORMAL),
                                           QIcon(Path+SET_DELETEPROJECT_ICON_FOCUS),
                                           QIcon(Path+SET_DELETEPROJECT_ICON_CLICKED));

    //设置按钮尺寸
    m_NewProjectButton->resize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT);
    m_OpenProjectButton->resize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT);
    m_DeleteProjectButton->resize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT);

    //设置按钮尺寸
    m_NewProjectButton->setIconSize(QSize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT));
    m_OpenProjectButton->setIconSize(QSize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT));
    m_DeleteProjectButton->setIconSize(QSize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT));


    //将按钮添加到工具栏
    ui->toolBar_project->addWidget(m_NewProjectButton);
    ui->toolBar_project->addWidget(m_OpenProjectButton);
    ui->toolBar_project->addWidget(m_DeleteProjectButton);

    m_NewProjectButton->show();
    m_OpenProjectButton->show();
    m_DeleteProjectButton->show();
    ui->toolBar_project->show();

    NewMenu = new QMenu(this);
    NewMenu->addAction(STRING_MENU_PROJECT_NEW_2D, this,SLOT(slot_new_2d()));
    NewMenu->addAction(STRING_MENU_PROJECT_NEW_3D,this,SLOT(slot_new_3d()));
    m_NewProjectButton->setMenu(NewMenu);

    //点击按钮触发相应动作
    //connect(m_NewProjectButton,SIGNAL(clicked(bool)), this, SLOT(slot_PushButton_NewProject()));
    connect(m_OpenProjectButton,SIGNAL(clicked(bool)), this, SLOT(slot_PushButton_Open()));
    connect(m_DeleteProjectButton,SIGNAL(clicked(bool)), this, SLOT(slot_PushButton_DeleteProject()));

    /***********************作业工具栏***********************/
    m_EditJobButton = new ButtonThreeStatus;
    m_CheckJobButton = new ButtonThreeStatus;
    m_SerialJobButton = new ButtonThreeStatus;
    m_ParallelJobButton = new ButtonThreeStatus;
    m_DeleteJobButton = new ButtonThreeStatus;

    //设置按钮图标
    m_EditJobButton->SetButtonIncons(QIcon(Path+SET_EDITJOB_ICON_NORMAL),
                                     QIcon(Path+SET_EDITJOB_ICON_FOCUS),
                                     QIcon(Path+SET_EDITJOB_ICON_CLICKED));

    m_CheckJobButton->SetButtonIncons(QIcon(Path+SET_CHECHJOB_ICON_NORMAL),
                                      QIcon(Path+SET_CHECHJOB_ICON_FOCUS),
                                      QIcon(Path+SET_CHECHJOB_ICON_CLICKED));

    m_SerialJobButton->SetButtonIncons(QIcon(Path+SET_SERIALJOB_ICON_NORMAL),
                                       QIcon(Path+SET_SERIALJOB_ICON_FOCUS),
                                       QIcon(Path+SET_SERIALJOB_ICON_CLICKED));
    m_ParallelJobButton->SetButtonIncons(QIcon(Path+SET_PARALLELJOB_ICON_NORMAL),
                                         QIcon(Path+SET_PARALLELJOB_ICON_FOCUS),
                                         QIcon(Path+SET_PARALLELJOB_ICON_CLICKED));
    m_DeleteJobButton->SetButtonIncons(QIcon(Path+SET_DELETEJOB_ICON_NORMAL),
                                       QIcon(Path+SET_DELETEJOB_ICON_FOCUS),
                                       QIcon(Path+SET_DELETEJOB_ICON_CLICKED));


    //设置按钮尺寸
    m_EditJobButton->resize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT);
    m_CheckJobButton->resize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT);
    m_SerialJobButton->resize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT);
    m_ParallelJobButton->resize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT);
    m_DeleteJobButton->resize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT);

    //设置按钮尺寸
    m_EditJobButton->setIconSize(QSize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT));
    m_CheckJobButton->setIconSize(QSize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT));
    m_SerialJobButton->setIconSize(QSize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT));
    m_ParallelJobButton->setIconSize(QSize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT));
    m_DeleteJobButton->setIconSize(QSize(INT_SIZE_MENU_BUTTON_WIDTH, INT_SIZE_MENU_BUTTON_HIGHT));


    //将按钮添加到工具栏
    ui->toolBar_job->addWidget(m_EditJobButton);
    ui->toolBar_job->addWidget(m_CheckJobButton);
    ui->toolBar_job->addWidget(m_SerialJobButton);
    ui->toolBar_job->addWidget(m_ParallelJobButton);
    ui->toolBar_job->addWidget(m_DeleteJobButton);

    ui->toolBar_job->show();

    connect(m_EditJobButton, SIGNAL(clicked(bool)), this, SLOT(slot_PushButton_EditJob()));
    connect(m_CheckJobButton, SIGNAL(clicked(bool)), this, SLOT(slot_PushButton_CheckJob()));
    connect(m_SerialJobButton, SIGNAL(clicked(bool)), this, SLOT(slot_PushButton_SerialJob()));
    connect(m_ParallelJobButton, SIGNAL(clicked(bool)), this, SLOT(slot_PushButton_ParallelJob()));
    connect(m_DeleteJobButton, SIGNAL(clicked(bool)), this, SLOT(slot_PushButton_DeleteJob()));
}


/********************************************
    Function: bool LoadMenuAndTab()
    Description: 读取菜单及tab栏信息，初始化软件主界面菜单以及tab界面软件模块，Load Menu and Tablist,
    Input:None
    Output:None
    Return:返回读取菜单及tab栏信息是否成功
    Calls: LoadMenuRoot()
    Called By:构造函数
********************************************/
bool MainWindow::LoadMenuAndTab()
{
    //wait
    LoadMenuRoot();
    return true;
}


/********************************************
    Function:bool LoadMenuRoot()
    Description: 读取root级菜单信息
    Input:None
    Output:None
    Return:返回读取root级菜单信息是否成功
    Calls:None
    Called By:LoadMenuAndTab()
********************************************/
bool MainWindow::LoadMenuRoot()
{
    //wait
    try
    {
        //增加菜单
        projectMenu = new QMenu(this);
        projectMenu->setTitle(STRING_MENU_PROJECT);

        seconMenu = new QMenu(projectMenu);                             //工区菜单的二级菜单
        seconMenu->addAction(STRING_MENU_PROJECT_NEW_2D, this,SLOT(slot_new_2d()));
        seconMenu->addAction(STRING_MENU_PROJECT_NEW_3D,this,SLOT(slot_new_3d()));
        seconMenu->setTitle(STRING_MENU_PROJECT_NEW);
        projectMenu->addMenu(seconMenu);

        projectMenu->addAction(QString(STRING_MENU_PROJECT_ACTION_OPNE),this,SLOT(slot_PushButton_Open()) );
        projectMenu->addAction(QString(STRING_MENU_PROJECT_ACTION_OPEN_RECENT),this,SLOT(slot_Project_Menu_Open_Recent()));
        projectMenu->addAction(QString(STRING_MENU_PROJECT_ACTION_EDIT),this, SLOT(slot_PushButton_EditProject()));
        projectMenu->addAction(QString(STRING_MENU_PROJECT_ACTION_DELETE),this,SLOT(slot_PushButton_DeleteProject()));
        projectMenu->addAction(QString(STRING_MENU_PROJECT_ACTION_EXIT),this,SLOT(slot_Project_Menu_Exit()));

        QMenu *moduleMenu = new QMenu(this);
        moduleMenu->setTitle(STRING_MENU_MODULE);

        QMenu *jobMenu = new QMenu(this);
        jobMenu->setTitle(STRING_MENU_JOB);

        QMenu *optionMenu = new QMenu(this);
        optionMenu->setTitle(STRING_MENU_OPTION);

        ui->menuBar->addMenu(projectMenu);                              //将工区菜单添加到菜单栏
        ui->menuBar->addMenu(moduleMenu);
        ui->menuBar->addMenu(jobMenu);
        ui->menuBar->addMenu(optionMenu);

        QMenu *helpMenu = new QMenu(this);
        helpMenu->setTitle(STRING_MENU_HELP);
        helpMenu->addAction(QString(STRING_MENU_HELP), this, SLOT(showQModelingHelp()));
        ui->menuBar->addMenu(helpMenu);

        QSizePolicy spTab(QSizePolicy::Preferred,QSizePolicy::Preferred);
        QString err;
        QString sqlCmd = "SELECT * FROM UnitList WHERE ISROOT = 1";
        sqlWithLicense(sqlCmd);
        sqlCmd += " ORDER BY SortNum";
        //qDebug() <<"lsw print:"<< sqlCmd;
        QSqlQuery qry;
        qry=m_qry->query(sqlCmd);

                        if (qry.size()< 1)
                            throw "Load menu list error,pls check system data!";
        int maxRowNum = 0;
        while (qry.next())
        {
            //create a root menu
            QMenu * RootMenu = new QMenu(moduleMenu);
            RootMenu->setTitle(qry.record().field("UnitName").value().toString());
            moduleMenu->addMenu(RootMenu);
            QWidget * tab = new QWidget(this);
            tab->setSizePolicy(spTab);
            tab->setObjectName(QString::fromUtf8("tab"));
            this->ui->tabWidget->addTab(tab,qry.record().field("UnitName").value().toString());
            m_ModuleName = qry.record().field("UnitName").value().toString();

            QGridLayout *pLo = new QGridLayout(NULL);
            pLo->setObjectName(QString::fromUtf8("GridLayout"));
            tab->setLayout(pLo);
            pLo->setSpacing(0);
            pLo->setMargin(50);
            //than call a recusive function to finish the menu tree under this root
            QSqlQuery qryMenu;
            sqlCmd = "SELECT * FROM UnitList WHERE PARENTID =  "+ qry.record().field("UnitID").value().toString();
            sqlWithLicense(sqlCmd);
            sqlCmd += " ORDER BY SortNum";
            qryMenu = m_qry->query(sqlCmd);
            int iRow = 0;
            int iCol = 0;

            QString Path;
            Path = QApplication::applicationDirPath() + "/../icon/";  // path is what ? delete soon , gxx!
            while (qryMenu.next())
            {
                if (qryMenu.record().field("IsMenu").value().toString() == QString("1"))
                {
                    RootMenu->addMenu(createSubMenu(qryMenu.record().field("UnitName").value().toString()));
                }
                else
                {
                    RootMenu->addAction(LoadUnitDetails(qryMenu.record().field("UnitID").value().toInt(),
                                                        qryMenu.record().field("UnitName").value().toString(),
                                                        this));
                    buildTabIcon(pLo,qryMenu.record(),Path,iRow,iCol,maxRowNum);
                }
            }
            m_SideBarHeight = getTabWidgetHeight(maxRowNum);
            ui->tabWidget->setMaximumHeight(getTabWidgetHeight(maxRowNum));
        }

        m_MaxModuleCount =  m_ModuleCount >= m_MigrationModuleCount ? m_ModuleCount : m_MigrationModuleCount;


        connect(g_Mapper,SIGNAL(mapped(int)),this,SLOT(RunUnitByFileName(int)));//不明白的话好好看看范例，放错位置结果会很怪，add by gxx 2013.11.13
        connect(&m_unitDescMapper,SIGNAL(mapped(QString)),this,SLOT(showUnitDesc(QString)));
        connect(&m_unitHelpMapper,SIGNAL(mapped(QString)),this,SLOT(showUnitHelp(QString)));
    }
    catch (char* exception)
    {
        QMessageBox::critical(NULL,"Query Error Message",exception);
        return false;
    }
    catch (QString exception)
    {
        QMessageBox::critical(NULL,"Query Error Message",exception);
        return false;
    }
    return true;
}


/********************************************
    Function:QAction *LoadUnitDetails(int id, QString utName,QWidget *parent)
    Description:读取动态加载模块信息
    Input:None
    Output:None
    Return:加载模块的信息
    Calls:None
    Called By:None
********************************************/
QAction *MainWindow::LoadUnitDetails(int id, QString utName,QWidget *parent)
{
    QAction * act;
    act = new QAction(utName,parent);
    connect(act,SIGNAL(triggered()),g_Mapper,SLOT(map()));
    g_Mapper->setMapping(act,id);
    return act;
}

/********************************************
    Function:QMenu *createSubMenu(QString menuTitle)
    Description:创建子菜单
    Input:
            1.menuTitle:菜单名
    Output:None
    Return:子菜单
    Calls:None
    Called By:None
********************************************/
QMenu * MainWindow::createSubMenu(QString menuTitle)
{
    QMenu * subMenu = new QMenu;
    subMenu = new QMenu(this);
    subMenu->setTitle(menuTitle);
    return subMenu;
}

/********************************************
    Function:bool LoadStatusInfo()
    Description:读取status信息
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
bool MainWindow::LoadStatusInfo()
{
    return true;
}

/********************************************
    Function:void LoadEmbedWin()
    Description: 加载内嵌在软件主界面中的窗体，包括SideBar和LogBar
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:构造函数
********************************************/
void MainWindow::LoadEmbedWin()
{
    try
    {
        if(m_MaxModuleCount >= INT_MOUDULE_COUNT_0 && m_MaxModuleCount <= INT_MOUDULE_COUNT_4)         //模块个数<4
        {
            this->ui->tabWidget->resize(INT_RIGHTBUTTOB_WIDTH_SIZE, INT_TABWIDGET_WIDTH);
            this->ui->lwRightBottom->resize(INT_RIGHTBUTTOB_WIDTH_SIZE, INT_RIGHTBUTTOB_HEIGHT_SIZE);
            this->ui->lwLeftContain->resize(INT_LEFTBUTTOB_WIDTH_SIZE, INT_LEFTWIDGET_HEIGHT_SIZE_700);
        }
        else if(m_MaxModuleCount >= INT_MOUDULE_COUNT_5 && m_MaxModuleCount <= INT_MOUDULE_COUNT_8)
        {
            this->ui->tabWidget->resize(INT_RIGHTBUTTOB_WIDTH_SIZE, INT_TABWIDGET_WIDTH);
            this->ui->lwRightBottom->resize(INT_RIGHTBUTTOB_WIDTH_SIZE, INT_RIGHTBUTTOB_HEIGHT_SIZE);
            this->ui->lwLeftContain->resize(INT_LEFTBUTTOB_WIDTH_SIZE, INT_LEFTWIDGET_HEIGHT_SIZE_700);

        }
        else if(m_MaxModuleCount >= INT_MOUDULE_COUNT_9 && m_MaxModuleCount <= INT_MOUDULE_COUNT_11)
        {
            this->ui->tabWidget->resize(INT_RIGHTBUTTOB_WIDTH_SIZE, INT_TABWIDGET_WIDTH);
            this->ui->lwRightBottom->resize(INT_RIGHTBUTTOB_WIDTH_SIZE, INT_RIGHTBUTTOB_HEIGHT_SIZE);
            this->ui->lwLeftContain->resize(INT_LEFTBUTTOB_WIDTH_SIZE, INT_LEFTWIDGET_HEIGHT_SIZE_700);

        }
        else if(m_MaxModuleCount == INT_MOUDULE_COUNT_12)
        {
            this->ui->lwRightBottom->resize(INT_RIGHTBUTTOB_WIDTH_SIZE, INT_RIGHTBUTTOB_HEIGHT_SIZE);
            this->ui->lwLeftContain->resize(INT_LEFTBUTTOB_WIDTH_SIZE, INT_LEFTWIDGET_HEIGHT_SIZE_829);
        }
        else if(m_MaxModuleCount >= INT_MOUDULE_COUNT_13 && m_MaxModuleCount <= INT_MOUDULE_COUNT_16)
        {
            this->ui->lwRightBottom->resize(INT_RIGHTBUTTOB_WIDTH_SIZE, INT_RIGHTBUTTOB_HEIGHT_SIZE);
            this->ui->lwLeftContain->resize(INT_LEFTBUTTOB_WIDTH_SIZE, INT_LEFTWIDGET_HEIGHT_SIZE_962);
        }
        else if(m_MaxModuleCount >= INT_MOUDULE_COUNT_17 && m_MaxModuleCount <= INT_MOUDULE_COUNT_20)
        {
            this->ui->lwRightBottom->resize(INT_RIGHTBUTTOB_WIDTH_SIZE, INT_RIGHTBUTTOB_HEIGHT_SIZE);
            this->ui->lwLeftContain->resize(INT_LEFTBUTTOB_WIDTH_SIZE, INT_LEFTWIDGET_HEIGHT_SIZE_1095);
        }

        //        //初始化sidebar,logbar大小
        //        this->ui->lwRightBottom->resize(INT_RIGHTBUTTOB_WIDTH_SIZE, INT_RIGHTBUTTOB_HEIGHT_SIZE);
        //        this->ui->lwLeftContain->resize(INT_LEFTBUTTOB_WIDTH_SIZE, INT_LEFTTBUTTOB_HEIGHT_SIZE);


        QPalette palett;
        palett.setColor(QPalette::Base, QColor(COLOR_RGB_R, COLOR_RGB_G, COLOR_RGB_B));
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// LEFT side bar
        m_eDlg = new SideBar(this->ui->lwLeftContain->x()-INT_LEFT_EMBED_WINDOW_ADJ,this->ui->lwLeftContain->y()-INT_TOP_EMBED_WINDOW_ADJ,
                             this->ui->lwLeftContain->width(),INT_LWLEFTCONTAIN_HEGHT,this->ui->lwLeftContain);
        m_eDlg->SetId(&m_ProId,&m_GatId);
        m_eDlg->SetSQLBase(this->pSqlfct,db);
        m_eDlg->init();
        m_eDlg->show();
        connect(m_eDlg,SIGNAL(signal_Project_changed(int)),this,SLOT(slot_getProj_changed(int)));
        connect(m_eDlg,SIGNAL(signal_IndexID_changed(int)),this,SLOT(slot_getIndexID_changed(int)));
        connect(m_eDlg,SIGNAL(signal_select_unitid(int)),this,SLOT(RunUnitByFileName(int)));

        //connect(m_eDlg,SIGNAL(signal_IndexID_changed(int)),this,SLOT(slot_getProj_changed(int)));

        this->ui->lwLeftContain->setAutoFillBackground(true);
        this->ui->lwLeftContain->setPalette(palett);
        this->ui->lwLeftContain->show();
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// RIGHT-BOTTOM log bar
        m_logDlg = new logBar(INT_LWRIGHTBOTTOM_X,INT_LWRIGHTBOTTOM_Y,this->ui->lwRightBottom->width()+INT_LWRIGHTBOTTOM_WDITH_ADD,this->ui->lwRightBottom->height(),this->ui->lwRightBottom); //
        //m_logDlg = new logBar(0,0,this->ui->lwRightBottom->width(),this->ui->lwRightBottom->height(),this->ui->lwRightBottom);
        m_logDlg->SetSQLBase(pSqlfct,db);
        m_logDlg->Show();
        this->ui->lwRightBottom->setAutoFillBackground(true);
        //        QPalette palett;
        //        palett.setColor(QPalette::Base, QColor(COLOR_RGB_R, COLOR_RGB_G, COLOR_RGB_B));
        this->ui->lwRightBottom->setPalette(palett);
        this->ui->lwRightBottom->show();
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
    catch(const char* err)
    {
        QMessageBox::about(this,"error",err);
    }
    catch(QString err)
    {
        QMessageBox::about(this,"error",err);
    }
}

/********************************************
    Function:void RunUnitByFileName(int id)
    Description:try to load a unit and run it, default search $${PWD} path ,also we can setup path.
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::RunUnitByFileName(int id)
{
    try{
        QString Path;
        Path = QApplication::applicationDirPath() + "/../lib/";  // path is what ? delete soon , gxx!
        QString sPathAndName;
        int unitId;
        string Title;
        for (unsigned int i = 0;i < m_ModuleInfos.size();i++)
        {
            if (m_ModuleInfos[i]->ModuleId == id)
            {
                sPathAndName = Path + m_ModuleInfos[i]->FileName;
                unitId = m_ModuleInfos[i]->ModuleId;
                Title = m_ModuleInfos[i]->Title.toStdString();
            }
        }
        if (sPathAndName.isEmpty())
        {
            QMessageBox::critical(this,"System Error!","Error, system working wrong please connect software support!");
            return;
        }
        // load link file

        void * pHandle = dlopen(sPathAndName.toStdString().c_str(),RTLD_LAZY);
        // catch Exception
        if (!pHandle)
        {
            fprintf (stderr, "dlopen error is: %s\n", dlerror());
            QMessageBox::critical(NULL,"Load Link File Error","Load ["+ sPathAndName +"] failure , may be cause by file lost!");
        }
        //load sub project function
        create_t * crt = (create_t *)dlsym(pHandle,CHARS_QMODEL_BASE_MODULE_CREATE);
        void (*dst)(CommonPlug* p);
        dst = (void (*)(CommonPlug* p)) dlsym(pHandle,CHARS_QMODEL_BASE_MODULE_DESTORY);
        if(!crt)
        {
            QMessageBox::about(NULL,"Load Link File Error","No create");
            return;
        }
        if(!dst)
        {
            QMessageBox::about(NULL,"Load Link File Error","No destory");
            return;
        }
        //user-modules created, initial and jumped out
        CommonPlug* pSub = crt();

        pSub->Set_Num(m_ProId,m_GatId);
        pSub->Set_SqlBase(pSqlfct,db);
        pSub->setCONNECT(&m_sigConn);
        pSub->addPipeParam(string("unitid"),unitId,Title);
        pSub->addPipeParam(string("moduleid"),m_moduleId++,string("module runtime id"));
        lc.append(pSub);
        pSub->CallWidget();
        dst(pSub);
        dlclose(pHandle);

    }
    catch(...){
        dlerror();
    }
}

/********************************************
    Function:void CreateSqlLink()
    Description:初始化数据库，initial sql link type ,will support many SQL type like  XML or MYSQL after edit system.ini node list ,
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::CreateSqlLink()
{
    SqlFunctions sqlfunc;
    Connections conn;
    QString ConnName = "MenuRoot";
    conn.Server = connstr.Server;

    conn.ConnName = ConnName;
    conn.User = connstr.UserName;
    conn.Passwd = connstr.Password;
    conn.Database = connstr.Database;
    if (!pSqlfct)
        sqlfunc.Create(MYSQL,conn,&pSqlfct);
    m_qry = pSqlfct->sqlQryFct();
    db = m_qry->getDB();
}

/********************************************
    Function:void SetBtnIcon(QPushButton *t, QString IconName)
    Description: 设置菜单栏图标及信息
    Input:
            1.QPushButton *t:按钮控件指针
            2.QString IconName:图标名
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::SetBtnIcon(QPushButton *t, QString IconName)
{
    int s = 128;
    QPixmap *pixmap = NULL;
    pixmap = new QPixmap(s,s);
    pixmap->load(IconName);
    QIcon *icon = new QIcon(*pixmap);
    t->setIcon(*icon);
    t->setIconSize(QSize(s,s));
}

/********************************************
    Function:void closeEvent(QCloseEvent *event)
    Description:关闭事件，当存在一些模块窗体没有关闭时，主窗体不能关闭
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::closeEvent(QCloseEvent *event)
{
    if ((lc.count() > 0) || (m_count > 0))          //some module not close yet , can not close mainwindow
    {
        event->ignore();
        QMessageBox::critical(NULL,QString("Warning"), QString("Please close all module dialog!"));
        for (int i= 0; i < lc.count(); i++){
            lc.at(i)->m_mmDlg->QMEvent(QM_EVENT_SYSTEM_CLOSE);
        }
    }
    else
    {
        event->accept();
    }
}

/********************************************
    Function:void resizeEvent(QResizeEvent* event)
    Description: 窗口扩展事件，重新设定主界面大小尺寸,主要涉及侧边栏和LogBar，当主界面长宽尺寸发生变化时起作用
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::resizeEvent(QResizeEvent* )
{
    m_eDlg->get_resize_height_width(ui->lwLeftContain->height(),ui->lwLeftContain->width());
    m_logDlg->get_resize_height_width(ui->lwRightBottom->width(),ui->lwRightBottom->height());
}


/********************************************
    Function:void setMainTitle(int projId)
    Description:设置窗口抬头，根据工区ID，确定工区名，以此工区名作为当前QModeling主界面的标题
    Input:
            1.projId:当前打开工区的工区ID
    Output:None
    Return:None
    Calls:None
    Called By:
********************************************/
void MainWindow::setMainTitle(int projId)
{
    QString projName = getProjName(projId);
    QString title = QString(CHARS_MAIN_TITLE).arg(projName);
    this->setWindowTitle(title);
}

/********************************************
    Function:QString getProjName(int projId)
    Description:获取工区名
    Input:
             1.projId:当前打开工区的工区ID
    Output:None
    Return:获取工区名
    Calls:None
    Called By:None
********************************************/
QString MainWindow::getProjName(int projId)
{

    QStringList fields;
    fields << QString(STRING_PROJECTNO) << QString(PROJECT_NAME);
    LiConditionList cl;
    cl << QString(STRING_PROJECTNO) << projId << liEqual << AND;
    LiResultList rst = m_qry->query(fields,LiTableName(STRING_PROJECTLIST_TABLE),&cl);
    if (rst.getCount() < 1)
    {
        return QString("");
    }
    else
    {
        return rst.at(0,PROJECT_NAME);
    }
}

/********************************************
    Function:int getTabWidgetHeight(int rowNum)
    Description:获取菜单栏高度
    Input:
            1.int rowNum:模块总行数
    Output:None
    Return:菜单栏高度
    Calls:None
    Called By:
********************************************/
int MainWindow::getTabWidgetHeight(int rowNum)
{
    if (rowNum <= 0)
        return INT_HEIGHT_TABWID_BY_ROW * 2; //每个模块必然占用两行
    return rowNum * INT_HEIGHT_TABWID_BY_ROW; //temp code gxx
}

/********************************************
    Function:void slot_getProj_changed(int projId)
    Description:槽函数，当接收到工区发生改变时触发，
    Input: 1.int projId:改变的工区ID
    Output:
    Return:
    Calls: QM_SLOT_ARGU_1_INT(int , int event, int value)
    Called By:
********************************************/
void MainWindow::slot_getProj_changed(int projId)
{
    QM_SLOT_ARGU_1_INT(-1,QM_EVENT_MODULE_PROJECT_CHANGED,projId);

    m_projectID = projId;

    m_eDlg->GetProjectIDFromMainInterface(m_projectID);                 //在其他模块工区发生改变时，影响SideBar
}

/********************************************
    Function:void slot_getIndexID_changed(int indexID)
    Description:槽函数，当接收到数据发生改变时触发，
    Input:1.int indexID:改变的数据索引ID
    Output:
    Return:
    Calls: QM_SLOT_ARGU_1_INT()
    Called By:
********************************************/
void MainWindow::slot_getIndexID_changed(int indexID)
{
    QM_SLOT_ARGU_1_INT(-1,QM_EVENT_MODULE_SGYDATA_CHANGED,indexID);
}

/********************************************
    Function:void slot_PushButton_Open()
    Description:槽函数，菜单栏中点击“Project”菜单中的菜单选项，打开工区
    Input:
    Output:
    Return:
    Calls: slot_projectmanager_new_window()
    Called By:
********************************************/
void MainWindow::slot_PushButton_Open()
{
    openproject = new OpenProject;
    openproject->SetSQLBase(this->pSqlfct,db);
    openproject->show();

    //接收工区发生改变信号
    connect(openproject,SIGNAL(signal_Project_changed(int)),this,SLOT(slot_getProj_changed(int)));

    slot_projectmanager_new_window();
    connect(openproject,SIGNAL(signal_projectmanager_close_window()),this,SLOT(slot_projectmanager_close_window()));
}


/********************************************
    Function:void slot_Project_Menu_Open_Recent()
    Description: 槽函数，菜单栏中点击“Project”菜单中的菜单选项，打开最近打开过的工区
    Input:None
    Output:None
    Return:None
    Calls: slot_projectmanager_new_window();
    Called By:
********************************************/
void MainWindow::slot_Project_Menu_Open_Recent()
{
    m_openRecent = new OpenRecentProject;
    m_openRecent->SetSQLBase(this->pSqlfct,db);
    m_openRecent->GetOpenRecentProjectList(m_qry);
    m_openRecent->show();
    //接收工区发生改变信号
    connect(m_openRecent,SIGNAL(signal_Project_changed(int)),this,SLOT(slot_getProj_changed(int)));

    slot_projectmanager_new_window();
    connect(m_openRecent,SIGNAL(signal_projectmanager_close_window()),this,SLOT(slot_projectmanager_close_window()));

}


/********************************************
    Function:void slot_Project_Menu_Exit()
    Description:槽函数，菜单栏中点击“Project”菜单中的菜单选项，退出菜单
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:
********************************************/
void MainWindow::slot_Project_Menu_Exit()
{
    int qry = QMessageBox::question(NULL, "Exit", "Sure to  exit?", QMessageBox::Yes, QMessageBox::No);
    if(qry == QMessageBox::Yes)
        this->close();
    else if(qry == QMessageBox::No)
        return;

}


/********************************************
    Function:void slot_PushButton_NewProject()
    Description:槽函数，点击“新建工区”按钮触发，新建2D/3D工区
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::slot_PushButton_NewProject()
{

    //    m_menu = new CMenu;
    //    m_menu->setWindowModality(Qt::WindowModal);
    //    m_menu->SetSQLBase(pSqlfct, db);
    //    m_menu->setWindowModality(Qt::ApplicationModal);
    //    m_menu->Show();

    //二级菜单
    //    seconMenu = new QMenu(projectMenu);
    //    seconMenu->addAction("New 2D", this,SLOT(slot_new_2d()));
    //    seconMenu->addAction("New 3D",this,SLOT(slot_new_3d()));
    //    projectMenu->addMenu(seconMenu);
}


/********************************************
    Function:void slot_new_2d()
    Description:新建2D工区
    Input:None
    Output:None
    Return:None
    Calls:  slot_new_New2DNameAndPath();
    Called By:None
********************************************/
void MainWindow::slot_new_2d()
{
    New2DNameAndPath *new2d = new New2DNameAndPath;
    new2d->SetSQLBase(pSqlfct, db);
    new2d->show();

    slot_new_New2DNameAndPath();                        //执行New2DNameAndPath窗口++操作
    connect(new2d,SIGNAL(signal_close_New2DNameAndPath()),this,SLOT(slot_close_New2DNameAndPath()));
}

/********************************************
    Function:void slot_new_3d()
    Description:新建3D工区
    Input:None
    Output:None
    Return:None
    Calls:slot_projectmanager_new_window();
    Called By:None
********************************************/
void MainWindow::slot_new_3d()
{
    New3DNameAndPath *new3d = new New3DNameAndPath;
    new3d->SetSQLBase(pSqlfct, db);
    new3d->show();

    slot_projectmanager_new_window();
    connect(new3d,SIGNAL(signal_projectmanager_close_window()),this,SLOT(slot_projectmanager_close_window()));
}




/********************************************
    Function:void slot_new_New2DNameAndPath()
    Description:槽函数,记录工区管理时打开窗体的总个数,弹出时触发
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
    Others:此部分，功能与slot_projectmanager_new_window()重复，以后得优化下20160509
********************************************/
void MainWindow::slot_new_New2DNameAndPath()
{
    m_count++;
}


/********************************************
    Function:void slot_close_New2DNameAndPath()
    Description:槽函数,记录工区管理时打开窗体的总个数,关闭时触发
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
    Others:此部分，功能与slot_projectmanager_new_window()重复，以后得优化下20160509
********************************************/
void MainWindow::slot_close_New2DNameAndPath()
{
    m_count--;
}


/********************************************
    Function:void showDynIconMenu(QObject *info)
    Description:show unit's dynmic icon (at right-middle area) menu list;
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::showDynIconMenu(QObject *info)
{
    QMenu *mnu = new QMenu(this);
    ModuleInfo *temp = static_cast<ModuleInfo*>(info);
    mnu->setGeometry(temp->pt().x(),temp->pt().y(),INT_DYNMICON_WIDTH,INT_DYNMICON_HEIGHT);
    mnu->addAction(LoadUnitDetails(temp->ModuleId,QString(STRING_DYNMICON_MENU_ACT_RUN),mnu));
    //create show desc action
    QAction *actShowDesc = new QAction(QString(STRING_DYNMICON_MENU_ACT_DESC),mnu);
    connect(actShowDesc,SIGNAL(triggered(bool)),&m_unitDescMapper,SLOT(map()));
    m_unitDescMapper.setMapping(actShowDesc,temp->unitDesc);
    mnu->addAction(actShowDesc);

    //create help action
    QAction *actHelp = new QAction(QString(STRING_DYNMICON_MENU_ACT_HELP),mnu);
    connect(actHelp,SIGNAL(triggered(bool)),&m_unitHelpMapper,SLOT(map()));
    //m_unitHelpMapper.setMapping(actShowDesc,temp->UnitName());
    //    m_unitHelpMapper.setMapping(actShowDesc,temp->Title);
    m_unitHelpMapper.setMapping(actHelp,temp->Title);
    mnu->addAction(actHelp);

    mnu->show();
}


/********************************************
    Function:void showUnitHelp(QString utName)
    Description:显示各模块的帮助信息
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::showUnitHelp(QString utName)
{
    Assistant temp;
    temp.showModuleAssistant(utName);
}


/********************************************
    Function:void showQModelingHelp()
    Description: 显示模块的帮助信息
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::showQModelingHelp()
{
    Assistant temp;
    temp.showModuleAssistant("2D_RTM");
}


/********************************************
    Function:void slot_projectmanager_new_window()
    Description:  槽函数,记录工区管理时打开窗体的总个数,弹出时触发
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::slot_projectmanager_new_window()
{
    m_count++;
}


/********************************************
    Function:void slot_projectmanager_close_window()
    Description:槽函数,记录工区管理时打开窗体的总个数,关闭时触发
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::slot_projectmanager_close_window()
{
    m_count--;
}


/********************************************
    Function: void slot_get_projectmanager_id(int ProjectID)
    Description: 槽函数，获取工区ID
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::slot_get_projectmanager_id(int ProjectID)
{
    m_projectID = ProjectID;
}

/********************************************
    Function:void slot_PushButton_EditProject()
    Description:槽函数，点击“编辑工区”按钮触发，编辑工区功能
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::slot_PushButton_EditProject()
{
    m_editProject = new EditProject;
    m_editProject->SetSQLBase(pSqlfct, db);

}


/********************************************
    Function:void slot_PushButton_DeleteProject()
    Description:槽函数，点击“删除工区”按钮触发，删除工区及其工区所在目录功能
    Input:None
    Output:None
    Return:None
    Calls: slot_projectmanager_new_window();
    Called By:None
********************************************/
void MainWindow::slot_PushButton_DeleteProject()
{
    m_deleteProject = new DeleteProject;
    m_deleteProject->setWindowModality(Qt::WindowModal);
    m_deleteProject->SetSQLBase(pSqlfct, db);
    m_deleteProject->show();

    slot_projectmanager_new_window();
    connect(m_deleteProject,SIGNAL(signal_projectmanager_close_window()),this,SLOT(slot_projectmanager_close_window()));
}

/********************************************
    Function:void slot_PushButton_EditJob()
    Description:槽函数, 编辑作业
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::slot_PushButton_EditJob()
{
    QMessageBox::about(this, "To be achieved", "This Button is to be achieved");
}

/********************************************
    Function:void slot_PushButton_CheckJob()
    Description: 槽函数，检查作业
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::slot_PushButton_CheckJob()
{
    QMessageBox::about(this, "To be achieved", "This Button is to be achieved");
}

/********************************************
    Function:void slot_PushButton_SerialJob()
    Description: 槽函数, 串行提交作业
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::slot_PushButton_SerialJob()
{
    QMessageBox::about(this, "To be achieved", "This Button is to be achieved");
}

/********************************************
    Function:void slot_PushButton_ParallelJob()
    Description:槽函数，并行作业文件
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::slot_PushButton_ParallelJob()
{
    QMessageBox::about(this, "To be achieved", "This Button is to be achieved");
}

/********************************************
    Function:void slot_PushButton_DeleteJob()
    Description: 槽函数，删除作业文件
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void MainWindow::slot_PushButton_DeleteJob()
{
    QMessageBox::about(this, "To be achieved", "This Button is to be achieved");
}

/********************************************
    Function:void QM_SignalConnector::setOwner(QWidget *q)
    Description:
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void QM_SignalConnector::setOwner(QWidget *q)
{
    m_owner = q;
    this->m_signal = MakeDelegate((MainWindow*)m_owner,&MainWindow::QM_SLOT);
    this->m_signal_argu_1 = MakeDelegate((MainWindow*)m_owner,&MainWindow::QM_SLOT_ARGU_1_INT);
}



