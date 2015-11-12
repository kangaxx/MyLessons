#include "imacro.h"



lcg::IMacro::IMacro(QSqlRecord &rcd)
{
    setByRecord(rcd);

}

lcg::IMacro *lcg::IMacro::operator =(QSqlRecord &rcd)
{
    setByRecord(rcd);
    return this;
}

void lcg::IMacro::setByRecord(QSqlRecord &rcd)
{
    bool isInt;
    //field id
    ErrorMsg::message(QString("Create IMacro fail , no id!"),
                     rcd.contains(CHARS_MACRO_FIELDNAME_ID));
    m_id = rcd.field(CHARS_MACRO_FIELDNAME_ID).value().toInt(&isInt);
    ErrorMsg::message(QString("Create IMacro fail , id valid : ") +
                     rcd.field(CHARS_MACRO_FIELDNAME_ID).value().toString(),isInt);
    //field pos
    ErrorMsg::message(QString("Create IMacro fail , no pos!"),
                     rcd.contains(CHARS_MACRO_FIELDNAME_POS));
    m_pos = rcd.field(CHARS_MACRO_FIELDNAME_POS).value().toInt(&isInt);
    ErrorMsg::message(QString("Create IMacro fail , pos valid : ") +
                     rcd.field(CHARS_MACRO_FIELDNAME_POS).value().toString(),isInt);
    //field name
    ErrorMsg::message(QString("Create IMacro fail , no name!"),
                     rcd.contains(CHARS_MACRO_FIELDNAME_NAME));
    m_name = rcd.field(CHARS_MACRO_FIELDNAME_NAME).value().toString();
    ErrorMsg::message(QString("Create IMacro fail , pos valid : ") +
                     rcd.field(CHARS_MACRO_FIELDNAME_NAME).value().toString(),(m_name.size() > 0));
}

lcg::IMacro::~IMacro()
{
    //do nothing , but necessary
}






void lcg::CppMacro::insertElement(ICodeElement *element)
{
    this->m_elem.push_back(element);
}

QStringList lcg::CppMacro::getValue()
{
    QStringList rst;
    for (int i = 0;i<m_elem.size();i++)
        rst << m_elem.at(i)->getValue();
    return rst;
}


lcg::IFormula::~IFormula()
{
    //do nothing ,but necessary
}


void lcg::IFormula::setByRecord(QSqlRecord &rcd)
{
    bool isInt;
    //field id
    ErrorMsg::message(QString("Create IMacro fail , no id!"),
                     rcd.contains(CHARS_MACRO_FIELDNAME_ID));
    m_id = rcd.field(CHARS_MACRO_FIELDNAME_ID).value().toInt(&isInt);
    ErrorMsg::message(QString("Create IMacro fail , id valid : ") +
                     rcd.field(CHARS_MACRO_FIELDNAME_ID).value().toString(),isInt);
    //field pos
    ErrorMsg::message(QString("Create IMacro fail , no pos!"),
                     rcd.contains(CHARS_MACRO_FIELDNAME_POS));
    m_pos = rcd.field(CHARS_MACRO_FIELDNAME_POS).value().toInt(&isInt);
    ErrorMsg::message(QString("Create IMacro fail , pos valid : ") +
                     rcd.field(CHARS_MACRO_FIELDNAME_POS).value().toString(),isInt);
    //field name
    ErrorMsg::message(QString("Create IMacro fail , no name!"),
                     rcd.contains(CHARS_MACRO_FIELDNAME_NAME));
    m_name = rcd.field(CHARS_MACRO_FIELDNAME_NAME).value().toString();
    ErrorMsg::message(QString("Create IMacro fail , pos valid : ") +
                     rcd.field(CHARS_MACRO_FIELDNAME_NAME).value().toString(),(m_name.size() > 0));
}


void lcg::CppFormulaSingleElement::insertElement(ICodeElement *elem)
{
    ErrorMsg::message(QString("CppFormulaSingleElement::insertElement fail , m_elem.size : ")
                      +QString::number(m_elem.size())
                     ,(m_elem.size() == 0));


}

void lcg::CppFormulaSingleElement::insertMacro(IMacro *macro)
{
    m_macro.push_back(macro);
}



QStringList lcg::CppFormulaSingleElement::getValue()
{
    QStringList rst;
    return rst;
}

QString lcg::CppFormulaSingleElement::getElemString()
{
    combinerElemVector func;
    IElementCombiner *comber = new StringElementCombiner;
    return (comber->*func)(m_elem);
    delete comber;
}
