#include "dnifgenerator.h"

DCodeGenerator::DCodeGenerator()
{
    this->mp_CFile = 0;
    this->mp_Temp = 0;
    this->m_FileNum = 0;
    this->m_MacroNum = 0;
    this->mp_CodeMacros = 0;
}

DCodeGenerator::DCodeGenerator(const DIfTemplate *t, const DIfCodeFile *c, int FileNum, const DCodeMacro cm[], int MacroNum)
{
    this->mp_Temp = (DIfTemplate*)t;
    this->mp_CFile = (DIfCodeFile*)c;
    this->m_FileNum = FileNum;
    this->mp_CodeMacros = (DCodeMacro*)cm;
    this->m_MacroNum = MacroNum;
}

DCodeGenerator::~DCodeGenerator()
{
    delete this->mp_Temp;
    for (int i = 0; i < this->m_FileNum; i++)
        delete &(this->mp_CFile[i]);

}

DCodeGenerator *DCodeGenerator::Instance()
{
    if (sp_CgInstance == 0)
        sp_CgInstance = new DCodeGenerator();
    return sp_CgInstance;
}

void DCodeGenerator::Close()
{
    delete sp_CgInstance;
    sp_CgInstance = 0;
}

eCGResult DCodeGenerator::Initial(const char *templateFile, const char *fileName[], int fileNum, const char *codeMacros[], int macrosNum, eCGFileType ft)
{
    FILE *pt;
    pt = fopen(templateFile,"r");
    if (!pt)
        return CG_R_TemplateNoFound;

}



DIfTemplate::~DIfTemplate()
{
// do nothing yet
}

DCppTemplate::DCppTemplate(char *tempName)
{
    FILE *fp;
    fp = fopen(tempName,"r");

    if (!fp)
        throw "Construct DCppTemplate fail, file open error ,please check tempName!";

    this->mp_TemplateContains = new char[INT_MAX_TEMPLATESIZE];
    m_ContainSize  = fread(this->mp_TemplateContains,sizeof(char),INT_MAX_TEMPLATESIZE,fp);
    m_HaveFileNameFlag = false;
}

DCppTemplate::DCppTemplate(FILE *fp)
{
    if (!fp)
        throw "Construct DCppTemplate fail, File *fp is Null";

    this->mp_TemplateContains = new char[INT_MAX_TEMPLATESIZE];
    m_ContainSize  = fread(this->mp_TemplateContains,sizeof(char),INT_MAX_TEMPLATESIZE,fp);
    m_HaveFileNameFlag = false;
//    for (int i = 0; i < this->m_ContainSize)

}

DCppTemplate::DCppTemplate(DCppTemplate &other)
{
    if(this == &other)
        return;
    else if(other.mp_TemplateContains == 0 || other.m_ContainSize ==0)
    {
        this->m_ContainSize = 0;
        this->mp_TemplateContains = 0;
        this->m_HaveFileNameFlag = false;
    }
    else
    {
        this->m_ContainSize = other.m_ContainSize;
        this->mp_TemplateContains = new char[other.m_ContainSize];
        this->m_HaveFileNameFlag = other.m_HaveFileNameFlag;
    }
}

DCppTemplate::~DCppTemplate()
{
    this->m_ContainSize =0;
    delete [] this->mp_TemplateContains;
}

void DCppTemplate::GetTemplateName(char *tempName)
{
    char result[]="no template name function yet";
}

DIfTemplate &DCppTemplate::operator=(DIfTemplate &right)
{
    if (this == &right)
        return *this;

}

vector<string> DCppTemplate::GetCodesFileName()
{
    vector<string> result;
    if (this->mp_TemplateContains == 0 || this->m_ContainSize <= 0)
        return result;
}

int DCppTemplate::GetSourceBlockNum()
{
    return FindSource().size();
}

vector<string> DCppTemplate::GetFileList()
{
    vector<string> result;
    for (auto fileStc : FindFileName())
    {
        if (fileStc.Contain.length() > 0)
            result.push_back(fileStc.Contain);
    }
    return result;
}

string DCppTemplate::UpdateMacro(DCodeMacro cm[], int macroNum)
{
    string source = this->mp_TemplateContains;
    string result;
    int i = 0;
    vector<DCppTemplate::stc_Flag> allFlag;
    char cl[3] = "/*";
    char cr[3] = "*/";
    allFlag = FindFlags(source.c_str(),cl,cr,source.length(),sizeof(cr));
    vector<DCppTemplate::stc_Flag> macroFlag;
    macroFlag = FindMacroFlag(allFlag);
    if (!CheckFlagSequence(macroFlag))
        return source;
    int copyPos = 0;
    for (auto tf : macroFlag)
    {
        for (int i = 0; i < macroNum; i++)
        {
            if (RemoveFlagTag(tf.Contain,STR_CGFLAG_FLAGTYPE_END.length()) == cm[i].CMName)
            {
                result += source.substr(copyPos,tf.beginPos-copyPos);
                result += cm[i].CMValue;
                copyPos = tf.endPos;
            }
        }
    }
    result += source.substr(copyPos,source.length() - copyPos);
    return result;
}

