#ifndef __VECTORITERATOR_INL
#define __VECTORITERATOR_INL

using difference_type = std::ptrdiff_t;

template <typename T>
VectorIterator<T>::VectorIterator(T* pointer) : pointer(pointer)
{ }

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator = (T* pointer)
{
    this->pointer = pointer;
    return *this;
}

template <typename T>
VectorIterator<T>::operator bool() const
{
    return this->pointer != nullptr;
}

template <typename T>
bool VectorIterator<T>::operator == (const VectorIterator<T>& other) const
{
    return this->pointer == other.pointer;
}

template <typename T>
bool VectorIterator<T>::operator != (const VectorIterator<T>& other) const
{
    return !(*this == other);
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator += (const difference_type& movement)
{
    this->pointer += movement;
    return *this;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator -= (const difference_type& movement)
{
    this->pointer -= movement;
    return *this;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator ++ ()
{
    ++this->pointer;
    return *this;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator -- ()
{
    --this->pointer;
    return *this;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator ++ (int)
{
    VectorIterator<T> result(*this);
    ++(*this);
    return result;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator -- (int)
{
    VectorIterator<T> result(*this);
    --(*this);
    return result;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator + (const difference_type& movement) const
{
    VectorIterator<T> result(*this);
    result += movement;
    return result;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator - (const difference_type& movement) const
{
    VectorIterator<T> result(*this);
    result -= movement;
    return result;
}

template <typename T>
difference_type VectorIterator<T>::operator - (const VectorIterator<T>& other) const
{
    return std::distance(other.pointer, this->pointer);
}

template <typename T>
T& VectorIterator<T>::operator * ()
{
    return *this->pointer;
}

template <typename T>
const T& VectorIterator<T>::operator * () const
{
    return *this->pointer;
}

template <typename T>
T* VectorIterator<T>::operator -> ()
{
    return this->pointer;
}

template <typename T>
const T* VectorIterator<T>::operator -> () const
{
    return this->pointer;
}

#endif
