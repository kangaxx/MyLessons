
/*
 *Copyright@2013 上海青凤致远地球物理地质勘探科技有限公司
 *All Right Reserved
 *
 *简    介：QModeling 程序主界面。
 *作    者：GXX
 *完成日期：2013.11.06
 *功能类：ModuleInfo        收集管理模块信息的类

 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <dlfcn.h>
#include <QMainWindow>
#include <QSignalMapper>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QMenu>
#include <QAction>
#include "commonplug.h"
#include "xmlfilefunctions.h"
#include "sqlfunctions.h"
#include "sidebar.h"
#include "logBar.h"
#include "projectmanagerso.h"
#include "buttonthreestatus.h"
#include "qmessagebox.h"
#include "commonfunctions.h"
#include "QCoreApplication"
#include "QLabel"
#include "Assistant.h"
#include "commonfunction_c.h"


#define INT_LEFT_EMBED_WINDOW_ADJ 9
#define INT_TOP_EMBED_WINDOW_ADJ 20
#define INT_LEFT_LOGBAR_WINDOW_ADJ 9
#define INT_TOP_LOGBAR_WINDOW_ADJ 0

#define INT_SIZE_MENU_BUTTON_WIDTH  20          //图幅菜单按钮大小，宽
#define INT_SIZE_MENU_BUTTON_HIGHT  20          //图幅菜单按钮大小，高

#define INT_LWLEFTCONTAIN_HEGHT 600

#define INT_LWRIGHTBOTTOM_X     -10
#define INT_LWRIGHTBOTTOM_Y     -12
#define INT_LWRIGHTBOTTOM_WDITH_ADD     10

#define COLOR_RGB_R     245
#define COLOR_RGB_G     245
#define COLOR_RGB_B     245

#define STRING_MENU_PROJECT                     "Project"           //工区菜单名
#define STRING_MENU_PROJECT_ACTION_OPNE         "&Open"             //“打开工区”菜单的名称
#define STRING_MENU_PROJECT_ACTION_OPEN_RECENT  "&Open Recent"      //“打开最近访问过的工区”菜单的名称
#define STRING_MENU_PROJECT_ACTION_NEW          "&New"              //“新建工区”菜单的名称
#define STRING_MENU_PROJECT_ACTION_EDIT         "&Edit"             //“编辑工区”菜单的名称
#define STRING_MENU_PROJECT_ACTION_DELETE       "&Delete"           //“删除工区”菜单的名称
#define STRING_MENU_PROJECT_ACTION_EXIT         "&Exit"             //“退出”菜单的菜单的名称
#define STRING_MENU_PROJECT_NEW                 "New"               //“新建工区”菜单的名称
#define STRING_MENU_PROJECT_NEW_2D              "New 2D"            //“新建2D工区”菜单的名称
#define STRING_MENU_PROJECT_NEW_3D              "New 3D"            //“新建3D工区”菜单的名称

#define STRING_MENU_MODULE                       "Module"           //“模块”菜单的名称
#define STRING_MENU_JOB                         "Job"               //“作业”菜单的名称
#define STRING_MENU_OPTION                      "Option"            //“选项”菜单的名称
#define STRING_MENU_HELP                        "Help"              //“帮助文档”菜单的名称

/*新建工区按钮的三态图标*/
#define SET_NEWPROJECT_ICON_NORMAL      "../icon/addproject_normal.png"         //正常情况下，新建工区按钮的图标
#define SET_NEWPROJECT_ICON_FOCUS       "../icon/addproject_fcous.png"          //鼠标在按钮上时，新建工区按钮的图标
#define SET_NEWPROJECT_ICON_CLICKED     "../icon/addproject_clicked.png"        //点击情况下，新建工区按钮的图标

/*编辑工区按钮的三态图标*/
#define SET_EDITPROJECT_ICON_NORMAL     "../icon/editproject_normal.PNG"         //正常情况下，编辑工区按钮的图标
#define SET_EDITPROJECT_ICON_FOCUS      "../icon/editproject_focus.PNG"          //鼠标在按钮上时，编辑工区按钮的图标
#define SET_EDITPROJECT_ICON_CLICKED    "../icon/editproject _clicked.PNG"       //点击情况下，编辑工区按钮的图标

/*删除工区按钮的三态图标*/
#define SET_DELETEPROJECT_ICON_NORMAL   "../icon/deleteproject_normal.PNG"      //正常情况下，删除工区按钮的图标
#define SET_DELETEPROJECT_ICON_FOCUS    "../icon/deleteproject_focus.PNG"       //鼠标在按钮上时，删除工区按钮的图标
#define SET_DELETEPROJECT_ICON_CLICKED  "../icon/deleteproject_clicked.PNG"     //点击情况下，删除工区按钮的图标

