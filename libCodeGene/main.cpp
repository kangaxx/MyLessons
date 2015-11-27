#include <iostream>
#include <sqlfunctions.h>
#include <itemplatefile.h>
#include <icodegenedao.h>
#include <commonfunction_c.h>

using namespace std;
using namespace lcg;

int main()
{
    Connections conn;
    FSqlFactory *sql = &(SqlFunctions::Create(MYSQL,QString::fromLatin1(CHARS_SQL_INIFILE),QString::fromStdString(BaseFunctions::getConfigPath())));
    TemplateCPPFileDao dao(sql);
    cout << "Hello World!" << endl;
    delete sql;
    return 0;
}

