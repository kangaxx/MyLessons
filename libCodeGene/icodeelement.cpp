#include "icodeelement.h"





lcg::IElementCombiner::~IElementCombiner()
{
    //do nothing
}


QStringList lcg::StringElementCombiner::getCombinedString(ICodeElement *elem, int num)
{
    QStringList rst;
    QString temp;
    for (int i = 0;i<num;i++){
        temp += elem->getValue();
    }
    rst << temp;
    return rst;

}

QStringList lcg::StringElementCombiner::getCombinedString(vector<lcg::ICodeElement *> elem)
{
    QStringList rst;
    QString temp;
    for (int i = 0;elem.size();i++){
        temp += elem[i]->getValue();
    }
    rst << temp;
    return rst;
}
