#ifndef __STACK_QUEUE
#define __STACK_QUEUE

#include <stdexcept>
#include <stack>

template <typename T>
class QueueWith2Stacks
{
    private:
        std::stack<T> leftStack;
        std::stack<T> rightStack;
        std::size_t queueSize;

    public:
        QueueWith2Stacks();

        void enqueue(const T& elem);
        T dequeue();

        void push(const T& elem);
        void pop();

        T& back();
        const T& back() const;

        size_t size() const;
        bool empty() const;
};

template <typename T>
QueueWith2Stacks<T>::QueueWith2Stacks() 
    : queueSize(0)
{ }

template <typename T>
void QueueWith2Stacks<T>::enqueue(const T& elem)
{
    this->leftStack.push(elem);
    this->queueSize++;
}

template <typename T>
T QueueWith2Stacks<T>::dequeue()
{
    if(this->empty())
    {
        throw std::logic_error("Empty queue!");
    }

    while(this->leftStack.size() > 1)
    {
        this->rightStack.push(this->leftStack.top());
        this->leftStack.pop();
    }

    T result = this->leftStack.top();
    this->leftStack.pop();

    while(!this->rightStack.empty())
    {
        this->leftStack.push(this->rightStack.top());
        this->rightStack.pop();
    }

    this->queueSize--;

    return result;
}

template <typename T>
void QueueWith2Stacks<T>::push(const T& elem)
{
    this->enqueue(elem);
}

template <typename T>
void QueueWith2Stacks<T>::pop()
{
    this->dequeue();
}

template <typename T>
T& QueueWith2Stacks<T>::back()
{
    if(this->empty())
    {
        throw std::logic_error("Empty queue!");
    }

    return this->leftStack.top();
}

template <typename T>
const T& QueueWith2Stacks<T>::back() const
{
    if(this->empty())
    {
        throw std::logic_error("Empty queue!");
    }
    
    return this->leftStack.top();
}

template <typename T>
size_t QueueWith2Stacks<T>::size()  const
{
    return this->queueSize;
}

template <typename T>
bool QueueWith2Stacks<T>::empty() const
{
    return this->queueSize == 0;
}

#endif