/*编辑作业按钮的三态图标*/
#define SET_EDITJOB_ICON_NORMAL    "../icon/editjob_icon_normal.PNG"            //正常情况下，编辑作业按钮的图标
#define SET_EDITJOB_ICON_FOCUS     "../icon/editjob_icon_focus.PNG"             //鼠标在按钮上时，编辑作业按钮的图标
#define SET_EDITJOB_ICON_CLICKED   "../icon/editjob_icon_clicked.PNG"           //点击情况下，编辑作业按钮的图标

/*检查作业按钮的三态图标*/
#define SET_CHECHJOB_ICON_NORMAL    "../icon/checkjob_icon_normal.PNG"          //正常情况下，检查作业按钮的图标
#define SET_CHECHJOB_ICON_FOCUS     "../icon/checkjob_icon_focus.PNG"           //鼠标在按钮上时，检查作业按钮的图标
#define SET_CHECHJOB_ICON_CLICKED   "../icon/checkjob_icon_clicked.PNG"         //点击情况下，检查作业按钮的图标

/*串行提交作业按钮的三态图标*/
#define SET_SERIALJOB_ICON_NORMAL    "../icon/serialjob_icon_normal.png"        //正常情况下，串行提交作业按钮的图标
#define SET_SERIALJOB_ICON_FOCUS     "../icon/serialjob_icon_focus.png"         //鼠标在按钮上时，串行提交作业按钮的图标
#define SET_SERIALJOB_ICON_CLICKED   "../icon/serialjob_icon_clicked.png"       //点击情况下，串行提交作业按钮的图标

/*并行提交作业按钮的三态图标*/
#define SET_PARALLELJOB_ICON_NORMAL    "../icon/paralleljob_icon_normal.PNG"    //正常情况下，并行提交作业按钮的图标
#define SET_PARALLELJOB_ICON_FOCUS     "../icon/paralleljob_icon_focus.PNG"     //鼠标在按钮上时，并行提交作业按钮的图标
#define SET_PARALLELJOB_ICON_CLICKED   "../icon/paralleljob_icon_clicked.PNG"   //点击情况下，并行提交作业按钮的图标

/*删除作业按钮的三态图标*/
#define SET_DELETEJOB_ICON_NORMAL    "../icon/deletejob_icon_normal.png"        //正常情况下，删除作业按钮的图标
#define SET_DELETEJOB_ICON_FOCUS     "../icon/deletejob_icon_focus.png"         //鼠标在按钮上时，删除作业按钮的图标
#define SET_DELETEJOB_ICON_CLICKED   "../icon/deletejob_icon_clicked.png"       //点击情况下，删除作业按钮的图标

#define STRING_ICOM_LOCATE      "../icon"
#define CHARS_MAIN_TITLE    "QModeling 1.0 |Project: %1"                        //QModeling主界面标题
#define INT_HEIGHT_TABWID_BY_ROW    200                                         //每行高度

#define INT_RIGHTBUTTOB_WIDTH_SIZE  730                                         //右边控件宽
#define INT_RIGHTBUTTOB_HEIGHT_SIZE  100                                        //右边控件高
#define INT_LEFTBUTTOB_WIDTH_SIZE  289                                          //左边控件宽
#define INT_LEFTTBUTTOB_HEIGHT_SIZE  900                                        //左边控件高

#define INT_TABWIDGET_WIDTH     400                                             //tabwidget宽
#define INT_LEFTWIDGET_HEIGHT_SIZE_700  700                                     //左边控件高
#define INT_LEFTWIDGET_HEIGHT_SIZE_829  829
#define INT_LEFTWIDGET_HEIGHT_SIZE_962  962
#define INT_LEFTWIDGET_HEIGHT_SIZE_1095  1095

/*加载模块的个数*/
#define INT_MOUDULE_COUNT_0     0
#define INT_MOUDULE_COUNT_4     4
#define INT_MOUDULE_COUNT_5     5
#define INT_MOUDULE_COUNT_8     8
#define INT_MOUDULE_COUNT_9     9
#define INT_MOUDULE_COUNT_11    11
#define INT_MOUDULE_COUNT_12    12
#define INT_MOUDULE_COUNT_13    13
#define INT_MOUDULE_COUNT_16    16
#define INT_MOUDULE_COUNT_17    17
#define INT_MOUDULE_COUNT_20    20

