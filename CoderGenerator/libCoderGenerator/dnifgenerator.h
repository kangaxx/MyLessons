#ifndef DNIFGENERATOR_H
#define DNIFGENERATOR_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

const int INT_MAX_TEMPLATESIZE = 65536;
const int INT_POS_BEFORE_FLAG = 0;
const int INT_POS_AFTER_FLAG = 1;
const string STR_CGFLAG_BEGIN = "/*";
const string STR_CGFLAG_END = "*/";
const string STR_CGFLAG_SOURCE_BEGIN = "/*sb*/";
const string STR_CGFLAG_SOURCE_END = "/*se*/";
const string STR_CGFLAG_FILE_BEGIN = "/*fb*/";
const string STR_CGFLAG_FILE_END = "/*fe*/";

const string STR_CGFLAG_MACRO_BEGIN = "<m";
const string STR_CGFLAG_FOMULE_BEGIN = "<o";
const string STR_CGFLAG_FLAGTYPE_END = "/>";


//DCodeGenerator "1" *-- "1" DIfTemplate : contains
//class DIfTemplate <|-- DCppTemplate

enum eCGResult{
    CG_R_None = -1,
    CG_R_Success = 0,
    CG_R_TemplateError = 1,
    CG_R_CodeFileError = 2,
    CG_R_FileLost = 15,
    CG_R_CodesRepeat =16,
    CG_R_TemplateNoFound = 25,
    CG_R_MacroNoFount = 35,
    CG_R_MacroReapt = 36,
    CG_R_MemError = 31
};

enum eCGFileType{
    CG_FT_CPP = 1,
    CG_FT_Fort = 2
};

enum eCGFlagType{
    CG_FLAG_File = 1,
    CG_FLAG_Macro = 2,
    CG_FLAG_Fomule = 3,
    CG_FLAG_NONE = -1
};

enum eCGMacroType{
    CG_MACRO_Normal = 1,
    CG_MACRO_Multi = 2
};

class DCodeMacro{
public:
    DCodeMacro();
    DCodeMacro(string name, string value);
    DCodeMacro(string name, string value, eCGMacroType type);
    string GetName();
    string GetValue();
    void SetName(string name);
    void SetValue(string value);
    void SetName(const char* name);
    void SetValue(const char* value);
private:
    string m_Name;
    string m_Value;
    eCGMacroType m_Type;
};

class DIfTemplate{
public:
    virtual ~DIfTemplate()=0;
    virtual DIfTemplate& operator=(DIfTemplate& right)=0;
    virtual void GetTemplateName(char *tempName)=0;
    virtual string GetUpdatedCodes(const char* fileName,DCodeMacro cm[], int macroNum)=0;
    virtual string GetUpdatedCodes(int srcBlockId, DCodeMacro cm[], int macroNum)=0;
};

class DCppTemplate:public DIfTemplate{
public:
    DCppTemplate(FILE *fp);
    DCppTemplate(char *tempName);
    DCppTemplate(){mp_TemplateContains=0; m_ContainSize = 0; m_HaveFileNameFlag = false;}
    DCppTemplate(DCppTemplate &other);
    virtual ~DCppTemplate();

    virtual void GetTemplateName(char *tempName);
    virtual DIfTemplate &operator=(DIfTemplate& right);
    vector<string> GetCodesFileName();
    vector<string> GetMacroName();
    struct stc_Flag{
        string Contain;
        int beginPos;
        int endPos;
        stc_Flag(){Contain = ""; beginPos = -1; endPos = -1;}
    };

    void SetHaveFile(bool value){this->m_HaveFileNameFlag = value;}
    int GetSourceBlockNum();
    vector<string> GetFileList();

    virtual string GetUpdatedCodes(const char *fileName,DCodeMacro cm[], int macroNum);
    virtual string GetUpdatedCodes(int srcBlockId, DCodeMacro cm[], int macroNum);
private:
    char* mp_TemplateContains;
    int m_ContainSize;
    bool m_HaveFileNameFlag;
    FILE *mp_File;
    stc_Flag FindMacroByName(const char *source, string macroName, int srcSize, int i = 0); //to find macro by macro num , seqNo means start char num , if seqno more zhan srcSize, will return null stc_Flag
    vector<stc_Flag> FindFlags(const char *source, const char *tagLeft, const char *tagRight, int srcSize, int tagSize); //find all flags in file ,for check template correctable;
    eCGFlagType GetFlagType(string flagStr);
    vector<stc_Flag> FindSource();
    vector<stc_Flag> FindFileName();

    vector<stc_Flag> FindMacroFlag(vector<stc_Flag> allFlag);
    vector<stc_Flag> FindFomuleFlag(vector<stc_Flag> allFlag);


    bool CheckFlagSequence(vector<DCppTemplate::stc_Flag> allFlag);
    bool CheckContain();
    string RemoveFlagTag(string tagStr, int tagSize);
    int GetBlockSequenceByFile(const char *fileName);
};

class DIfCodeFile{
public:
    virtual ~DIfCodeFile()=0;
    virtual bool InsertCodes(const char* Codes)=0;
};

class DCppCodeFile:public DIfCodeFile{
public:
    DCppCodeFile(const char *fileName);
    ~DCppCodeFile();
    virtual bool InsertCodes(const char *Codes);
private:
    FILE *mp_File;
};



class DCodeGenerator{
protected:
    DCodeGenerator();
    DCodeGenerator(const DIfTemplate *t, const DIfCodeFile *c, int FileNum, const DCodeMacro cm[], int MacroNum);
    ~DCodeGenerator();
public:
    static DCodeGenerator *Instance();
    static void Close();
    static eCGResult Initial(const char *templateFile, const char *fileName[] , int fileNum, const char *codeMacros[]=0, int macrosNum = 0,eCGFileType ft = CG_FT_CPP);
    static eCGResult AddMacros(const char *macroName, const char *macroValue, const char *macroType=0);
    eCGResult Operator();
private:
    static DCodeGenerator *sp_CgInstance;
    DIfTemplate *mp_Temp;
    DIfCodeFile *mp_CFile;
    DCodeMacro *mp_CodeMacros;
    int m_FileNum, m_MacroNum;
};
#endif // DNIFGENERATOR_H
