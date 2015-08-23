#include <iostream>
#include <assert.h>
using namespace std;
namespace dulink{
template<class T>
class DuLink{
private:
    class Node{
    public:
        T data;
        Node *prior;
        Node *next;
        Node(T &element,Node *prior, Node *next):data(element){this->next = next;this->prior = prior; prior->next=next->prior = this;}
        Node():data(data){}
    };
    Node *head;
public:
    DuLink():head(new Node()){head->prior=head->next=head;}
    int size();

    T &operator [](int idx);
    //判断是否为空链
    bool isEmpty()const{return head==head->next?true:false;}
    //将元素添加至最后，注意node的指针设置
    void addToLast(const T& element){Node* ne=new Node(element,head->prior,head);head->prior=head->prior->next=ne;}
    //获取最后一个元素
    T getLastElement()const{assert(!isEmpty());return head->prior->data;}
    //删除最后一个元素，注意node的指针设置
    void delLastElement(){assert(!isEmpty());Node* p=head->prior->prior;delete head->prior;head->prior=p;p->next=head;}
    //修改最后一个元素
    void alterLastEmlent(const T& newElement){assert(!isEmpty());head->prior->data=newElement;}
    //插入元素
    void insert(T element, int pos){insertElement(element, pos);}
    void insertElement(T element, int pos);
    //获取元素
    T &get(int idx){return getElement(idx);}
    T &getElement(int idx);
    //删除元素
    T del(int idx){return delElement(idx);}
    T delElement(int idx);
    //修改元素
    void alter(const T &newElement, int idx){alterElement(newElement,idx);}
    void alterElement(const T &newElement,int idx);
    //查找元素
    int findElement(const T& element) const;
    //正序遍历
    void Traverse(void (*visit)(T&element));
    //逆序遍历
    void TraverseBack(void (*visit)(T&element));
    //清空链表
    void clear(){clearAllElement();}
    void clearAllElement();
    //销毁链表
    ~DuLink();
};

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

}

class myNode{
public:
    myNode(){m_id = new int;}
    myNode(int id){m_id = new int; *m_id = id;}
    myNode(myNode &other){
        m_id = new int;
        *m_id = *(other.m_id);
    }
    myNode &operator =(myNode &right){
        if (this == &right)
            return right;
        this->setId(right.getId());
        return *this;
    }

    void setId(int i){*m_id = i;}
    int getId(){return *m_id;}

private:
    int *m_id;
};



int main()
{
    myNode n1(1);
    myNode n2(2);
    myNode n3(3);
    dulink::DuLink<myNode> l;
    l.insert(n1,1);
    l.insert(n2,2);
    l.insert(n3,3);
    cout << l.size() << endl;
    myNode t;
    t = l.getElement(0);
    cout << t.getId() << endl;
    cout << l[2].getId() << endl;
    return 0;
}

