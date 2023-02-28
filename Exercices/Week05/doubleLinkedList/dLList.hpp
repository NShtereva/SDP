#ifndef __DOUBLE_LINKED_LIST_HPP
#define __DOUBLE_LINKED_LIST_HPP

#include "dLListIter.hpp"

#include <cassert>

template <typename T>
class DLList
{
    private:
        struct Element
        {
            T data;
            Element* prev;
            Element* next;
        };

        friend class DLListIterator<T>;

        Element *front, *back;

        void copy(const DLList& other);
        void erase();

        void divideHelper(Element*& prev, Element*& temp);
    
    public:
        DLList();
        DLList(const DLList& other);
        ~DLList();

        DLList& operator = (const DLList& other);

        bool empty() const;

        // включване на първи елемент
        bool insertFirst(const T& x);

        // включване на последен елемент
        bool insertLast(const T& x);

        // включване на елемент преди дадена позиция
        bool insertBefore(const T& x, const DLListIterator<T>& pos);

        // включване на елемент след дадена позиция
        bool insertAfter(const T& x, const DLListIterator<T>& pos);

        // изключване на първи елемент
        bool deleteFirst(T& x);

        // изключване на последен елемент
        bool deleteLast(T& x);

        // изключване на елемент преди дадена позиция
        bool deleteBefore(T& x, const DLListIterator<T>& pos);

        // изключване на елемент на дадена позиция, унищавайки позицията
        bool deleteAt(T& x, DLListIterator<T>& pos);

        // изключване на елемент след дадена позиция
        bool deleteAfter(T& x, const DLListIterator<T>& pos);

        // константен достъп до елемент на дадена позиция
        const T& getAt(const DLListIterator<T>& pos) const;

        // достъп до елемент на дадена позиция с възможност за промяна
        T& getAt(DLListIterator<T>& pos);

        // връща позицията в началото
        DLListIterator<T> begin() const;

        // връща позицията в края
        DLListIterator<T> last() const;
 
        // връща позцията след края -> [begin; end)
        DLListIterator<T> end() const;

        // задачи:
        void reverse();
        void removeRepeats();
        void unique();
        void append(DLList& other);
        void divide(bool (*pred)(T));
};

template <typename T>
DLList<T>::DLList() : front(nullptr), back(nullptr)
{ }

template <typename T>
DLList<T>::DLList(const DLList& other) : front(nullptr), back(nullptr)
{
    this->copy(other);
}

template <typename T>
DLList<T>::~DLList()
{
    this->erase();
}

template <typename T>
DLList<T>& DLList<T>::operator = (const DLList& other)
{
    if(this != &other)
    {
        this->erase();
        this->copy(other);
    }
    return *this;
}

template <typename T>
void DLList<T>::copy(const DLList& other)
{
    for(const T& x : other)
    {
        this->insertLast(x);
    }
}

template <typename T>
void DLList<T>::erase()
{
    while(!this->empty())
    {
        T x;
        this->deleteLast(x);
    }
}

template <typename T>
bool DLList<T>::empty() const
{
    return this->front == nullptr;
}

template <typename T>
bool DLList<T>::insertFirst(const T& x)
{
    if(this->empty())
    {
        this->front = this->back = new Element{x, nullptr, nullptr};
        return true;
    }

    Element* temp = new Element{x, nullptr, this->front};
    this->front->prev = temp;
    this->front = temp;

    return true;
}

template <typename T>
bool DLList<T>::insertLast(const T& x)
{
    if(this->empty())
    {
        this->front = this->back = new Element{x, nullptr, nullptr};
        return true;
    }

    Element* temp = new Element{x, this->back, nullptr};
    this->back->next = temp;
    this->back = temp;
    temp = nullptr;

    return true;
}

template <typename T>
bool DLList<T>::insertBefore(const T& x, const DLListIterator<T>& pos)
{
    if(this->empty())
    {
        this->front = this->back = new Element{x, nullptr, nullptr};
        return true;
    }

    if(!pos.valid())
    {
        return false;
    }

    if(pos == this->begin())
    {
        return this->insertFirst(x);
    }

    return insertAfter(x, pos.prev());
}

template <typename T>
bool DLList<T>::insertAfter(const T& x, const DLListIterator<T>& pos)
{
    if(this->empty())
    {
        this->front = this->back = new Element{x, nullptr};
        return true;
    }

    if(!pos.valid())
    {
        return false;
    }

    if(pos.ptr->next)
    {
        Element* temp = new Element{x, pos.ptr, pos.ptr->next};
        pos.ptr->next->prev = temp;
        pos.ptr->next = temp;
    }
    else
    {
        return this->insertLast(x);
    }
    return true;
}

template <typename T>
bool DLList<T>::deleteFirst(T& x)
{
    if(this->empty())
    {
        return false;
    }
    
    Element* save = this->front;

    if(this->front->next)
    {
        this->front = this->front->next;
        this->front->prev = nullptr;
    }
    else
    {
        this->front = this->back = nullptr;
    }

    x = save->data;
    delete save;
    
    return true;
}

