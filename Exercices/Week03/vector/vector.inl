#ifndef __VECTOR_INL
#define __VECTOR_INL

#include <cassert>
#include <exception>

template <typename T>
Vector<T>::Vector() : vector(nullptr), size(0), capacity(0)
{ }

template <typename T>
Vector<T>::Vector(size_t size, const T& value)
{
    T* buffer = nullptr;

    try
    {
        buffer = new T[size];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

    this->vector = buffer;
    this->size = size;
    this->capacity = size;

    for(int i = 0; i < size; i++)
    {
        this->vector[i] = value;
    } 
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
    this->copy(other);
}

template <typename T>
Vector<T>::~Vector()
{
    this->clear();
}

template <typename T>
Vector<T>& Vector<T>::operator = (const Vector<T>& other)
{
    if(this != &other)
    {
        this->clear();
        this->copy(other);
    }
    return *this;
}

template <typename T>
void Vector<T>::copy(const Vector<T>& other)
{
    if(other.empty())
    {
        this->vector = nullptr;
        this->size = 0;
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

    this->vector = buffer;
    this->size = other.size;
    this->capacity = other.capacity;

    for(int i = 0; i < this->size; i++)
    {
        this->vector[i] = other.vector[i];
    }
}

template <typename T>
void Vector<T>::deallocate()
{
    delete[] this->vector;
    this->vector = nullptr;
}

template <typename T>
VectorIterator<T> Vector<T>::begin() noexcept
{
    return VectorIterator<T>(this->vector);
}

template <typename T>
VectorIterator<const T> Vector<T>::begin() const noexcept
{
    return VectorIterator<const T>(this->vector);
}

template <typename T>
VectorIterator<const T> Vector<T>::cbegin() const noexcept
{
    return VectorIterator<const T>(this->vector);
}

template <typename T>
VectorIterator<T> Vector<T>::end() noexcept
{
    return VectorIterator<T>(this->vector + this->size);
}

template <typename T>
VectorIterator<const T> Vector<T>::end() const noexcept
{
    return VectorIterator<const T>(this->vector + this->size);
}

template <typename T>
VectorIterator<const T> Vector<T>::cend() const noexcept
{
    return VectorIterator<const T>(this->vector + this->size);
}

template <typename T>
size_t Vector<T>::getSize() const noexcept
{
    return this->size;
}

template <typename T>
size_t Vector<T>::getCapacity() const noexcept
{
    return this->capacity;
}

template <typename T>
bool Vector<T>::empty() const
{
    return this->size == 0;
}

template <typename T>
void Vector<T>::resize(size_t newSize, const T& defaultValue)
{
    if(newSize == 0)
    {
        this->clear();
        return;
    }

    T* buffer = nullptr;

    try
    {
        buffer = new T[newSize];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

    int limit = std::min(this->size, newSize);
    for(int i = 0; i < limit; i++)
    {
        buffer[i] = this->vector[i];
    }

    for(int i = limit; i < newSize; i++)
    {
        buffer[i] = defaultValue;
    }

    this->clear();

    this->vector = buffer;
    this->size = newSize;
    this->capacity = newSize;    
}

template <typename T>
void Vector<T>::reserve(size_t newCapacity)
{
    if(newCapacity <= this->capacity)
    {
        return;
    }

    T* buffer = nullptr;

    try
    {
        buffer = new T[newCapacity];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

    for(int i = 0; i < this->size; i++)
    {
        buffer[i] = this->vector[i];
    }

    this->deallocate();

    this->vector = buffer;
    this->capacity = newCapacity;   
}

template <typename T>
T& Vector<T>::operator [] (size_t pos)
{
    return this->vector[pos];
}

template <typename T>
const T Vector<T>::operator [] (size_t pos) const
{
    return this->vector[pos];
}

template <typename T>
T& Vector<T>::at(size_t pos)
{
    if(pos >= this->size)
    {
        throw std::out_of_range("Invalid index!");
    }
    return this->vector[pos];
}

template <typename T>
const T& Vector<T>::at(size_t pos) const
{
    if(pos >= this->size)
    {
        throw std::out_of_range("Invalid index!");
    }
    return this->vector[pos];
}

template <typename T>
T& Vector<T>::front()
{
    assert(!this->empty());
    return this->vector[0];
}

template <typename T>
const T& Vector<T>::front() const
{
    assert(!this->empty());
    return this->vector[0];
}

template <typename T>
T& Vector<T>::back()
{
    assert(!this->empty());
    return this->vector[this->size - 1];
}

template <typename T>
const T& Vector<T>::back() const
{
    assert(!this->empty());
    return this->vector[this->size - 1];
}

template <typename T>
T* Vector<T>::data() noexcept
{
    return this->vector;    
}

template <typename T>
const T* Vector<T>::data() const noexcept
{
    return this->vector;
}

template <typename T>
void Vector<T>::push_back(const T& element)
{
    if(this->size + 1 > this->capacity)
    {
        size_t capacity = (this->capacity == 0) ? INITIAL_CAPACITY : this->capacity * INCREASE_STEP;
        
        T* buffer = nullptr;

        try
        {
            buffer = new T[capacity];
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return;
        }

        for(int i = 0; i < this->size; i++)
        {
            buffer[i] = this->vector[i];
        }

        this->deallocate();
        
        this->vector = buffer;
        this->capacity = capacity;
    }

    this->vector[this->size] = element;
    this->size++;
}

template <typename T>
void Vector<T>::pop_back()
{
    if(!this->empty())
    {
        this->size--;
    }
}

template <typename T>
void Vector<T>::clear() noexcept
{
    this->deallocate();
    this->size = 0;
    this->capacity = 0;
}

template <typename U>
std::ostream& operator << (std::ostream& out, const Vector<U>& vector)
{
    for(int i = 0; i < vector.size; i++)
    {
        out << vector[i] << ' ';
    }
    return out;
}

#endif
