#include "dnserver.h"

#include "basefunctions.h"


DnInterfaceServer::~DnInterfaceServer()
{
    //do nothing
}



DnStudentServer::DnStudentServer(FSqlFactory *f)
{
    if (this->m_pSqlfct)
        delete m_pSqlfct;
    m_pSqlfct = f;
}

DnStudentServer::~DnStudentServer()
{

}

bool DnStudentServer::AppendRecord(DnInterfaceDao *dao)
{
    if (!dao)   //null?
        throw "Error in AppendRecord, dao is null!";
    dao->AddRecord(m_Records);
}

void DnStudentServer::GetData()
{
    try
    {
        LiField FieldId,FieldName,FieldAge;
        LiDataContext dc;
        LiTable tb;

        dc.SetTableName("Demo_Student");
        FieldId.SetName("Id");
        FieldName.SetName("Name");
        FieldAge.SetName("Age");

        dc.AddField(&FieldId);
        dc.AddField(&FieldName);
        dc.AddField(&FieldAge);

        if (m_pSqlfct == NULL)
            QMessageBox::about(NULL,"error","sqlfct is null!");

        ISqlQuery *qry;

        qry = this->m_pSqlfct->sqlQryFct();
        qry->query(dc,tb);
        this->m_Records = tb.GetRecords().GetRecords();
    }
    catch(QString exception)
    {
        QMessageBox::about(NULL,"error",exception);
    }
    catch(const char* exception)
    {
        QMessageBox::about(NULL,"error",exception);
    }
}


DnInterfaceServer::DnInterfaceServer()
{
    // do nothing
}
