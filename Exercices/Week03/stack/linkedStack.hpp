#ifndef __LINKEDSTACK_HPP
#define __LINKEDSTACK_HPP

#include <exception>

template <typename T>
class LinkedStack
{
    private:
        struct Node
        {
            T data;
            Node* next;
        };

        Node* stackTop;

        void copy(const LinkedStack& other);
        void erase();
        
    public:
        LinkedStack();
        LinkedStack(const LinkedStack& other);
        ~LinkedStack();

        LinkedStack& operator = (const LinkedStack& other);

        void push(T element);
        void pop();

        bool empty() const;

        const T& top() const;        
};

template <typename T>
LinkedStack<T>::LinkedStack() : stackTop(nullptr)
{ }

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& other)
{
    this->copy(other);
}

template <typename T>
LinkedStack<T>::~LinkedStack()
{
    this->erase();
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator = (const LinkedStack<T>& other)
{
    if(this != &other)
    {
        this->erase();
        this->copy(other);
    }
    return *this;
}

template <typename T>
void LinkedStack<T>::copy(const LinkedStack<T>& other)
{
    this->stackTop = new Node{other.stackTop->data, nullptr};

    Node* nextOther = other.stackTop->next;
    Node* currThis = this->stackTop;

    while(nextOther)
    {
        currThis->next = new Node{nextOther->data, nullptr};
        currThis = currThis->next;
        nextOther = nextOther->next;
    }
}

template <typename T>
void LinkedStack<T>::erase()
{
    while(!this->empty())
    {
        this->pop();
    }
}

template <typename T>
void LinkedStack<T>::push(T element)
{
    Node* newNode = nullptr;
    
    try
    {
        newNode = new Node{element, this->stackTop};
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    
    this->stackTop = newNode;    
}

template <typename T>
void LinkedStack<T>::pop()
{
    if(this->empty())
    {
        throw std::logic_error("Empty stack!");
    }

    Node* save = this->stackTop;
    this->stackTop = this->stackTop->next;
    delete save;
}

template <typename T>
bool LinkedStack<T>::empty() const
{
    return this->stackTop == nullptr;
}

template <typename T>
const T& LinkedStack<T>::top() const
{
    if(this->empty())
    {
        throw std::logic_error("Empty stack!");
    }

    return this->stackTop->data;
}

#endif
