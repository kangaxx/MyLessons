#include "icodegenedao.h"



lcg::ICodeGeneDao::ICodeGeneDao(FSqlFactory *sql)
{
    ErrorMsg::message(QString("Read data fail , set sql point fail"),(sql == NULL));
    m_sqlptr = sql;
}


vector<lcg::ITemplateFile *> lcg::TemplateCPPFileDao::getData()
{
    vector<ITemplateFile *> rst;
    ErrorMsg::message(QString("Read data fail, template file id invalid : ") +
                      QString::number(m_fileId),(m_fileId==INT_SET_READONLY_FIELD_RESULT_OK));
    ISqlQuery *qry = m_sqlptr->sqlQryFct();
    QStringList fields;
    fields << FIELDNAME_CHARS_TEMPLATEFILE_ID << FIELDNAME_CHARS_TEMPLATEFILE_NAME << FIELDNAME_CHARS_TEMPLATEFILE_CONTEXT;
    LiConditionList conds;
    conds << FIELDNAME_CHARS_TEMPLATEFILE_ID << m_fileId << AND << liEqual;
    LiResultList temp = qry->query(fields,TABLENAME_CHARS_TEMPLATEFILE_NAME,&conds);
    for (int i=0;i<temp.getCount();i++)
    {
        ITemplateFile *t = new CppTemplateFile();
        t->initial(temp.at(i,FIELDNAME_CHARS_TEMPLATEFILE_CONTEXT).toStdString(),
                   temp.at(i,FIELDNAME_CHARS_TEMPLATEFILE_NAME).toStdString(),
                   temp.at(i,FIELDNAME_CHARS_TEMPLATEFILE_ID).toInt());
        rst.push_back(t);
    }
    return rst;
}
