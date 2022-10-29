#ifndef __STACK_HPP
#define __STACK_HPP

#include <exception>

template <typename T>
class Stack
{
    private:
        static const std::size_t CAPACITY = 128;
        std::size_t stackSize;

        T stack[CAPACITY];
        
    public:
        Stack();

        void push(T element);
        void pop();

        bool empty() const;
        std::size_t size() const;

        const T& top() const;        
};

template <typename T>
Stack<T>::Stack() : stackSize(0)
{ }

template <typename T>
void Stack<T>::push(T element)
{
    if(this->stackSize + 1 > this->CAPACITY)
    {
        throw std::runtime_error("Stack overflow!");
    }

    this->stack[this->stackSize] = element;
    this->stackSize++;
}

template <typename T>
void Stack<T>::pop()
{
    if(this->empty())
    {
        throw std::runtime_error("Empty stack!");
    }
    
    this->stackSize--;
}

template <typename T>
bool Stack<T>::empty() const
{
    return this->stackSize == 0;
}

template <typename T>
std::size_t Stack<T>::size() const
{
    return this->stackSize;
}

template <typename T>
const T& Stack<T>::top() const
{
    if(this->empty())
    {
        throw std::logic_error("Empty stack!");
    }
    
    return this->stack[this->stackSize - 1];
}

#endif
