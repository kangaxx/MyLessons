#include "itemplatefile.h"

using namespace lcg;


ITemplateFile::~ITemplateFile()
{
    //do nothing yet;
}


CppTemplateFile::CppTemplateFile():ITemplateFile(fileName)
{
    FILE *f;
    f = fopen(fileName.c_str(),"r");
    if (!f)
        throw static_cast<int>(PS_CG_TemplateNoFound);
    this->m_fileContain = new char[INT_MAX_CPPFILETEMPLATELENGTH];
    if (f)
        fclose(f);
}

CppTemplateFile::~CppTemplateFile()
{
//do nothing yet
}
