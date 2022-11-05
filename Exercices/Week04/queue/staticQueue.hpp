#ifndef __STATIC_QUEUE
#define __STATIC_QUEUE

#include <stdexcept>

template <typename T>
class StaticQueue
{
    private:
        static const std::size_t CAPACITY = 100;

        T queue[CAPACITY];

        std::size_t frontIndex;
        std::size_t backIndex;
        std::size_t queueSize;

        bool full() const;

    public:
        StaticQueue();

        void enqueue(const T& elem);
        T dequeue();

        void push(const T& elem);
        void pop();

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;

        size_t size() const;
        bool empty() const;
};

template <typename T>
StaticQueue<T>::StaticQueue() 
    : frontIndex(0), backIndex(0), queueSize(0)
{ }

template <typename T>
void StaticQueue<T>::enqueue(const T& elem)
{
    if(this->full())
    {
        throw std::runtime_error("The queue is full!");
    }
    
    this->queue[this->backIndex++] = elem;
    if(this->backIndex >= CAPACITY)
    {
        this->backIndex %= CAPACITY;
    }

    this->queueSize++;
}

template <typename T>
T StaticQueue<T>::dequeue()
{
    if(this->empty())
    {
        throw std::logic_error("Empty queue!");
    }

    T result = this->queue[this->frontIndex++];
    if(this->frontIndex >= CAPACITY)
    {
        this->frontIndex %= CAPACITY;
    }

    this->queueSize--;

    return result;
}

template <typename T>
void StaticQueue<T>::push(const T& elem)
{
    this->enqueue(elem);
}

template <typename T>
void StaticQueue<T>::pop()
{
    this->dequeue();
}

template <typename T>
T& StaticQueue<T>::front()
{
    if(this->empty())
    {
        throw std::logic_error("Empty queue!");
    }

    return this->queue[this->frontIndex];
}

template <typename T>
const T& StaticQueue<T>::front() const
{
    if(this->empty())
    {
        throw std::logic_error("Empty queue!");
    }
    
    return this->queue[this->frontIndex];
}

template <typename T>
T& StaticQueue<T>::back()
{
    if(this->empty())
    {
        throw std::logic_error("Empty queue!");
    }

    return this->queue[this->backIndex - 1];
}

template <typename T>
const T& StaticQueue<T>::back() const
{
    if(this->empty())
    {
        throw std::logic_error("Empty queue!");
    }
    
    return this->queue[this->backIndex - 1];
}

template <typename T>
size_t StaticQueue<T>::size()  const
{
    return this->queueSize;
}

template <typename T>
bool StaticQueue<T>::empty() const
{
    return this->queueSize == 0;
}

template <typename T>
bool StaticQueue<T>::full() const
{
    return this->queueSize == CAPACITY;
}

#endif
