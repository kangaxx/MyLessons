#include <iostream>

using namespace std;
class theMethod;

typedef int (*func)(int&,int&);
typedef int (theMethod::*member_func)(int &, int &);

int sum(int &a, int &b){a = a+b;return a;}
int swap(int &a, int &b){ a= a^b; b= a^b; a= a^b;return a;}

int totalMathod(int (*ptr)(int &,int &),int &a, int &b){
    return ptr(a,b);
}

class theMethod{
public:
    virtual int twoInt(int &a, int &b) = 0;
    static int Max(int &a, int &b);
};

class theMethodDerivedA:public theMethod
{
public:
    int twoInt(int &a, int &b){return a+b;}
};

class theMethodDerivedB:public theMethod
{
public:
    int twoInt(int &a, int &b){return a-b;}
};


int main()
{
    func normalFunc;
    member_func memFunc;
    int a,b,c,d;
    a= 1;
    b= 2;
    c= 2;
    d = 1;
    normalFunc = sum;
    cout << normalFunc(a,b) << endl;

    memFunc = &theMethod::twoInt;
    theMethod *m = new theMethodDerivedB;
    cout << (m->*memFunc)(c,d) << endl;
    return 0;
}

