#include "itemplatefile.h"

using namespace lcg;


ITemplateFile::~ITemplateFile()
{
    //do nothing yet;
}


CppTemplateFile::CppTemplateFile(string fileName):ITemplateFile(fileName)
{
    FILE *f;
    f = fopen(fileName.c_str(),"r");
    if (!f)
        throw static_cast<int>(PS_CG_TemplateNoFound);
    this->m_fileContain = new char[INT_MAX_CPPFILETEMPLATELENGTH];
    m_fileLength = fread(this->m_fileContain,sizeof(char),INT_MAX_CPPFILETEMPLATELENGTH,f);
    if (f)
        fclose(f);
}

CppTemplateFile::~CppTemplateFile()
{
    delete [] m_fileContain;
}
