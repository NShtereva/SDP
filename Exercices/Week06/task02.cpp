#include <iostream>
#include <cassert>

struct Element
{
    int data;
    Element* next;
};

int lastIndex(Element* ptr)
{
    int index = -1;

    Element* temp = ptr;
    while(temp)
    {
        index++;
        temp = temp->next;
    }

    return index;
}

void deleteAfter(Element*& ptr)
{
    if(!ptr || !ptr->next)
    {
        return;
    }

    Element* save = ptr->next;
    ptr->next = ptr->next->next;
    delete save;
}

void removeIdx(Element* ptr)
{
    int last = lastIndex(ptr),
        i = 0;

    Element* temp = ptr;
    Element* prev = ptr;

    while(temp)
    {
        if(temp->data == last - i)
        {
            deleteAfter(prev);
        }
        else
        {
            if(i != 0)
            {
                prev = prev->next;
            }
        }

        temp = prev->next;
        i++;
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
                               new Element{2,
                                           new Element{4,
                                                       new Element{0, nullptr}}}};

    removeIdx(ptr);

    Element* temp = ptr;
    for(int i : {1, 4})
    {
        assert(temp->data == i);
        temp = temp->next;
    }

    deallocate(ptr);                   
    return 0;
}
