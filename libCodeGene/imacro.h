#ifndef IMACRO_H
#define IMACRO_H
#include "itemplatefile.h"
#include "ierrormsg.h"
#include "common.h"

#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlDriver"
#include "QtSql/QSqlError"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlRecord"
#include "QtSql/QSqlField"
#include "QtSql/QSqlQueryModel"
#include "QDebug"
#include "QFile"
#include "QtXml"
#include "QtXml/QDomDocument"
#include "QtXml/QDomNode"

#include "icodeelement.h"

namespace lcg{


typedef QString (IElementCombiner::*combinerElemArray)(ICodeElement *,int);
typedef QString (IElementCombiner::*combinerElemVector)(vector<ICodeElement *>);
//Macro just means string replace, if in <repeat> type formula , it the valueNum will direct repeat time!
class IMacro
{
protected:
    IMacro(){;}
public:
    IMacro(int id,int pos,QString name):m_id(id),m_pos(pos),m_name(name){;} //(int TemplateId , int Pos), Pos can not over temp length!
    IMacro(QSqlRecord &rcd);
    virtual ~IMacro() = 0;

    IMacro *operator =(QSqlRecord &rcd);
    int getID(){return m_id;}
    int getPos(){return m_pos;}
    QString getName(){return m_name;}

    virtual void insertElement(ICodeElement *elem) = 0; //elem is value! , elem list means mulitpule value , or
    virtual QStringList getValue() = 0;
protected:
    int m_id;
    int m_pos;
    QString m_name;
    QList<ICodeElement*> m_elem;
    void setByRecord(QSqlRecord &rcd);

};

//for c++ codes file
class CppMacro:public IMacro
{
public:
    explicit CppMacro(int id,int pos,QString name):IMacro(id,pos,name){;}
    explicit CppMacro(QSqlRecord &rcd):IMacro(rcd){;}
    ~CppMacro(){;}

    void insertElement(ICodeElement *element);
    QStringList getValue();
};


//formula, combines multipule macros to build some complex codes lines!
class IFormula
{
protected:
    IFormula(){;}
public:
    IFormula(int id,int pos):m_id(id),m_pos(pos){;} //(int TemplateId , int Pos), Pos can not over temp length!
    IFormula(QSqlRecord &rcd){setByRecord(rcd);}
    virtual ~IFormula() = 0;

    IMacro *operator =(QSqlRecord &rcd){setByRecord(rcd);}
    int getID(){return m_id;}
    int getPos(){return m_pos;}
    QString getName(){return m_name;}

    virtual void insertElement(ICodeElement *elem) = 0;
    virtual void insertMacro(IMacro *macro) = 0;
    virtual QStringList getValue() = 0;

protected:
    int m_id;
    QString m_name;
    int m_pos;
    vector<ICodeElement*> m_elem;
    vector<IMacro*> m_macro;
    void setByRecord(QSqlRecord &rcd);
};

//single element means direct codes string ,
//and maybe with one or more macros,which will extend to an codes block;
class CppFormulaSingleElement:public IFormula
{
public:
    explicit CppFormulaSingleElement(int id, int pos):IFormula(id,pos){;}
    explicit CppFormulaSingleElement(QSqlRecord &rcd):IFormula(rcd){;}
    ~CppFormulaSingleElement(){;}

    void insertElement(ICodeElement *elem);
    void insertMacro(IMacro *macro);
    QStringList getValue();
private:
    QString getElemString();
};
}
#endif // IMACRO_H
