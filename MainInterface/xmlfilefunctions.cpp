#include "xmlfilefunctions.h"
#include "QXmlStreamReader"
#include "qxmlstream.h"
#include "QFile"
#include "QDomDocument"
#include "QMessageBox"


xmlFileFunctions::xmlFileFunctions()
{
    g_File = 0;
}


xmlFileFunctions::~xmlFileFunctions()
{
    try
    {
        if (g_File)
        {
            if (g_File->isOpen())
                g_File->close();
            delete g_File;
        }
    }
    catch (...)
    {
    }
}


/********************************************
    Function:void SetFile(QString FileName, QString FilePath)
    Description: 设置XML文件
    Input:
            1.QString FileName:文件名
            2.QString FilePath:文件路径
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
void xmlFileFunctions::SetFile(QString FileName, QString FilePath)
{
    if((FileName.trimmed().isEmpty()) || (FilePath.trimmed().isEmpty()))
        throw "FileName or FilePath is invalid!";
    g_File = new QFile;
    g_File->setFileName(FilePath+"/"+FileName);
    if (!g_File->exists())
        throw "File not exists,pls check it!";
}


/********************************************
    Function:void SetFile(QString FileName)
    Description: 设置XML文件
    Input:
            1.QString FileName:文件名
    Output:None
    Return:None
    Calls:SetFile();
    Called By:None
********************************************/
void xmlFileFunctions::SetFile(QString FileName)
{
    if (FileName.trimmed().isEmpty())
        throw "FileName is invalid!";
    SetFile(FileName,".");
}


/********************************************
    Function:bool OpenFile()
    Description: 打开XML文件
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
bool xmlFileFunctions::OpenFile()
{
    if (!g_File)
        throw "Open fail,File was not initialization!";
    if (g_File->isOpen())
        throw "File already opened,can not open again!";
    if (g_File->fileName().trimmed().isEmpty())
        throw "Can't read file ,may be forget SetFile or failed!";
    if(!g_File->open(QIODevice::ReadOnly))
        throw "File can not open , pls check it!";
    return true;
}


/********************************************
    Function:bool CloseFile()
    Description: 关闭XML文件
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
bool xmlFileFunctions::CloseFile()
{
    if (!g_File)
        throw "Close fail,File was not initialization!";
    else
    {
        if (g_File->isOpen())
            g_File->close();
        delete g_File;
        g_File = 0;
    }
    return true;
}


/********************************************
    Function: QString GetValueByElementName(QString ElemName, int ) const
    Description: 根据元素名获取相应元素的值
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
QString xmlFileFunctions::GetValueByElementName(QString ElemName, int ) const
{
    if (!g_File->isOpen())
        throw "File not opened ,pls OPEN it first!";

    QDomDocument doc("configs");
    if(!doc.setContent(g_File))
    {
        g_File->close();
        throw "xml File content error , pls check the text in xml file!";
    }

    QDomElement root;
    root = doc.documentElement();
    QDomNode n;
    QDomNodeList nl;
    nl=doc.childNodes();
    for (int i = 0; i < nl.count(); ++i)
    {
        if (nl.at(i).nodeName() == ElemName)
        {
            return nl.at(i).nodeValue();
        }
    }
    return "";
}

/********************************************
    Function:xmlFileFunctions::DBConn xmlFileFunctions::GetDBConn() const
    Description: 获得XML节点值
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
xmlFileFunctions::DBConn xmlFileFunctions::GetDBConn() const
{
    DBConn result;
    //step 1 find node which name "configs"
    if (!g_File->isOpen())
        throw "File not opened ,pls OPEN it first!";

    QDomDocument doc("configs");
    if(!doc.setContent(g_File))
    {
        g_File->close();
        throw "xml File content error , pls check the text in xml file!";
    }

    QDomElement root;
    root = doc.documentElement();
    QDomNode n;
    QDomNodeList nl;
    nl=doc.childNodes();
    for (int i = 0; i < nl.count(); ++i)
    {
        if (nl.at(i).nodeName() == "configs")
        {
            if (!nl.at(i).hasChildNodes())
                throw "DB configs is Empty,pls check the xml file.";

            //step 2 find node which have childnode "server",recusive nodelist tree
            //maybe there are many nodes contain db connect string,return the first found
            n = GetDBNode(nl.at(i));
            if ((!n.isNull()) && (n.hasChildNodes()))
            {
                GetDBConnByNodeList(n.childNodes(),result);
            }

            return result;
        }
    }
    return result;
}

/********************************************
    Function:QDomNode GetDBNode(QDomNode InNode) const
    Description:  获得XML节点
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
QDomNode xmlFileFunctions::GetDBNode(QDomNode InNode) const
{

    QDomNode result;
    QDomNode n;
    n = InNode.firstChild();
    while (!n.isNull())
    {

        if (n.nodeName() == QString("server"))
            if ( (!n.toElement().attribute("value").trimmed().isEmpty()) // node value like  <nodename 'nodevalue'></nodename>
                 || (!n.toElement().text().trimmed().isEmpty()))    //node text like <nodename>'text'</nodename>
                return InNode;

        n = n.nextSibling();
    }


    for (int i = 0; i < InNode.childNodes().count(); ++i)
    {
        if (InNode.childNodes().at(i).hasChildNodes())
            result = GetDBNode(InNode.childNodes().at(i));
        if (!result.isNull())
            return result;
    }


    return result;
}


/********************************************
    Function:xmlFileFunctions::DBConn xmlFileFunctions::GetDBConnByNodeList(QDomNodeList nl,DBConn &result) const
    Description:  通过节点列表，获得XML节点值
    Input:None
    Output:None
    Return:None
    Calls:None
    Called By:None
********************************************/
xmlFileFunctions::DBConn xmlFileFunctions::GetDBConnByNodeList(QDomNodeList nl,DBConn &result) const
{
    DBConn ret;
    QString s;
    for (int i = 0; i < nl.count(); ++i)
    {
        s = nl.at(i).nodeName();
        if(s== QString("server"))
        {
            if (!nl.at(i).toElement().text().trimmed().isEmpty())
                result.Server=nl.at(i).toElement().text();
            else if(!nl.at(i).toElement().attribute("value").trimmed().isEmpty())
                result.Server=nl.at(i).toElement().attribute("value");
        }
        else if (s == QString("username"))
            result.UserName = nl.at(i).toElement().text();
        else if(s == QString("password"))
            result.Password=  nl.at(i).toElement().text();
        else if(s ==QString("database"))
            result.Database=  nl.at(i).toElement().text();

    }
    ret = result;
    return ret;
}
