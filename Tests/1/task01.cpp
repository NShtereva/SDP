#include <iostream>
#include <stdexcept>
#include <cassert>

template <class T>
struct Node 
{
    T data; 
    Node<T> *next;
};

template <class T>
T reduce(Node<T>* ptr, T (*F)(const T&, const T&))
{
    if(!ptr)
    {
        throw std::logic_error("Empty list!");
    }

    if(!ptr->next)
    {
        return ptr->data;
    }
    
    T temp = F(ptr->data, ptr->next->data);
    T result = temp;

    Node<T>* rest = ptr->next->next;
    while(rest)
    {
        result = F(temp, rest->data);
        temp = result;
        rest = rest->next;
    }

    return result;
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

double div(const double& x, const double& y)
{
    if(y == 0)
        throw std::invalid_argument("Division by 0!");

    if(x == 0)
        return 0;

    return x / y;
}

int main()
{
    Node<double>* L = new Node<double>{1024, 
                        new Node<double>{16,
                            new Node<double>{4, 
                                new Node<double>{2, nullptr}}}};

    assert(reduce(L, div) == 8);

    deallocate(L); 
    return 0;
}
