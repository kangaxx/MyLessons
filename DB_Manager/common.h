#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <functional>

class Form;

template <class T>
class Property
{
public:
    Property(T t){m_Value = t;}
    Property()
    {
        //do nothing
    }
    ~Property(){}


    Property& operator =(Property& right)
    {
        if (this == &right)
            return *this;
        if (OnChange) OnChange();
        else if (OnChange_g) OnChange_g(*this);
        this->m_Value = right.m_Value;
        return *this;
    }

    operator T(void) const {return m_Value;}
    Property& operator =(T right)
    {
        this->m_Value = right;
        if (OnChange) OnChange();
        else if (OnChange_g) OnChange_g(*this);
        return *this;
    }

    Property& operator =(T *right)
    {
        if (right)
            this->m_Value = *right;
        if (OnChange) OnChange();
        else if (OnChange_g) OnChange_g(*this);
        return *this;
    }

    typedef std::function<void(Property&)> _GlobalEvent;
    _GlobalEvent OnChange_g;
    typedef std::function<void(void)> _Event;
    _Event OnChange;
private:
    T m_Value;
};


//it is the Demo Below

//using namespace std;

//void widthChange(Property<int> t){ cout << "change value to : "<< t << endl;}
//void widthChange2(){cout << "change mode 2 : " << endl;}
//class Form
//{
//public:
//    Form(){x = 3;width.OnChange = [&]{ ; cout << "x x x : " << x << endl;};}
//    Property<int> width;
//    void WidthChange(){cout << "width change to :" << width << endl;}
//    void changechange(){cout << "change change" << endl;}
//    int x;
//};

//int main()
//{

//    Property<int> width(2);
//    Property<int> Height(5);
//    width = 3;
//    Height = width;
//    cout << "height:" << Height << endl;
//    int * t = new int (4);
//    width = *t;
//    if (width == 3)
//        cout << width << endl;
//    width.OnChange_g = widthChange;
//    width = 5;
//    cout << width<< endl;
//    Form f;
//    f.width = 5;

//    cout << f.width << endl;
//    f.x = 5;
//    f.width = 10;
//    cout << f.width << endl;
//    return 0;
//}



#endif // COMMON_H
