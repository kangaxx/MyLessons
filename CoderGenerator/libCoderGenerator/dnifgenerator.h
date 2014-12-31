#ifndef DNIFGENERATOR_H
#define DNIFGENERATOR_H
//DCodeGenerator "1" *-- "1" DIfTemplate : contains
//class DIfTemplate <|-- DCppTemplate

class DCodeGenerator{
protected:
    DCodeGenerator(DIfTemplate *t,DIfCodeFile *c,int FileNum,
                   DCodeMacro cm[],int MacroNum);
public:
    static DCodeGenerator * Instance(DIfTemplate *t,DIfCodeFile *c,int FileNum,
                   DCodeMacro cm[],int MacroNum);
    static void Close();
    eCGResult Operator();
private:
    static DCodeGenerator *s_CgInstance;
    DIfTemplate *m_Temp;
    DIfCodeFile *m_CFile;
    DCodeMacro *m_CodeMacros;
    int m_FileNum, m_MacroNum;
};

class DIfTemplate{
public:
    virtual ~DifTempate()=0;

    virtual DIfTemplate& operator=(DIfTempate& right)=0;
};

class DCppTemplate{
public:
    ~DCppTemplate;
private:
    char *m_TemplateContains;
}

#endif // DNIFGENERATOR_H