vector<DCppTemplate::stc_Flag> DCppTemplate::FindFlags(const char *source, const char *tagLeft, const char *tagRight, int srcSize , int tagSize)
{
    vector<DCppTemplate::stc_Flag> result;
    if (srcSize < 1 || tagSize < 1)
        return result;
    char *flagStr;
    int b=-1,e=-1;

    for(int i = 0;i < srcSize; i++)
    {
        if (strncmp(&source[i],tagLeft,tagSize-1)==0)
        {
            if (e < 0)
            {
                b = i;
                i += tagSize - 2;
            }
            else
            {

                b = -1;
                e = -1;
            }
        }
        else if (strncmp(&source[i],tagRight,tagSize-1)==0)
        {
            if (b >= 0 && b < i)
            {
                DCppTemplate::stc_Flag temp;
                e = i+tagSize-1;
                flagStr = new char[e-b+1];
                memcpy(flagStr,&source[b],e-b);
                flagStr[e-b] ='\0';
                temp.Contain = RemoveFlagTag(flagStr,tagSize-1);
                temp.beginPos = b;
                temp.endPos = e;
                result.push_back(temp);
                delete []flagStr;
                i += tagSize - 2;
            }
            b = -1;
            e = -1;
        }
    }
    return result;
}

eCGFlagType DCppTemplate::GetFlagType(string flagStr)
{
    if (flagStr.length() <= 0)
        return CG_FLAG_NONE;
    vector<std::string> flagBegins;
    flagBegins.push_back(STR_CGFLAG_MACRO_BEGIN);
    flagBegins.push_back(STR_CGFLAG_FOMULE_BEGIN);

    for (auto Tag : flagBegins)
    {
        if (FindFlags(flagStr.c_str(),Tag.c_str(),STR_CGFLAG_FLAGTYPE_END.c_str(),flagStr.length(),STR_CGFLAG_FLAGTYPE_END.length()+1).size()>0)
        {
            if (Tag == STR_CGFLAG_MACRO_BEGIN)
                return CG_FLAG_Macro;
            else if (Tag == STR_CGFLAG_FOMULE_BEGIN)
                return CG_FLAG_Fomule;
        }
    }
    return CG_FLAG_NONE;
}

vector<DCppTemplate::stc_Flag> DCppTemplate::FindSource()
{
    vector<DCppTemplate::stc_Flag> result;
    result = FindFlags(this->mp_TemplateContains,STR_CGFLAG_SOURCE_BEGIN.c_str(),STR_CGFLAG_SOURCE_END.c_str(),STR_CGFLAG_SOURCE_END.length()+1,this->m_ContainSize);
    return result;
}

vector<DCppTemplate::stc_Flag> DCppTemplate::FindFileName()
{
    vector<DCppTemplate::stc_Flag> result;
    result = FindFlags(this->mp_TemplateContains,STR_CGFLAG_FILE_BEGIN.c_str(),STR_CGFLAG_FILE_END.c_str(),STR_CGFLAG_FILE_END.length()+1,this->m_ContainSize);
    return result;
}

vector<DCppTemplate::stc_Flag> DCppTemplate::FindMacroFlag(vector<DCppTemplate::stc_Flag> allFlag)
{
    vector<DCppTemplate::stc_Flag> result;
    for (auto Tag : allFlag)
    {
        if (GetFlagType(Tag.Contain) == CG_FLAG_Macro)
            result.push_back(Tag);
    }
    return result;
}

vector<DCppTemplate::stc_Flag> DCppTemplate::FindFomuleFlag(vector<DCppTemplate::stc_Flag> allFlag)
{
    vector<DCppTemplate::stc_Flag> result;
    for (auto Tag : allFlag)
    {
        if (GetFlagType(Tag.Contain) == CG_FLAG_Fomule)
            result.push_back(Tag);
    }
    result;
}

bool DCppTemplate::CheckFlagSequence(vector<DCppTemplate::stc_Flag> allFlag)
{
    for (int i=0;i<allFlag.size();i++)
    {
        if (allFlag[i].beginPos >= allFlag[i].endPos)
            return false;
        if (i < allFlag.size()-1)
            if (allFlag[i].endPos > allFlag[i+1].beginPos)
                return false;
    }
    return true;
}



string DCppTemplate::RemoveFlagTag(string tagStr, int tagSize)
{
    tagStr.erase(tagStr.begin(),tagStr.begin()+tagSize);
    tagStr.erase(tagStr.end()-tagSize,tagStr.end());
    return tagStr;
}