template <typename T>
bool DLList<T>::deleteLast(T& x)
{
    DLListIterator<T> pos = this->last();
    return this->deleteAt(x, pos);
}

template <typename T>
bool DLList<T>::deleteBefore(T& x, const DLListIterator<T>& pos)
{
    if(this->empty() || pos.ptr == this->front || !pos.valid())
    {
        return false;
    }
    
    DLListIterator<T> prev = pos.prev();
    return this->deleteAt(x, prev);
}

template <typename T>
bool DLList<T>::deleteAt(T& x, DLListIterator<T>& pos)
{
    if(this->empty() || !pos.valid())
    {
        return false;
    }

    DLListIterator<T> prev = pos.prev();
    if(!prev.valid())
    {
        x = *pos;
        return this->deleteFirst(x);
    }

    pos = DLListIterator<T>();
    return deleteAfter(x, prev);
}

template <typename T>
bool DLList<T>::deleteAfter(T& x, const DLListIterator<T>& pos)
{
    if(this->empty() || pos.ptr == this->back || !pos.valid())
    {
        return false;
    }

    Element* toDelete = pos.ptr->next;
    if(toDelete == nullptr)
    {
        return false;
    }

    if(toDelete == this->back)
    {
        this->back = pos.ptr;
        this->back->next = nullptr;
    }
    else
    {
        toDelete->next->prev = pos.ptr;
        pos.ptr->next = toDelete->next;
    }

    x = toDelete->data;
    delete toDelete;
    return true;
}

template <typename T>
const T& DLList<T>::getAt(const DLListIterator<T>& pos) const
{
    if(!pos.valid())
    {
        throw std::runtime_error("Attempted access through an invalid position!");
    }
    return pos.get();
}

template <typename T>
T& DLList<T>::getAt(DLListIterator<T>& pos)
{
    if(!pos.valid())
    {
        throw std::runtime_error("Attempted access through an invalid position!");
    }
    return pos.get();
}

template <typename T>
DLListIterator<T> DLList<T>::begin() const
{
    return DLListIterator<T>(this->front);
}

template <typename T>
DLListIterator<T> DLList<T>::last() const
{
    return DLListIterator<T>(this->back);
}

template <typename T>
DLListIterator<T> DLList<T>::end() const
{
    return DLListIterator<T>();
}

template <typename T>
void DLList<T>::reverse()
{
    if(this->empty() || !this->front->next)
    {
        return;
    }

    Element* originalEnd = this->back;

    while(this->front != originalEnd)
    {
        T x;
        this->deleteFirst(x);
        DLListIterator<T> pos = originalEnd;
        this->insertAfter(x, pos);
    }
}

template <typename T>
void DLList<T>::removeRepeats()
{
    if(this->empty())
    {
        return;
    }

    Element* temp = this->front;
    while(temp->next)
    {
        if(temp->data == temp->next->data)
        {
            T x;
            DLListIterator<T> pos = temp->next;
            this->deleteAt(x, pos);
        }
        else
        {
            temp = temp->next;
        }
    }
}

template <typename T>
void DLList<T>::unique()
{
    if(this->empty())
    {
        return;
    }

    Element* temp = this->front;
    Element* prev = temp;

    while(temp->next)
    {
        Element* helper = temp->next;
        while(prev->next)
        {
            if(temp->data == helper->data)
            {
                T x;
                DLListIterator<T> pos = helper;
                this->deleteAt(x, pos);

                helper = prev->next;
            }
            else
            {
                helper = helper->next;
                prev = prev->next;
            }
        }
        temp = temp->next;
        prev = temp;
    }
}

template <typename T>
void DLList<T>::append(DLList& other)
{
    if(other.empty())
    {
        return;
    }

    this->back->next = other.front;
    this->back = other.back;
    other.front = other.back = nullptr;
}

template <typename T>
void DLList<T>::divideHelper(Element*& prev, Element*& temp)
{
    if(prev == this->front && temp == this->front)
    {
        this->front = this->front->next;
        this->front->prev = nullptr;
        
        prev->prev = this->back;

        this->back->next = prev;
        this->back = prev;
        prev->next = nullptr;

        temp = this->front;
        prev = temp;
    }
    else
    {
        prev->next = prev->next->next;
        temp->prev = this->back;

        this->back->next = temp;
        this->back = temp;
        this->back->next = nullptr;

        temp = prev->next;
        temp->prev = prev;
    }
}

template <typename T>
void DLList<T>::divide(bool (*pred)(T))
{
    if(this->empty() || !this->front->next)
    {
        return;
    }

    Element* last = this->back;
    Element* temp = this->front;
    Element* prev = temp;

    while(temp != last)
    {
        if(pred(temp->data))
        {
            this->divideHelper(prev, temp);
        }
        else
        {
            if(temp != this->front)
            {
                prev = prev->next;
            }
            temp = temp->next;
        }
    }

    if(pred(temp->data))
    {
        this->divideHelper(prev, temp);
    }
}

#endif
