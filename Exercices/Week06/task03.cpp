#include <iostream>
#include <cassert>

template <typename T>
struct Element
{
    T data;
    Element* next;
};

template <typename T>
bool dupsub(Element<T>* ptr, unsigned int k)
{
    Element<T>* temp = ptr;

    while(temp)
    {
        Element<T>* save = temp;
        Element<T>* helper = temp->next;
        int counter = 0;

        while(helper)
        {
            if(helper->data == temp->data)
            {
                counter++;
                temp = temp->next;
            }
            else
            {
                if(counter >= k)
                {
                    return true;
                }
                else
                {
                    counter = 0;
                    temp = save;
                }
            }
            helper = helper->next;
        }

        if(counter >= k)
        {
            return true;
        }

        temp = save->next;

    }

    return false;
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
    Element<int>* ptr1 = new Element<int>{1, 
                            new Element<int>{2,
                                new Element<int>{3,
                                    new Element<int>{4,
                                        new Element<int>{1, 
                                            new Element<int>{2,
                                                new Element<int>{5, nullptr}}}}}}};

    Element<int>* ptr2 = new Element<int>{1, 
                            new Element<int>{2,
                                new Element<int>{3,
                                    new Element<int>{3,
                                        new Element<int>{3, 
                                            new Element<int>{4, nullptr}}}}}};

    Element<int>* ptr3 = new Element<int>{1, 
                            new Element<int>{2,
                                new Element<int>{3,
                                    new Element<int>{8,
                                        new Element<int>{3, 
                                            new Element<int>{4, nullptr}}}}}};
    unsigned int k = 2;
    assert(dupsub(ptr1, k));
    assert(dupsub(ptr2, k));
    assert(!dupsub(ptr3, k));

    deallocate(ptr1);     
    deallocate(ptr2);
    deallocate(ptr3);              
    return 0;
}
