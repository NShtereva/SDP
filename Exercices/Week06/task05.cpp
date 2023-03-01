#include <iostream>
#include <cassert>

struct Element
{
    int data;
    Element* next;
};

void removedups(Element* ptr)
{
    if(!ptr)
    {
        return;
    }

    Element* temp = ptr;
    Element* prev = temp;

    while(temp->next)
    {
        Element* helper = temp->next;
        while(prev->next)
        {
            if(temp->data == helper->data)
            {
                Element* save = helper;
                helper = helper->next;
                prev->next = prev->next->next;
                delete save;
            }
            else
            {
                helper = helper->next;
                prev = prev->next;
            }
        }
        temp = temp->next;
        prev = temp;
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
                        new Element{1,
                            new Element{2,
                                new Element{3, 
                                    new Element{3,
                                        new Element{3,
                                            new Element{4, nullptr}}}}}}};

    removedups(ptr);

    Element* temp = ptr;
    for(int i = 1; i <= 4; i++)
    {
        assert(temp->data == i);
        temp = temp->next;
    }

    deallocate(ptr);                   
    return 0;
}
