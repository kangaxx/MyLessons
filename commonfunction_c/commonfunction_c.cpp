#include "commonfunction_c.h"
using namespace commonfunction_c;
int BaseFunctions::GetWorkPath(char *dest)
{
    if (dest == 0)
        return -1;
    int n = 0;
    n = readlink("/proc/self/exe" , dest , DEFAULT_LINUX_PATH_LENGTH);
    if(!( n > 0 && n < DEFAULT_LINUX_PATH_LENGTH))
       return -1;
    string FilePath(dest);
    int lastSlash = 0;
    if ((lastSlash = FilePath.find_last_of("/",FilePath.find_last_not_of("/")-1))<=1)
        return -1;
    dest[lastSlash]='\0';
    return n;
}

const char *BaseFunctions::getConfigPath(int mode)
{
    static char ConfigPath[DEFAULT_LINUX_PATH_LENGTH];
    if ((mode & FPM_SYSENV) == FPM_SYSENV){
        if (getSysEnvConfigPath(ConfigPath) != NULL)
            return ConfigPath;
    }
    return ConfigPath;
}

string BaseFunctions::GetParaByName(string fileName, string name)
{
    FILE *f;
    if ((f=fopen(fileName.c_str(),"r"))==0)
        throw string("Initial file not found! file name :") + fileName;
    char fileContent[MAX_INIFILE_LINE_LENGTH];
    int n = 0;
    while((n=freadLine(fileContent,sizeof(fileContent),f))>0)
    {
        n--;    //if '=' is the last char, will cause some out of range error;
        if (strncmp(fileContent,name.c_str(),name.length())==0)//got it!!
        {

            for (;n-->=0;)
            {

                if (fileContent[n] == CHAR_INIFILE_PARAMETER_SPLIT_FLAG)// find "=" in "password=123456"
                {
                    for(int i=0;n+i < MAX_INIFILE_LINE_LENGTH;i++)
                        fileContent[i] = fileContent[n+i+1];
                    fclose(f);
                    return string(fileContent);
                }
            }
        }
    }
    fclose(f);
    return string("");

}

string BaseFunctions::GetParaByLine(string fileName, int lineNum)
{

    FILE *f;
    if ((f=fopen(fileName.c_str(),"r"))==0)
        throw string("Initial file not found! file name :") + fileName;
    if (lineNum<1)
        throw "Error, GetParaByLine got incorrect lineNum";
    char fileContent[MAX_INIFILE_LINE_LENGTH];
    int n = 0;
    while((n=freadLine(fileContent,sizeof(fileContent),f))>0)
    {
        if (lineNum--==1)
        {
            fclose(f);
            return string(fileContent);
        }
    }
    fclose(f);
    return string("");
}

char *BaseFunctions::Int2Chars(int in, char *out, int size)
{
    if (size < 1 || size > DEFAULT_INTCHAR_SIZE)
        throw "Argument Size error : less than 1 or more than function limit!";
    if (out == NULL)
        throw "Error : Int2Chars argument out not allocate!";
    char *result = out;
    char *temp = out;
    memset(result,0,size);
    if ((double)in >= pow10(size) || in < 0) //In length must between 1 to size
        throw "Error : Int2Chars argument 'in' is error!";
    for(int j = size;j>0;j--)
    {
        int t = (in / ((int)pow10(j-1)))%10;
        if (t > 9 || t < 0)
            t = 0;
        *temp = t + 48;
        temp ++;
    }
    result[size] = '\0';
    return result;
}

int BaseFunctions::Chars2Int(const char *in, int size)
{
    if (size < 1 || size > DEFAULT_INTCHAR_SIZE)
        throw "Argument Size error : less than 1 or more than function limit!";
    if (in == NULL)
        throw "Error : Chars2Int argument out not allocate!";
    int result = 0;
    for (int k = 0; k < size; k++)
    {
        int t = int(in[k])-48;
        if (t > 9 || t < 0){
            size = k;
            break;
        }
    }
    for (int i = size - 1;i>=0;i--)
    {
        int t = *(in++) -48;
        if (t > 9 || t < 0)
            t = 0;
        result += t *((int)pow10(i));
    }
    return result;
}

int BaseFunctions::Str2Int(string s)
{
    if (s.size()< 1) throw "Error:commonfunction_c Str2Int get EMPTY string";  // 空字符串判断
    int i = 0;
    int result = 0;
    while (s[i] != '\0')  // 循环条件
    {
        if (s[i] == ' ') continue;  // 空格判断
        if (s[i] > '9' || s[i] < '0') throw "Error : commonfuction_c Str2Int get non-digital string"; //非数字判断
        result = result * 10 + (s[i] - '0');
        i++;
    }
    return result;
}

int BaseFunctions::Str2Int(string s, int i)
{
    try
    {
        int result = Str2Int(s);
        return result;
    }
    catch(...)
    {
        return i;
    }
}

string BaseFunctions::time2str(time_t time)
{
    char buf[DEFAULT_DATETIME_LEN];
    struct tm *tmp = localtime(&time);
    strftime(buf,DEFAULT_DATETIME_LEN,DEFAULT_DATETIME_FMT,tmp);

    string t_ = string(buf);
    while (t_.find('T')!= t_.npos)
        t_.replace(t_.find('T'),1," ");
    return t_;
}

