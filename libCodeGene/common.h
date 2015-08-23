#ifndef COMMON_H
#define COMMON_H
#define INT_MAX_CPPFILETEMPLATELENGTH 1024*1024*5 //CPP file max to 5M;
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
#endif // COMMON_H

