#ifndef __LINKED_LIST_HPP
#define __LINKED_LIST_HPP

#include "lListIter.hpp"

#include <cassert>

template <typename T>
class LList
{
    private:
        struct Element
        {
            T data;
            Element* next;
        };

        friend class LListIterator<T>;

        Element *front, *back;

        void copy(const LList& other);
        void erase();

        LListIterator<T> findPrev(const LListIterator<T>& it);

        void divideHelper(Element*& prev, Element*& temp);
    
    public:
        LList();
        LList(const LList& other);
        ~LList();

        LList& operator = (const LList& other);

        bool empty() const;

        // включване на първи елемент
        bool insertFirst(const T& x);

        // включване на последен елемент
        bool insertLast(const T& x);

        // включване на елемент преди дадена позиция
        bool insertBefore(const T& x, const LListIterator<T>& pos);

        // включване на елемент след дадена позиция
        bool insertAfter(const T& x, const LListIterator<T>& pos);

        // изключване на първи елемент
        bool deleteFirst(T& x);

        // изключване на последен елемент
        bool deleteLast(T& x);

        // изключване на елемент преди дадена позиция
        bool deleteBefore(T& x, const LListIterator<T>& pos);

        // изключване на елемент на дадена позиция, унищавайки позицията
        bool deleteAt(T& x, LListIterator<T>& pos);

        // изключване на елемент след дадена позиция
        bool deleteAfter(T& x, const LListIterator<T>& pos);

        // константен достъп до елемент на дадена позиция
        const T& getAt(const LListIterator<T>& pos) const;

        // достъп до елемент на дадена позиция с възможност за промяна
        T& getAt(LListIterator<T>& pos);

        // връща позицията в началото
        LListIterator<T> begin() const;

        // връща позицията в края
        LListIterator<T> last() const;
 
        // връща позцията след края -> [begin; end)
        LListIterator<T> end() const;

        // задачи:
        void reverse();
        void removeRepeats();
        void unique();
        void append(LList& other);
        void divide(bool (*pred)(T));
};

template <typename T>
LList<T>::LList() : front(nullptr), back(nullptr)
{ }

template <typename T>
LList<T>::LList(const LList& other)  : front(nullptr), back(nullptr)
{
    this->copy(other);
}

template <typename T>
LList<T>::~LList()
{
    this->erase();
}

template <typename T>
LList<T>& LList<T>::operator = (const LList& other)
{
    if(this != &other)
    {
        this->erase();
        this->copy(other);
    }
    return *this;
}

template <typename T>
void LList<T>::copy(const LList& other)
{
    for(const T& x : other)
    {
        this->insertLast(x);
    }
}

template <typename T>
void LList<T>::erase()
{
    while(!this->empty())
    {
        T x;
        this->deleteLast(x);
    }
}

template <typename T>
LListIterator<T> LList<T>::findPrev(const LListIterator<T>& it)
{
    LListIterator<T> result = this->front;
    while(result.valid() && result.next() != it)
    {
        ++result;
    }
    return result;
}

template <typename T>
bool LList<T>::empty() const
{
    return this->front == nullptr;
}

template <typename T>
bool LList<T>::insertFirst(const T& x)
{
    if(this->empty())
    {
        this->front = this->back = new Element{x, nullptr};
        return true;
    }

    this->front = new Element{x, this->front};
    return true;
}

template <typename T>
bool LList<T>::insertLast(const T& x)
{
    if(this->empty())
    {
        this->front = this->back = new Element{x, nullptr};
        return true;
    }

    Element* temp = new Element{x, nullptr};
    this->back->next = temp;
    this->back = temp;
    temp = nullptr;

    return true;
}

template <typename T>
bool LList<T>::insertBefore(const T& x, const LListIterator<T>& pos)
{
    if(this->empty())
    {
        assert(!pos.valid());
    }

    if(pos == this->begin())
    {
        return this->insertFirst(x);
    }

    LListIterator<T> prev = this->findPrev(pos);
    return insertAfter(x, prev);
}

template <typename T>
bool LList<T>::insertAfter(const T& x, const LListIterator<T>& pos)
{
    if(this->empty())
    {
        this->front = this->back = new Element{x, nullptr};
        return true;
    }

    pos.ptr->next = new Element{x, pos.ptr->next};

    if (pos.ptr == this->back)
    {
        this->back = back->next;
    }
    return true;
}

template <typename T>
bool LList<T>::deleteFirst(T& x)
{
    if(this->empty())
    {
        return false;
    }
    
    Element* save = this->front;

    if(this->front->next)
    {
        this->front = this->front->next;
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
bool LList<T>::deleteLast(T& x)
{
    LListIterator<T> pos = this->last();
    return this->deleteAt(x, pos);
}

template <typename T>
bool LList<T>::deleteBefore(T& x, const LListIterator<T>& pos)
{
    if(this->empty() || pos.ptr == this->front || !pos.valid())
    {
        return false;
    }
    
    LListIterator<T> prev = this->findPrev(pos);
    return this->deleteAt(x, prev);
}

template <typename T>
bool LList<T>::deleteAt(T& x, LListIterator<T>& pos)
{
    if(this->empty() || !pos.valid())
    {
        return false;
    }

    LListIterator<T> prev = this->findPrev(pos);
    if(!prev.valid())
    {
        x = *pos;
        return this->deleteFirst(x);
    }

    pos = LListIterator<T>();
    return deleteAfter(x, prev);
}

template <typename T>
bool LList<T>::deleteAfter(T& x, const LListIterator<T>& pos)
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
    }

    pos.ptr->next = toDelete->next;
    x = toDelete->data;

    delete toDelete;
    return true;
}

template <typename T>
const T& LList<T>::getAt(const LListIterator<T>& pos) const
{
    if(!pos.valid())
    {
        throw std::runtime_error("Attempted access through an invalid position!");
    }
    return pos.get();
}

template <typename T>
T& LList<T>::getAt(LListIterator<T>& pos)
{
    if(!pos.valid())
    {
        throw std::runtime_error("Attempted access through an invalid position!");
    }
    return pos.get();
}

template <typename T>
LListIterator<T> LList<T>::begin() const
{
    return LListIterator<T>(this->front);
}

template <typename T>
LListIterator<T> LList<T>::last() const
{
    return LListIterator<T>(this->back);
}

template <typename T>
LListIterator<T> LList<T>::end() const
{
    return LListIterator<T>();
}

template <typename T>
void LList<T>::reverse()
{
    if(this->empty())
    {
        return;
    }

    Element* temp = this->front;
    while(temp->next)
    {
        Element* save = temp->next;
        temp->next = temp->next->next;
        
        save->next = this->front;
        this->front = save;
    }
}

template <typename T>
void LList<T>::removeRepeats()
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
            Element* save = temp->next;
            temp->next = temp->next->next;
            delete save;
        }
        else
        {
            temp = temp->next;
        }
    }
}

template <typename T>
void LList<T>::unique()
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
                Element* save = helper;
                helper = helper->next;
                prev->next = prev->next->next;
                delete save;
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
void LList<T>::append(LList& other)
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
void LList<T>::divideHelper(Element*& prev, Element*& temp)
{
    if(prev == this->front && temp == this->front)
    {
        this->front = this->front->next;
        this->back->next = prev;
        this->back = prev;
        prev->next = nullptr;

        temp = this->front;
        prev = temp;
    }
    else
    {
        prev->next = prev->next->next;
        this->back->next = temp;
        this->back = temp;
        temp->next = nullptr;
        temp = prev->next;
    }
}

template <typename T>
void LList<T>::divide(bool (*pred)(T))
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
