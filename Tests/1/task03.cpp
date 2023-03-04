#include <iostream>
#include <cassert>

template <class T>
struct Node 
{
    T data; 
    Node<T> *next;
};

template <class T>
void shuffle(Node<T>*& ptr, int N)
{
    int middle = (N % 2 == 0) ? (N / 2) : (N / 2 + 1);
    Node<T>* temp = ptr;

    while(middle > 1)
    {
        temp = temp->next;
        middle--;
    }

    while(temp->next)
    {
        Node<T>* save = temp->next;
        temp->next = temp->next->next;
        save->next = ptr;
        ptr = save;
    }
}

template <typename T>
void deallocate(Node<T>*& ptr)
{
    while(ptr)
    {
        Node<T>* save = ptr;
        ptr = ptr->next;
        delete save;
    }                      
}

int main()
{
    Node<int>* L1 = new Node<int>{1, 
                        new Node<int>{2,
                            new Node<int>{3, 
                                new Node<int>{4, nullptr}}}};

    int N1 = 4;

    shuffle(L1, N1);

    Node<int>* temp = L1;

    for(int i : {4,3,1,2})
    {
        assert(temp->data == i);
        temp = temp->next;    
    }

    deallocate(L1); 

    Node<int>* L2 = new Node<int>{1, 
                        new Node<int>{2,
                            new Node<int>{3, 
                                new Node<int>{4,
                                    new Node<int>{5, nullptr}}}}};

    int N2 = 5;

    shuffle(L2, N2);

    temp = L2;

    for(int i : {5,4,1,2,3})
    {
        assert(temp->data == i);
        temp = temp->next;    
    }

    deallocate(L2); 
    return 0;
}
