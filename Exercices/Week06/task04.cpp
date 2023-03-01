#include <iostream>
#include <cassert>

template <typename T>
struct Element
{
    T data;
    Element* next;
};

template <typename T>
Element<T>* last(Element<T>* ptr)
{
    Element<T>* temp = ptr;
    while(temp->next)
    {
        temp = temp->next;
    }
    return temp;
}

template <typename T>
void insertAfter(Element<T>*& ptr, T num)
{
    if(!ptr)
    {
        return;
    }

    ptr->next = new Element<T>{num, ptr->next};
    ptr = ptr->next;
}

template <typename T>
void mirror(Element<T>*& ptr)
{
    Element<T>* originalEnd = last(ptr);
    Element<T>* copy = originalEnd;

    Element<T>* temp = ptr;

    while(temp != originalEnd)
    {
        insertAfter(copy, temp->data);
        temp = temp->next;
        copy = originalEnd;
    }

    insertAfter(copy, temp->data);
}

template <typename T>
void deallocate(Element<T>*& ptr)
{
    while(ptr)
    {
        Element<T>* save = ptr;
        ptr = ptr->next;
        delete save;
    }                      
}

int main()
{
    Element<int>* ptr = new Element<int>{1, 
                          new Element<int>{2,
                              new Element<int>{3, nullptr}}};

    mirror(ptr);

    Element<int>* temp = ptr;
    for(int i : {1,2,3,3,2,1})
    {
        assert(temp->data == i);
        temp = temp->next;
    }

    deallocate(ptr);        
    return 0;
}
