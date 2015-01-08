#include "dnifgenerator.h"
using namespace std;
DCodeGenerator* DCodeGenerator::sp_CgInstance = NULL;
string RemoveFlagTag(string tagStr, int tagSize)
{
    tagStr.erase(tagStr.begin(),tagStr.begin()+tagSize);
    tagStr.erase(tagStr.end()-tagSize,tagStr.end());
    return tagStr;
}
static vector<DCppTemplate::stc_Flag> sFindString(const char *source, const char *flagLeft, const char *flagRight,int length,int FlagSize)
{
    vector<DCppTemplate::stc_Flag> result;
    int b=-1,e=-1;

    for(int i = 0;i < length; i++)
    {
        if (strncmp(&source[i],flagLeft,FlagSize-1)==0)
        {
            if (e < 0)
            {
                b = i;
                i += FlagSize - 2;
            }
            else
            {

                b = -1;
                e = -1;
            }
        }
        else if (strncmp(&source[i],flagRight,FlagSize-1)==0)
        {
            if (b >= 0 && b < i)
            {
                DCppTemplate::stc_Flag temp;
                e = i+FlagSize-1;
                char *kk;

                kk = new char[e-b+1];
                memcpy(kk,&source[b],e-b);
                kk[e-b] ='\0';
                temp.Contain = kk;
                temp.Contain = RemoveFlagTag(temp.Contain,FlagSize-1);
                temp.beginPos = b;
                temp.endPos = e;
                result.push_back(temp);
                delete []kk;
                i += FlagSize - 2;
            }
            b = -1;
            e = -1;
        }
    }
    return result;
}

eCGFlagType GetFlagType(string flagStr)
{
    if (flagStr.length() <= 0)
        return CG_FLAG_NONE;
    vector<std::string> flagBegins;
    flagBegins.push_back(STR_CGFLAG_MACRO_BEGIN);
    flagBegins.push_back(STR_CGFLAG_FOMULE_BEGIN);

    for (auto Tag : flagBegins)
    {
        if (sFindString(flagStr.c_str(),Tag.c_str(),STR_CGFLAG_FLAGTYPE_END.c_str(),flagStr.length(),(STR_CGFLAG_FLAGTYPE_END.length()+1)).size()>0)
        {
            if (Tag == STR_CGFLAG_MACRO_BEGIN)
                return CG_FLAG_Macro;
            else if (Tag == STR_CGFLAG_FOMULE_BEGIN)
                return CG_FLAG_Fomule;
        }
    }
    return CG_FLAG_NONE;
}

vector<DCppTemplate::stc_Flag> FindMacroFlag(vector<DCppTemplate::stc_Flag> allFlag)
{
    vector<DCppTemplate::stc_Flag> result;
    for (auto Tag : allFlag)
    {
        if (GetFlagType(Tag.Contain) == CG_FLAG_Macro)
            result.push_back(Tag);
        cout << " in find macro : " << Tag.Contain << endl;
    }
    return result;
}

bool CheckFlagSequence(vector<DCppTemplate::stc_Flag> allFlag)
{
    for (int i=0;i<allFlag.size();i++)
    {
        if (allFlag[i].beginPos >= allFlag[i].endPos)
            return false;
        if (i < allFlag.size()-1)
            if (allFlag[i].endPos > allFlag[i+1].beginPos)
                return false;
    }
    return true;
}

string UpdateMacro(string source, DCodeMacro cm[], int MacroNum)
{
    string result;
    vector<DCppTemplate::stc_Flag> allFlag;
    char cl[3] = "/*";
    char cr[3] = "*/";
    allFlag = sFindString(source.c_str(),cl,cr,source.length(),sizeof(cr));
    vector<DCppTemplate::stc_Flag> macroFlag;
    macroFlag = FindMacroFlag(allFlag);
    if (!CheckFlagSequence(macroFlag))
        return source;
    int copyPos = 0;

    for (auto tf : macroFlag)
    {
        for (int i = 0; i < MacroNum; i++)
        {
            if (RemoveFlagTag(tf.Contain,STR_CGFLAG_FLAGTYPE_END.length()) == cm[i].CMName)
            {
                cout << "bp:" << tf.beginPos << " and ep:" << tf.endPos << endl;
                result += source.substr(copyPos,tf.beginPos-copyPos);
                result += cm[i].CMValue;
                copyPos = tf.endPos;
            }
        }
    }
    result += source.substr(copyPos,source.length() - copyPos);
    return result;
}



int main()
{

    FILE *f;
    f = fopen("/home/gxx/Codes/svndb/files/test.txt","r");
    if (!f)
        cout << "fopen error!" << endl;
    DCppTemplate cpp(f);

//    char c;
//    int n = 0;

//    char *x = new char[INT_MAX_TEMPLATESIZE];
//    int t = fread(x,sizeof(char),INT_MAX_TEMPLATESIZE,f);
//    string test(x);
//    cout << "file contain is : " << test;

//    char cl[3] = "/*";
//    char cr[3] = "*/";

//    vector<DCppTemplate::stc_Flag> dc = sFindString(x,cl,cr,t,sizeof(cr));
//    for (auto dct : dc)
//    {
//        int x = GetFlagType(dct.Contain);
//        cout << dct.Contain << " type is :" << x << endl;

//        cout << "flag after RemoveTag: " << RemoveFlagTag(dct.Contain,2) << endl;
//    }
//                0123456789012345678901234567890123456789012345678901234567890123456789
//    string test= "/*<mSomebody/>*/ have /*<mNum/>*/ /*<mSomething/>*/. /*<mSomebody/>*/ is a good boy.";
//    string test = "/*<mSomebody/>*//*<mNum/>*/ have /*<xNum/>*/ /*<mSomething/>*/.\n /*<mSomebody/>*/ is a good boy. ";
    DCodeMacro cm[3];
    cm[0].CMName = "Something";
    cm[0].CMValue = "Book";
    cm[1].CMName = "Somebody";
    cm[1].CMValue = "Tom";
    cm[2].CMName = "Num";
    cm[2].CMValue = "3";
    cout << "update!" << endl;
//    cout << UpdateMacro(test,cm,3)+ "ed" << endl;
    cout << cpp.UpdateMacro(cm,3) << "ed" << endl;

    return 0;
}