#define INT_DYNMICON_WIDTH 80                                                   //模块上图标宽
#define INT_DYNMICON_HEIGHT 120                                                 //模块上图标高

#define STRING_DYNMICON_MENU_ACT_RUN    "Run"                                   //模块上右击run菜单名称1
#define STRING_DYNMICON_MENU_ACT_DESC   "Show Description"                      //模块上右击显示信息菜单名称
#define STRING_DYNMICON_MENU_ACT_HELP   "Help"                                  //模块上右击help菜单名称


namespace Ui {
class MainWindow;
}


/*该类是模块信息的集合体，使用该类来保存每一个功能类的各种信息，保持一致功能的集中，易于维护*/
class ModuleInfo :public QObject
{
    Q_OBJECT
public:
    ModuleInfo(ModuleInfo &other){
        if (this != &other){
            this->FileName = other.FileName;
            this->ModuleId = other.ModuleId;
            this->Title = other.Title;
            this->m_btn = other.m_btn;
            (*(other.m_cpy))++;
            this->m_cpy = other.m_cpy;
        }
    }
    ModuleInfo(){m_btn == NULL;m_cpy = NULL;}
    ~ModuleInfo(){
        //M_CPY record how many copy construct be called , delete m_btn and m_cpy after all copy mi deleted!
        if (m_cpy != NULL && *m_cpy > 0){
            (*m_cpy)--;
            if (*m_cpy == 0 ){
                if (m_btn != NULL)
                    delete m_btn;
                delete m_cpy;
            }
        }
    }

    ModuleInfo &operator =(ModuleInfo &right){
        if (this != &right){
            this->FileName = right.FileName;
            this->ModuleId = right.ModuleId;
            this->Title = right.Title;
            this->m_btn = right.m_btn;
            (*(right.m_cpy))++;
            this->m_cpy = right.m_cpy;
        }
        return *this;
    }

    QString FileName;                               //文件名
    int ModuleId;                                   //模块编号
    QString Title;                                  //标题
    QString unitDesc;                               //模块描述
    QString UnitName(){return FileName;}            //获取文件名

    void setBtn(QPushButton *pb){m_btn = pb;}       //设置按钮
    QPoint pt(){
        if (m_btn == NULL)
            return QPoint(0,0);
        return m_btn->mapToGlobal(QPoint(m_btn->width()-2,2));
    }
    void slotLeftclick();
private:
    QPushButton *m_btn;
    int *m_cpy;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void QM_SLOT(int moduleId,int event);                   //跨模块信号通信槽      //same as Qt signal and slot , QM slot can connect to QM_Main signal
    void QM_SLOT_ARGU_1_INT(int, int event, int value);     //this slot have one int argument

private:
    Ui::MainWindow *ui;
    QSignalMapper * g_Mapper;
    QSignalMapper m_unitDescMapper;                         //for unit(dynm icon) description!
    QSignalMapper m_unitHelpMapper;                         //for unit(dynm icon) help!
    xmlFileFunctions::DBConn connstr;                       //数据库连接信息

    bool LoadMenuAndTab();                                  //读取菜单及tab栏信息   //初始化软件主界面菜单以及tab界面软件模块，Load Menu and Tablist
    bool LoadMenuRoot();                                    //读取root级菜单信息
    QAction *LoadUnitDetails(int id, QString utName, QWidget *parent= 0);           //读取动态加载模块信息
    QMenu *createSubMenu(QString menuTitle);                //创建子菜单
    bool LoadStatusInfo();                                  //读取status信息
    void LoadEmbedWin();                                    //加载内嵌在软件主界面中的窗体
    void InitialToolBar();                                  //初始化工具栏图幅菜单
    void SetBtnIcon(QPushButton *, QString IconName);       //设置菜单栏图标及信息
    void closeEvent(QCloseEvent *event);                    //关闭事件，当存在一些模块窗体没有关闭时，主窗体不能关闭
    void resizeEvent(QResizeEvent* event);                  //窗口扩展事件，重新设定主界面大小尺寸,主要涉及侧边栏和LogBar，当主界面长宽尺寸发生变化时起作用
    void setMainTitle(int projId);                          //设置窗口抬头，根据工区ID，确定工区名，以此工区名作为当前QModeling主界面的标题
    QString getProjName(int projId);                        //获取工区名
    int getTabWidgetHeight(int rowNum);                     //获取菜单栏高度