time_t BaseFunctions::str2time(string str)
{
    tm tm_;
    int year, month, day, hour, minute,second;
    sscanf(str.c_str(),"%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    tm_.tm_year  = year-1900;
    tm_.tm_mon   = month-1;
    tm_.tm_mday  = day;
    tm_.tm_hour  = hour;
    tm_.tm_min   = minute;
    tm_.tm_sec   = second;
    tm_.tm_isdst = 0;

    time_t t_ = mktime(&tm_); //已经减了8个时区
    return t_; //秒时间
}

string BaseFunctions::cutValue(string wholeStr, string regExp)
{
    regex_t ex;

    int n;

    n = regcomp(&ex,regExp.c_str(),REG_NEWLINE|REG_EXTENDED); //complier
    if (n!= 0)
        throw "Error, commonfunction_c::cutValue fault in regcomp";

    regmatch_t match;
    n = regexec(&ex,wholeStr.c_str(),sizeof(match)/sizeof(regmatch_t),&match,REG_NOTBOL);
    if (n != 0)
        throw "Error, commonfunction_c::cutValue error ,or  regExp not found!";
    return wholeStr.substr(match.rm_so,match.rm_eo);

}

//getProcArgv: to get process argument, set *title to argu name ,like "-l" ,
//             it will try to match six mode successively, "-labc" , "-l=abc", "-l abc -other"
//             if matched , result is true , and dest will set to abc.
//             specially , "ls -l" or "ls -l -abc", still return true , dest set to '\0';
//             dest could be NULL if no or not need value;
bool BaseFunctions::getProcArgv(int argc, const char *argv[], const char *title, char *dest)
{
    if (argc < 0 || argv == NULL || title == NULL) return false;
    int t= 0;
    for (int i=0;i<argc;i++)
    {
        if ((t=strcmp_nonsafe(title,argv[i]))>0) //"-labc" or "-l=abc"
        {
            if (argv[i][t+1]== '=') //"-l=abc"
            {
                if (dest != NULL)
                    strcpy(dest,&(argv[i][t+2]));
            }
            else
            {
                if (dest != NULL)
                    strcpy(dest,&(argv[i][t+1]));
            }
            return true;
        }
        if (t==0) //"-l" or "-l abc"
        {
            if (i == argc -1 || argv[i+1][0] == '-') //"-l"
            {
                if (dest != NULL)
                   strcpy(dest,"");
            }
            else
            {
                if (dest != NULL)
                    strcpy(dest,&(argv[i+1][0]));
            }
            return true;
        }
    }
    return false;
}

char *BaseFunctions::getSysEnvConfigPath(char *dest)
{
    if (dest == NULL||getenv(CHARS_QMODEL_SYSENV_ROOT)==NULL)
        return NULL;
    strncpy(dest,getenv(CHARS_QMODEL_SYSENV_ROOT),DEFAULT_LINUX_PATH_LENGTH);
    if (access(dest,0) == -1)
        return NULL;
    return dest;
}

int BaseFunctions::freadLine(void *buffer, int size, FILE *f)
{
    if (!buffer)
        throw "Error : freadLine get an NULL buffer!";
    if (f == 0)
        throw "Error : freadLine need a opened file!";
    if (feof(f))
        throw "Error : freadLine get a file seek at feof!";
    int result=0;
    memset(buffer,'\0',size);
    for (;result<size;result++) //look, result added here!
    {
        char c;
        if (fread(&c,1,1,f)<1)
            break;
        if (isprint(c))
            ((char*)buffer)[result]=c;
        else
            break;
    }
    return result;
}

int BaseFunctions::strcmp_nonsafe(const char *c1, const char *c2)
{
    int rst = -1;
    if (c1 == NULL || c2 == NULL)
        return rst;
    while (*c1 != '\0')
    {
        if (*(c1++) != *(c2++))
            return -1; // c2 not include c1
        else
            rst++;
    }
    if (*c2 == '\0')
        return 0; //c2 == c1
    else
        return rst; //c2 include c1
}

template<class T>
int DuLink<T>::size(){
    int count = 0;
    for (Node *p=head->next;p!= head;p=p->next)
        count ++;
    return count;
}


template<class T>
void DuLink<T>::insertElement(T element, int pos){
    assert(pos > 0 && pos <= size()+1);
    Node *p = head;
    while(pos-- != 0)
        p=p->next;
    new Node(element,p->prior,p);

}

template<class T>
T &DuLink<T>::getElement(int idx){
    assert(idx>= 0 && idx<size());
    Node *p = head->next;
    while(idx-- != 0)
        p=p->next;
    return p->data;
}

template<class T>
T &DuLink<T>::operator [](int idx){
    return getElement(idx);
}

template<class T>
void DuLink<T>::clearAllElement(){
    Node *t,*p;
    p = head->next;
    while(p != head){
        t = p->next;
        delete p;
        p = t;
    }
}

template<class T>
T DuLink<T>::delElement(int idx){
    assert(idx >= 0 && idx < size());
    Node *t = head->next;
    while(idx-- != 0)
        t = t->next;
    t->prior->next = t->next;
    t->next->prior = t->prior;
    T ret = t->data;
    delete t;
    return ret;
}

template<class T>
DuLink<T>::~DuLink(){
    clearAllElement();
    if (head != NULL){
        delete head;
        head = NULL;
    }
}

template<class T>
void DuLink<T>::Traverse(void (*visit)(T &element)){
    Node *t = head->next;
    while(t != head){
        visit(t->data);
        t = t->next;
    }
}

template<class T>
void DuLink<T>::TraverseBack(void (*visit)(T &element)){
    Node *t = head->prior;
    while (t != head){
        visit(t->data);
        t= t->prior;
    }
}

template<class T>
void DuLink<T>::alterElement(const T &newElement, int idx){
    assert(idx >= 0 && idx < size());
    Node *t = head->next;
    while (idx-- != 0)
        t= t->next;
    t->data = newElement;
    return;
}





