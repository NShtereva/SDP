#ifndef __CIRCULAR_LIST_ITERATOR
#define __CIRCULAR_LIST_ITERATOR

#include <stdexcept>

#include "circularList.hpp"

template <typename T>
T CircularList<T>::Iterator::operator * ()
{
    return this->pointer->data;
}

template <typename T>
const T& CircularList<T>::Iterator::operator * () const
{
    return this->pointer->data;
}

template <typename T>
T* CircularList<T>::Iterator::operator -> ()
{
    return this->pointer;
}

template <typename T>
bool CircularList<T>::Iterator::operator == (const CircularList<T>::Iterator& rhs) const
{
    return this->pointer == rhs.pointer;
}

template <typename T>
bool CircularList<T>::Iterator::operator != (const CircularList<T>::Iterator& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
typename CircularList<T>::Iterator& CircularList<T>::Iterator::operator ++ ()
{
    this->pointer = this->pointer->next;
    return *this;
}

template <typename T>
typename CircularList<T>::Iterator CircularList<T>::Iterator::operator ++ (int)
{
    CircularList<T>::Iterator result = *this;
    ++(*this);
    return result;
}

#endif
