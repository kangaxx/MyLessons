#ifndef COMDEFINE_H
#define COMDEFINE_H
#ifdef WIN32
#define STR_GET_EXECPATH basefunctions::GetExePath_Win32()
#elif linux
#define STR_GET_EXECPATH basefunctions::GetExePath_Linux()
#endif
#endif // COMDEFINE_H
