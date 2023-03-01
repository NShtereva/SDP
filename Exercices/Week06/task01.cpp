#include <iostream>
#include <cassert>

struct Element
{
    int data;
    Element* next;
};

void insertAfter(Element*& ptr, int num)
{
    if(!ptr)
    {
        return;
    }

    ptr->next = new Element{num, ptr->next};
    ptr = ptr->next;
}

void fillgaps(Element* ptr)
{
    Element* temp = ptr;

    while(temp->next)
    {
        int a = temp->data, 
            b = temp->next->data;

        if(std::abs(b - a) > 1)
        {
            for(int i = a + 1; i < b; i++)
            {
                insertAfter(temp, i);
            }
        }
        else
        {
            temp = temp->next;
        }
    }
}

void deallocate(Element*& ptr)
{
    while(ptr)
    {
        Element* save = ptr;
        ptr = ptr->next;
        delete save;
    }                      
}

int main()
{
    Element* ptr = new Element{1, 
                               new Element{3,
                                           new Element{4,
                                                       new Element{10, nullptr}}}};

    fillgaps(ptr);

    Element* temp = ptr;
    for(int i = 1; i <= 10; i++)
    {
        assert(temp->data == i);
        temp = temp->next;
    }

    deallocate(ptr);                   
    return 0;
}
