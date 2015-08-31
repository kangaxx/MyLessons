#ifndef ICODEELEMENT_H
#define ICODEELEMENT_H
#include "common.h"
using namespace std;
namespace lcg{
//string type code element , easy set and get , base functions
class ICodeElement
{
public:
    virtual ~ICodeElement();
    virtual QString getValue() = 0;
    virtual void setValue(QString value) = 0;
protected:
    QString m_value;
};

//string type code element , easy set and get , base functions
class CodeElementString:public ICodeElement
{
public:
    explicit CodeElementString(){;}
    explicit CodeElementString(QString value){m_value=value;}
    void setValue(QString value){m_value=value;}
    QString getValue(){return m_value;}
};

//不同类别的元素在不同条件下按照不同的方式链接,这里是公共接口，有多少种元素就应该有多少种连接器
class IElementCombiner
{
public:
    IElementCombiner(){;}
    IElementCombiner(void *argv){this->m_argv = argv;}
    virtual ~IElementCombiner() = 0;
    virtual QStringList getCombinedString(ICodeElement *,int) = 0;
    virtual QStringList getCombinedString(vector<ICodeElement *>) = 0;
private:
    void *m_argv;
};

//string combiner easy to use .will always return one string
class StringElementCombiner:public IElementCombiner
{
public:
    StringElementCombiner():IElementCombiner(){;}
    StringElementCombiner(void *argv):IElementCombiner(argv){;}
    ~StringElementCombiner(){;}
    QStringList getCombinedString(ICodeElement *,int);
    QStringList getCombinedString(vector<ICodeElement *>);
};
}
#endif // ICODEELEMENT_H
