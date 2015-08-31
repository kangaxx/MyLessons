#ifndef IERRORMSG_H
#define IERRORMSG_H
#include "common.h"
#define INT_ERRORMSG_TYPE_ERROR 1
#define INT_ERRORMSG_TYPE_WARNING 2

class ErrorMsg
{
public:
    ErrorMsg();
    ErrorMsg(QString msg):m_msg(msg){;}
    QString getMsg(){return m_msg;}
    static void message(QString msg,bool condition = false,int type = INT_ERRORMSG_TYPE_ERROR){ if (!condition && INT_ERRORMSG_TYPE_ERROR == type) throw msg;}
private:
    QString m_msg;
};

#endif // IERRORMSG_H
