#ifndef __LLITER_HPP
#define __LLITER_HPP

#include <stdexcept>

#include "lList.hpp"

template <typename T>
class LList;

template <typename T>
class LListIterator
{
    private:
        friend class LList<T>;

        typename LList<T>::Element* ptr;

    public:
        LListIterator(typename LList<T>::Element* _ptr = nullptr);

        // проверка за валидност на позицията
        bool valid() const;

        // константен достъп до елемента на позицията
        const T& get() const;

        // достъп до елемента на позицията с възможност за промяна
        T& get();

        // следваща позиция
        LListIterator next() const;

        // преместваме се на следващата позиция
        // ++it
        LListIterator& operator ++ ();
        // it++
        LListIterator operator ++ (int);

        operator bool() const;
        bool operator ! () const;

        bool operator == (const LListIterator& other) const;
        bool operator != (const LListIterator& other) const;
        
        const T& operator * () const;
        T& operator * ();
};

template <typename T>
LListIterator<T>::LListIterator(typename LList<T>::Element* _ptr) : ptr(_ptr)
{ }

template <typename T>
bool LListIterator<T>::valid() const
{
    return this->ptr != nullptr;
}

template <typename T>
const T& LListIterator<T>::get() const
{
    if(!this->valid())
    {
        throw std::runtime_error("Attempted access through an invalid position!");
    }
    return this->ptr->data;
}

template <typename T>
T& LListIterator<T>::get()
{
    if(!this->valid())
    {
        throw std::runtime_error("Attempted access through an invalid position!");
    }
    return this->ptr->data;
}

template <typename T>
LListIterator<T> LListIterator<T>::next() const
{
    if(!this->valid())
    {
        throw std::runtime_error("Attempt to move to an invalid position!");
    }
    return this->ptr->next;
}

template <typename T>
LListIterator<T>& LListIterator<T>::operator ++ ()
{
    return *this = next();
}

template <typename T>
LListIterator<T> LListIterator<T>::operator ++ (int)
{
    LListIterator<T> save = *this;
    ++*this;
    return save;
}

template <typename T>
LListIterator<T>::operator bool() const
{
    return this->valid();
}

template <typename T>
bool LListIterator<T>::operator ! () const
{
    return !this->valid();
}

template <typename T>
bool LListIterator<T>::operator == (const LListIterator& other) const
{
    return this->ptr == other.ptr;
}

template <typename T>
bool LListIterator<T>::operator != (const LListIterator& other) const
{
    return !(*this == other);
}

template <typename T>
const T& LListIterator<T>::operator * () const
{
    return this->get();
}

template <typename T>
T& LListIterator<T>::operator * ()
{
    return this->get();
}

#endif
