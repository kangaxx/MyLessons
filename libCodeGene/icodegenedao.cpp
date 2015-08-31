#include "icodegenedao.h"



lcg::ICodeGeneDao::ICodeGeneDao(FSqlFactory *sql)
{
    ErrorMsg::message(QString("Read data fail , set sql point fail"),(sql == NULL));
}


vector<lcg::ITemplateFile *> lcg::TemplateCPPFileDao::getData()
{
    ErrorMsg::message(QString("Read data fail, template file id invalid : ") +
                      QString::number(m_fileId),(m_fileId==INT_SET_READONLY_FIELD_RESULT_OK));
    LiField fieldId, fieldType,fieldName;
    LiField condId;
    fieldId.SetName(QString(FIELDNAME_CHARS_TEMPLATEFILE_ID));
    fieldId.SetValue(QString::number(m_fieldId));

}
