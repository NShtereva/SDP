#ifndef __DLLITER_HPP
#define __DLLITER_HPP

#include <stdexcept>

#include "dLList.hpp"

template <typename T>
class DLList;

template <typename T>
class DLListIterator
{
    private:
        friend class DLList<T>;

        typename DLList<T>::Element* ptr;

    public:
        DLListIterator(typename DLList<T>::Element* _ptr = nullptr);

        // проверка за валидност на позицията
        bool valid() const;

        // константен достъп до елемента на позицията
        const T& get() const;

        // достъп до елемента на позицията с възможност за промяна
        T& get();

        // следваща позиция
        DLListIterator next() const;

        // предишна позиция
        DLListIterator prev() const;

        // преместваме се на следващата позиция
        // ++it
        DLListIterator& operator ++ ();
        // it++
        DLListIterator operator ++ (int);

        // преместваме се на предишната позиция
        // --it
        DLListIterator& operator -- ();
        // it--
        DLListIterator operator -- (int);

        operator bool() const;
        bool operator ! () const;

        bool operator == (const DLListIterator& other) const;
        bool operator != (const DLListIterator& other) const;
        
        const T& operator * () const;
        T& operator * ();
};

template <typename T>
DLListIterator<T>::DLListIterator(typename DLList<T>::Element* _ptr) : ptr(_ptr)
{ }

template <typename T>
bool DLListIterator<T>::valid() const
{
    return this->ptr != nullptr;
}

template <typename T>
const T& DLListIterator<T>::get() const
{
    if(!this->valid())
    {
        throw std::runtime_error("Attempted access through an invalid position!");
    }
    return this->ptr->data;
}

template <typename T>
T& DLListIterator<T>::get()
{
    if(!this->valid())
    {
        throw std::runtime_error("Attempted access through an invalid position!");
    }
    return this->ptr->data;
}

template <typename T>
DLListIterator<T> DLListIterator<T>::next() const
{
    if(!this->valid())
    {
        throw std::runtime_error("Attempt to move to an invalid position!");
    }
    return this->ptr->next;
}

template <typename T>
DLListIterator<T> DLListIterator<T>::prev() const
{
    if(!this->valid())
    {
        throw std::runtime_error("Attempt to move to an invalid position!");
    }
    return this->ptr->prev;
}

template <typename T>
DLListIterator<T>& DLListIterator<T>::operator ++ ()
{
    return *this = this->next();
}

template <typename T>
DLListIterator<T> DLListIterator<T>::operator ++ (int)
{
    DLListIterator<T> save = *this;
    ++*this;
    return save;
}

template <typename T>
DLListIterator<T>& DLListIterator<T>::operator -- ()
{
    return *this = this->prev();
}

template <typename T>
DLListIterator<T> DLListIterator<T>::operator -- (int)
{
    DLListIterator<T> save = *this;
    --*this;
    return save;
}

template <typename T>
DLListIterator<T>::operator bool() const
{
    return this->valid();
}

template <typename T>
bool DLListIterator<T>::operator ! () const
{
    return !this->valid();
}

template <typename T>
bool DLListIterator<T>::operator == (const DLListIterator& other) const
{
    return this->ptr == other.ptr;
}

template <typename T>
bool DLListIterator<T>::operator != (const DLListIterator& other) const
{
    return !(*this == other);
}

template <typename T>
const T& DLListIterator<T>::operator * () const
{
    return this->get();
}

template <typename T>
T& DLListIterator<T>::operator * ()
{
    return this->get();
}

#endif
