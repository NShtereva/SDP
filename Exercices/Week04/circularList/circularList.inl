#ifndef __CIRCULAR_LIST_INL
#define __CIRCULAR_LIST_INL

#include "circularList.hpp"

template <typename T>
CircularList<T>::CircularList() 
    : head(nullptr), tail(nullptr), listSize(0)
{ }

template <typename T>
CircularList<T>::CircularList(const CircularList<T>& other)
{
    this->copy(other);
}

template <typename T>
CircularList<T>::~CircularList()
{
    this->deallocate();
}

template <typename T>
CircularList<T>& CircularList<T>::operator = (const CircularList<T>& other)
{
    if(this != &other)
    {
        this->deallocate();
        this->copy(other);
    }
    return *this;
}

template <typename T>
void CircularList<T>::copy(const CircularList<T>& other)
{
    if(other.empty())
    {
        return;
    }

    try
    {
        Node* curr = other.head;

        this->head = new Node{curr->data, nullptr};
        this->tail = head;

        curr = curr->next;

        while(curr != other.head)
        {
            this->push_back(curr->data);
            curr = curr->next;
        }
    }
    catch(const std::exception& e)
    {
        this->deallocate();
        throw;
    } 

    this->listSize = other.listSize;       
}

template <typename T>
void CircularList<T>::deallocate()
{
    while(!this->empty())
    {
        this->pop_front();
    }
}

template <typename T>
void CircularList<T>::push_front(const T& element)
{
    this->head = new Node{element, this->head};
    if(this->listSize == 0)
    {
        this->tail = this->head;
    }

    this->tail->next = this->head;
    this->listSize++;
}

template <typename T>
void CircularList<T>::push_back(const T& element)
{
    if(this->listSize == 0)
    {
        this->push_front(element);
        return;
    }

    Node* newNode = nullptr;

    try
    {
        newNode = new Node{element, this->head};
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

    this->tail->next = newNode;
    this->tail = this->tail->next;
    this->listSize++;
}

template <typename T>
void CircularList<T>::pop_front()
{
    if(this->empty())
    {
        throw std::logic_error("Empty list!");
    }

    Node* save = this->head;
    this->head = this->head->next;
    delete save;

    this->listSize--;

    if(this->listSize == 0)
    {
        this->tail = nullptr;
        this->head = nullptr;
    }
    else
    {
        this->tail->next = this->head;
    }
}

template <typename T>
typename CircularList<T>::Iterator CircularList<T>::insertAfter(const CircularList<T>::Iterator& it, const T& element)
{
    Node* newNode = new Node{element, it.pointer->next};
    it.pointer->next = newNode;

    this->listSize++;
    return newNode;
}

template <typename T>
typename CircularList<T>::Iterator CircularList<T>::removeAfter(const CircularList<T>::Iterator& it)
{
    if(this->empty())
    {
        throw std::logic_error( "Empty list!" );
    }

    if(this->listSize == 1)
    {
        delete it.pointer;
        return nullptr;
    }

    Node* removed = it.pointer->next;

    if(removed == this->tail)
    {
        this->tail = it.pointer;
    }

    if (removed == this->head)
    {
        this->head = this->head->next;
    }

    it.pointer->next = removed->next;
    delete removed;

    this->listSize--;
    if(this->listSize == 1)
    {
        return this->head ? this->head : this->tail;
    }

    return it.pointer->next;
}

template <typename T>
typename CircularList<T>::Iterator CircularList<T>::begin() const
{
    return CircularList<T>::Iterator(this->head);
}

template <typename T>
typename CircularList<T>::Iterator CircularList<T>::end() const
{
    return CircularList<T>::Iterator(this->tail);
}

template <typename T>
T& CircularList<T>::front()
{
    if(this->empty())
    {
        throw std::logic_error("Empty list!");
    }
    return this->head->data;
}

template <typename T>
const T& CircularList<T>::front() const
{
    if(this->empty())
    {
        throw std::logic_error("Empty list!");
    }
    return this->head->data;
}

template <typename T>
T& CircularList<T>::back()
{
    if(this->empty())
    {
        throw std::logic_error("Empty list!");
    }
    return this->tail->data;
}

template <typename T>
const T& CircularList<T>::back() const
{
    if(this->empty())
    {
        throw std::logic_error("Empty list!");
    }
    return this->tail->data;
}

template <typename T>
std::size_t CircularList<T>::size() const
{
    return this->listSize;
}

template <typename T>
bool CircularList<T>::empty() const
{
    return this->listSize == 0;
}

template <typename T>
void CircularList<T>::print() const
{
    if(!this->empty())
    {
        Node* curr = this->head;
        while(curr->next != this->head)
        {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
}

#endif