    SideBar *m_eDlg;                                        //侧边栏控件指针
    logBar *m_logDlg;                                       //LogBar控件指针
    enum ParentType{Menu,Tab};
    QList<CommonPlug*> lc;                                  //模块列表
    static const int c_MaxRow=4;
    static const int c_MaxCol=4;
    vector<ModuleInfo*> m_ModuleInfos;                      //模块信息的集合体

signals:
    void signals_project_id_changed(int ProjectID);         //工区改变信号

public slots:
    void slot_close_New2DNameAndPath();                     //槽函数,记录工区管理时打开窗体的总个数,关闭时触发
    void slot_new_New2DNameAndPath();                       //槽函数,记录工区管理时打开窗体的总个数,弹出时触发
    void slot_projectmanager_close_window();                //槽函数,记录工区管理时打开窗体的总个数,关闭时触发
    void slot_projectmanager_new_window();                  //槽函数,记录工区管理时打开窗体的总个数,弹出时触发
    void slot_get_projectmanager_id(int ProjectID);         //槽函数，获取工区ID

private slots:
    void slot_getProj_changed(int projId);                  //槽函数，当接收到工区发生改变时触发
    void slot_getIndexID_changed(int indexID);              //槽函数，当接收到数据发生改变时触发，
    void RunUnitByFileName(int id);                         //try to load a unit and run it, default search $${PWD} path ,also we can setup path.

    void slot_PushButton_Open();                            //槽函数，菜单栏中点击“Project”菜单中的菜单选项，打开工区
    void slot_Project_Menu_Open_Recent();                   //槽函数，菜单栏中点击“Project”菜单中的菜单选项，打开最近打开过的工区
    void slot_Project_Menu_Exit();                          //槽函数，菜单栏中点击“Project”菜单中的菜单选项，退出菜单

    void slot_PushButton_NewProject();                      //槽函数，点击“新建工区”按钮触发，新建2D/3D工区
    void slot_PushButton_EditProject();                     //槽函数，点击“编辑工区”按钮触发，编辑工区功能
    void slot_PushButton_DeleteProject();                   //槽函数，点击“删除工区”按钮触发，删除工区及其工区所在目录功能

    void slot_new_2d();                                     //新建2D工区
    void slot_new_3d();                                     //新建3D工区

    void slot_PushButton_EditJob();                         //槽函数, 编辑作业
    void slot_PushButton_CheckJob();                        //槽函数，检查作业
    void slot_PushButton_SerialJob();                       //槽函数, 串行提交作业
    void slot_PushButton_ParallelJob();                     //槽函数，并行作业文件
    void slot_PushButton_DeleteJob();                       //槽函数，删除作业文件
    
    void showDynIconMenu(QObject *);                    //for dynm btn show Menu!
    void showUnitDesc(QString desc){ QMessageBox::about(this,QString("Unit Description"),desc);}
    //void showUnitHelp(QString utName){Assistant temp; temp.showModuleAssistant(utName);}
    void showUnitHelp(QString utName);                      //显示各模块的帮助信息
    void showQModelingHelp();                               //显示模块的帮助信息

private:
    /*数据库指针*/
    FSqlFactory * pSqlfct;
    ISqlQuery *m_qry;
    QSqlDatabase *db;

    int m_ProId;                                    //工区ID
    int m_GatId;
    int m_moduleId;                                 //模块编号
    int m_SideBarHeight;                            //侧边栏高度
    int m_MaxModuleCount;                           //模块最大数量
    int m_ModuleCount;                              //模块数量
    int m_MigrationModuleCount;                     //偏移模块数量
    QString m_ModuleName;                           //模块名


    //针对工区
    ButtonThreeStatus *m_NewProjectButton;          //新建工区按钮
    ButtonThreeStatus *m_EditProjectButton;         //编辑工区按钮
    ButtonThreeStatus *m_DeleteProjectButton;       //删除工区按钮
    ButtonThreeStatus *m_OpenProjectButton;         //打开工区按钮
    ButtonThreeStatus *m_ThreeStstusButton;

    //针对作业
    ButtonThreeStatus *m_EditJobButton;             //编辑作业按钮
    ButtonThreeStatus *m_CheckJobButton;            //检查作业按钮
    ButtonThreeStatus *m_SerialJobButton;           //串行作业按钮
    ButtonThreeStatus *m_ParallelJobButton;         //并行作业按钮
    ButtonThreeStatus *m_DeleteJobButton;           //删除作业按钮

