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


//get cpp file by id
class TemplateCPPFileDao:public ICodeGeneDao
{
public:
    TemplateCPPFileDao(FSqlFactory *sql):ICodeGeneDao(sql){this->m_fileId = INT_FIELD_ID_VALUE_ERROR;}
    TemplateCPPFileDao(FSqlFactory *sql,int fileId):ICodeGeneDao(sql),m_fileId(fileId){;}
    void setFileId(int id){this->m_fileId = id;}
    vector<ITemplateFile*> getData();
private:
    int m_fileId;
};


}
#endif // ICODEGENEDAO_H
