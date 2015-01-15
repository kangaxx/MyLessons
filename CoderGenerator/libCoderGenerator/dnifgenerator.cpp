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
    mp_File = fp;
}

DCppTemplate::DCppTemplate(FILE *fp)
{
    mp_File = 0; //file was opened out of class;
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
        this->mp_File = 0;
    }
    else
    {
        this->m_ContainSize = other.m_ContainSize;
        this->mp_TemplateContains = new char[other.m_ContainSize];
        this->m_HaveFileNameFlag = other.m_HaveFileNameFlag;
        this->mp_File = 0;
    }
}

DCppTemplate::~DCppTemplate()
{
    if (mp_File != 0)
        delete mp_File;
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
    return right;

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
    if (!m_HaveFileNameFlag)
        return result;  //no file name!
    for (auto fileStc : FindFileName())
    {
        if (fileStc.Contain.length() > 0)
            result.push_back(fileStc.Contain);
    }
    return result;
}

string DCppTemplate::GetUpdatedCodes(const char *fileName,DCodeMacro cm[], int macroNum)
{
    string result;
    if (!CheckContain())
        throw "Template is error , pls check it careful!";
    vector<stc_Flag> codeBlockList = FindSource();
    int seq = GetBlockSequenceByFile(fileName);
    result = GetUpdatedCodes(seq,cm,macroNum);
    return result;
}

string DCppTemplate::GetUpdatedCodes(int srcBlockId, DCodeMacro cm[], int macroNum)
{

    if (!CheckContain())
        throw "Template is error , pls check it careful!";
    vector<stc_Flag> codeBlockList = FindSource();

    if (srcBlockId < 0 || srcBlockId >= codeBlockList.size())
        throw "BlockId error !";
    string source = codeBlockList[srcBlockId].Contain;
    stc_Flag fgTemp;
    for (int i = 0;i < macroNum; i++)
    {
        int j = 0;
        for (; j< source.length();)
        {
            fgTemp = FindMacroByName(source.c_str(),cm[i].GetName(),source.length(),j);
            if (fgTemp.beginPos < 0)
                break;
            source.insert(fgTemp.endPos,cm[i].GetValue());
            j = fgTemp.endPos + cm[i].GetValue().length();
        }

    }
    return source;
//    vector<stc_Flag> srcFlags;
//    srcFlags = FindFlags(source.c_str(),STR_CGFLAG_BEGIN.c_str(),STR_CGFLAG_END.c_str(),source.length(),STR_CGFLAG_END.length()+1);
//    vector<DCppTemplate::stc_Flag> macroFlag;
//    macroFlag = FindMacroFlag(srcFlags);
//    if (!CheckFlagSequence(macroFlag))
//        return source;
//    int copyPos = 0;
//    for (auto tf : macroFlag)
//    {
//        for (int i = 0; i < macroNum; i++)
//        {

//            if (RemoveFlagTag(tf.Contain,STR_CGFLAG_FLAGTYPE_END.length()) == cm[i].GetName())
//            {
//                result += source.substr(copyPos,tf.beginPos-copyPos);
//                result += cm[i].GetValue();
//                copyPos = tf.endPos;
//            }
//        }
//    }
//    result += source.substr(copyPos,source.length() - copyPos);
}

DCppTemplate::stc_Flag DCppTemplate::FindMacroByName(const char *source, string macroName, int srcSize, int i)
{
    stc_Flag result;
    if (i < 0 || i >= srcSize)
        return result;
    string target = STR_CGFLAG_BEGIN + STR_CGFLAG_MACRO_BEGIN + macroName + STR_CGFLAG_FLAGTYPE_END + STR_CGFLAG_END;
    for (;i<srcSize;i++)
    {
        if (strncmp(&source[i],target.c_str(),target.length()) == 0)
        {
            result.Contain = macroName;
            result.beginPos = i;
            result.endPos = i+target.length();
            return result;
        }
    }
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
    result = FindFlags(mp_TemplateContains,STR_CGFLAG_SOURCE_BEGIN.c_str(),STR_CGFLAG_SOURCE_END.c_str(),this->m_ContainSize,STR_CGFLAG_SOURCE_END.length()+1);
    return result;
}

vector<DCppTemplate::stc_Flag> DCppTemplate::FindFileName()
{
    vector<DCppTemplate::stc_Flag> result;

    result = FindFlags(mp_TemplateContains,STR_CGFLAG_FILE_BEGIN.c_str(),STR_CGFLAG_FILE_END.c_str(),this->m_ContainSize,STR_CGFLAG_FILE_END.length()+1);
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

bool DCppTemplate::CheckContain()
{
    if (GetSourceBlockNum() <= 0)
        return false;

    if (m_HaveFileNameFlag)
    {
        if (GetFileList().size() != GetSourceBlockNum())
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

int DCppTemplate::GetBlockSequenceByFile(const char *fileName)
{
    vector<string> fileNameList;
    fileNameList = GetFileList();
    for(int i=0 ; i < fileNameList.size() ; i++)
    {
        if (fileNameList[i] == fileName)
            return i;
    }
    return -1;
}





DCppCodeFile::DCppCodeFile(const char *fileName)
{
    this->mp_File = new FILE;
    mp_File = fopen(fileName,"rw");
}

DCppCodeFile::~DCppCodeFile()
{

}

bool DCppCodeFile::InsertCodes(const char *Codes)
{
    return true;
}


DIfCodeFile::~DIfCodeFile()
{
    //do nothing yet
}


DCodeMacro::DCodeMacro()
{
    this->m_Type = CG_MACRO_Normal;
}

DCodeMacro::DCodeMacro(string name, string value)
{
    this->m_Name = name;
    this->m_Value = value;
    this->m_Type = CG_MACRO_Normal;
}

DCodeMacro::DCodeMacro(string name, string value, eCGMacroType type)
{
    this->m_Name = name;
    this->m_Value = value;
    this->m_Type = type;
}

string DCodeMacro::GetName()
{
    return m_Name;
}

string DCodeMacro::GetValue()
{
    return m_Value;
}

void DCodeMacro::SetName(string name)
{
    this->m_Name = name;
}

void DCodeMacro::SetValue(string value)
{
    this->m_Value = value;
}

void DCodeMacro::SetName(const char *name)
{
    this->m_Name = name;
}

void DCodeMacro::SetValue(const char *value)
{
    this->m_Value = value;
}