    DeleteProject *m_deleteProject;                 //删除工区浏览工区文件控件指针
    EditProject *m_editProject;                     //编辑工区浏览工区文件控件指针
    CMenu *m_menu;
    SideBar *m_openSideBar;
    OpenRecentProject *m_openRecent;                //打开最近访问浏览工区控件指针
    OpenProject *openproject;                       //打开浏览工区控件指针
    Assistant *assistant;                           //帮助文档指针
    QMenu *NewMenu;
    QMenu *projectMenu;
    QMenu *seconMenu;
    QMenu *help;
    QM_SignalConnector m_sigConn;                   //for modules and main interface signal system
    QM_SIGNAL m_sig;
    void createMenu();
    int m_count;                                    //记录工区管理界面打开的个数
    int m_projectID;

    void sqlWithLicense(QString &cmd){
        if (SqlFunctions::dayInLicense(INT_LICENSE_TYPE, INT_LICENSE_DATE_BEGIN, INT_LICENSE_DATE_DAYS))
            cmd += QString(" AND 1=1 ");
        else
            cmd += QString(" AND 1=2 ");
    }

    void CreateSqlLink();           //initial sql link type ,will support many SQL type like  XML or MYSQL after edit system.ini node list ,
    inline void buildTabIcon(QGridLayout *pLo,const QSqlRecord &record,QString Path ,int &iRow, int &iCol, int &maxRowNum){
        QPushButton * btn;
        QLabel *lbl;
        QSizePolicy spLbl(QSizePolicy::Minimum, QSizePolicy::Minimum);
        QSizePolicy spBtn(QSizePolicy::Minimum, QSizePolicy::Minimum);
        spBtn.setHorizontalStretch(0);
        spBtn.setVerticalStretch(0);
        spLbl.setHorizontalStretch(0);
        spLbl.setVerticalStretch(0);
        lbl = new QLabel(record.field("UnitName").value().toString().toUtf8());
        lbl->setText(record.field("UnitName").value().toString().toUtf8());
        lbl->setToolTip(record.field("UnitName").value().toString().toUtf8());
        lbl->setMaximumSize(QSize(150,16777215));
        lbl->setSizePolicy(spLbl);
        lbl->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        btn = new QPushButton(QString(""),NULL);
        btn->setObjectName(record.field("UnitName").value().toString().toUtf8());
        btn->setMaximumSize(QSize(120,120));
        btn->setSizePolicy(spBtn);
        btn->setToolTip(record.field("UnitDesc").value().toString().toUtf8());
        btn->setContextMenuPolicy(Qt::CustomContextMenu);
        QString iconName = Path+record.field("Icon").value().toString().toUtf8();
        SetBtnIcon(btn,iconName);

        pLo->addWidget(btn,iRow,iCol,1,1);
        pLo->addWidget(lbl,iRow+1,iCol,1,1);
        ModuleInfo *temp= new ModuleInfo;
        temp->FileName = record.field("SoName").value().toString();
        temp->ModuleId = record.field("UnitID").value().toInt();
        temp->Title = record.field("UnitName").value().toString();
        temp->unitDesc = record.field("UnitDesc").value().toString();
        temp->setBtn(btn);
        m_ModuleInfos.push_back(temp);
        connect(btn,SIGNAL(clicked()),g_Mapper,SLOT(map()));
        connect(btn, SIGNAL(customContextMenuRequested(QPoint)), &m_unitDescMapper, SLOT(map()));
        g_Mapper->setMapping(btn,temp->ModuleId);
        m_unitDescMapper.setMapping(btn,temp);
        connect(&m_unitDescMapper,SIGNAL(mapped(QObject*)),this,SLOT(showDynIconMenu(QObject*)));
        //        connect(btn, SIGNAL(customContextMenuRequested(QPoint)), &m_moduleIconMapper, SLOT(map()));

        //        m_moduleIconMapper.setMapping(btn,mi);
        //        connect(&m_moduleIconMapper,SIGNAL(mapped(QObject*)),this,SLOT(showDynBtnMenu(QObject*)));
        iCol++;


        if(m_ModuleName == QString("Tomo modules"))
        {
            m_ModuleCount++;
        }
        else if(m_ModuleName == QString("Migration modules"))
        {
            m_MigrationModuleCount++;
        }

        if (iCol>c_MaxCol-1) //每行最大
        {
            iCol -= c_MaxCol;
            iRow=iRow+2;
        }
        maxRowNum = maxRowNum > iRow - 2 ? maxRowNum:iRow-2;
        //maxRowNum = maxRowNum > iRow ? maxRowNum:iRow;
    }
};

#endif // MAINWINDOW_H
