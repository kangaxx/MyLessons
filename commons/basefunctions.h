#ifndef BASEFUNCTIONS_H
#define BASEFUNCTIONS_H

#include "sqlfunctions.h"
namespace base
{
    class basefunctions;
}
class basefunctions
{
public:
    basefunctions();
    void GetSqlLink(QString FileName, QString ConnName, Connections &Conn);
private:
    static QString GetExePath_Linux();
    static QString GetExePath_Win32();
};

#endif // BASEFUNCTIONS_H
