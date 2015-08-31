#ifndef ICODEGENEDAO_H
#define ICODEGENEDAO_H
#include "common.h"
#include "sqlfunctions.h"
#include "ierrormsg.h"
#include "itemplatefile.h"
namespace lcg{
class ICodeGeneDao
{
public:
    ICodeGeneDao(FSqlFactory *);
protected:
    ICodeGeneDao(){;}
    FSqlFactory *m_sqlptr;
};

class TemplateCPPFileDao:public ICodeGeneDao
{
public:
    TemplateFileDao(FSqlFactory *sql):ICodeGeneDao(sql){this->m_fileId = INT_FIELD_ID_VALUE_ERROR;}
    TemplateFileDao(FSqlFactory *sql,int fileId):ICodeGeneDao(sql),m_fileId(fileId){;}
    vector<ITemplateFile*> getData();
private:
    int m_fileId;
};


}
#endif // ICODEGENEDAO_H
