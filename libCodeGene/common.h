#ifndef COMMON_H
#define COMMON_H
#include <QString>
#include <QtCore>
#include <vector>
#include "sqlfunctions.h"
#define INT_MAX_CPPFILETEMPLATELENGTH 1024*1024*5 //CPP file max to 5M;
#define INT_MAX_MACRO_VALUE_SIZE 2048 //every char list max to 2048
#define FIELDNAME_CHARS_MACRO_ID "MacroId"
#define FIELDNAME_CHARS_MACRO_POS "MacroPos"
#define FIELDNAME_CHARS_MACRO_NAME "MacroName"
#define FIELDNAME_CHARS_TEMPLATEFILE_ID "FileId"
#define FIELDNAME_CHARS_TEMPLATEFILE_NAME "FileName"
#define FIELDNAME_CHARS_TEMPLATEFILE_CONTEXT "FileText"

#define TABLENAME_CHARS_TEMPLATEFILE_NAME "TEMPLATENAME"

#define INT_TEMPLATE_TYPE_CPP 1
#define INT_TEMPLATE_TYPE_JAVA 2

#define INT_SET_READONLY_FIELD_RESULT_OK 99

#define INT_FIELD_ID_VALUE_ERROR -1
#define INT_TEMPLATEFILE_TYPE_CPP 1
#define INT_TEMPLATEFILE_TYPE_JAVA 2
#define G_READ_ONLY_FILE_SET_(func,type) int (*func)(type &dest, type value)= _G_IO_DATA<type>::setReadOnly;
#define CHARS_MACRO_FIELDNAME_ID "MacroId"
#define CHARS_MACRO_FIELDNAME_POS "MacroPos"
#define CHARS_MACRO_FIELDNAME_NAME "MacroFieldName"


template<class valueType>
class _G_IO_DATA
{
public:
    static int setReadOnly(valueType &dest, valueType value){dest = value; return INT_SET_READONLY_FIELD_RESULT_OK;}
};
namespace lcg {

enum eProcSignal{
    PS_CG_None = -1,  //PS_CG_CG , ProcSignal Code Gene
    PS_CG_Success = 0,
    PS_CG_TemplateError = 1,
    PS_CG_CodeFileError = 2,
    PS_CG_FileLost = 15,
    PS_CG_CodesRepeat =16,
    PS_CG_TemplateNoFound = 25,
    PS_CG_MacroNoFount = 35,
    PS_CG_MacroReapt = 36,
    PS_CG_MemError = 31
};

}

#endif // COMMON_H

