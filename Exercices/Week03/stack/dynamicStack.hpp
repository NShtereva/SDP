#ifndef __DYNAMICSTACK_HPP
#define __DYNAMICSTACK_HPP

#include <exception>

template <typename T>
class DynamicStack
{
    private:
        static const std::size_t INITIAL_CAPACITY = 2;
        static const std::size_t INCREASE_STEP = 2;
        std::size_t capacity;
        std::size_t stackSize;
        T* stack;

        void copy(const DynamicStack& other);
        void deallocate();
        void resize();
        
    public:
        DynamicStack();
        DynamicStack(const DynamicStack& other);
        ~DynamicStack();

        DynamicStack& operator = (const DynamicStack& other);

        void push(T element);
        void pop();

        bool empty() const;
        std::size_t size() const;

        const T& top() const;        
};

template <typename T>
DynamicStack<T>::DynamicStack() 
    : stackSize(0)
{
    T* buffer = nullptr;

    try
    {
        buffer = new T[INITIAL_CAPACITY];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

    this->stack = buffer;
    this->capacity = INITIAL_CAPACITY;
}

template <typename T>
DynamicStack<T>::DynamicStack(const DynamicStack<T>& other)
{
    this->copy(other);
}

template <typename T>
DynamicStack<T>::~DynamicStack()
{
    this->deallocate();
}

template <typename T>
DynamicStack<T>& DynamicStack<T>::operator = (const DynamicStack<T>& other)
{
    if(this != &other)
    {
        this->deallocate();
        this->copy(other);
    }
    return *this;
}

template <typename T>
void DynamicStack<T>::copy(const DynamicStack& other)
{
    if(other.empty())
    {
        this->stack = nullptr;
        this->stackSize = 0;
        this->capacity = 0;

        return;
    }

    T* buffer = nullptr;

    try
    {
        buffer = new T[other.capacity];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

    std::size_t size = other.size;

    for(std::size_t i = 0; i < size; i++)
    {
        buffer[i] = other.stack[i];
    }

    this->stack = buffer;
    this->stackSize = size;
    this->capacity = other.capacity;
}

template <typename T>
void DynamicStack<T>::deallocate()
{
    delete[] this->stack;
    this->stack = nullptr;

    this->stackSize = 0;
    this->capacity = 0;
}

template <typename T>
void DynamicStack<T>::resize()
{
     T* buffer = nullptr;

    try
    {
        buffer = new T[this->capacity * INCREASE_STEP];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

    std::size_t size = this->stackSize;
    std::size_t capacity = this->capacity;

    for(std::size_t i = 0; i < size; i++)
    {
        buffer[i] = this->stack[i];
    }

    this->deallocate();

    this->stack = buffer;
    this->stackSize = size;
    this->capacity = capacity * INCREASE_STEP;
}

template <typename T>
void DynamicStack<T>::push(T element)
{
    if(this->stackSize + 1 > this->capacity)
    {
        this->resize();
    }

    this->stack[this->stackSize] = element;
    this->stackSize++;
}

template <typename T>
void DynamicStack<T>::pop()
{
    if(this->empty())
    {
        throw std::runtime_error("Empty stack!");
    }
    
    this->stackSize--;
}

template <typename T>
bool DynamicStack<T>::empty() const
{
    return this->stackSize == 0;
}

template <typename T>
std::size_t DynamicStack<T>::size() const
{
    return this->stackSize;
}

template <typename T>
const T& DynamicStack<T>::top() const
{
    if(this->empty())
    {
        throw std::logic_error("Empty stack!");
    }

    return this->stack[this->stackSize - 1];
}

#endif
