#ifndef __LINKED_QUEUE
#define __LINKED_QUEUE

#include <stdexcept>

template <typename T>
class LinkedQueue
{
    private:
        struct Node
        {
            T data;
            Node* next;
        };

        Node* head;
        Node* tail;
        std::size_t queueSize;

        void copy(const LinkedQueue& other);
        void deallocate();

    public:
        LinkedQueue();
        LinkedQueue(const LinkedQueue& other);
        ~LinkedQueue();

        LinkedQueue& operator = (const LinkedQueue& other);

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
LinkedQueue<T>::LinkedQueue() 
    : head(nullptr), tail(nullptr), queueSize(0)
{ }

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other)
{
    this->copy(other);
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    this->deallocate();
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator = (const LinkedQueue<T>& other)
{
    if(this != &other)
    {
        this->deallocate();
        this->copy(other);
    }
    return *this;
}

template <typename T>
void LinkedQueue<T>::copy(const LinkedQueue<T>& other)
{
    this->queueSize = 0;
    
    if(other.empty())
    {
        this->head = this->tail = nullptr;
        return;
    }    

    Node* curr = other.head;

    while(curr)
    {
        this->enqueue(curr->data);
        curr = curr->next;
    }
}

template <typename T>
void LinkedQueue<T>::deallocate()
{
    while(!this->empty())
    {
        this->dequeue(); 
    }
}

template <typename T>
void LinkedQueue<T>::enqueue(const T& elem)
{
    Node* newNode = nullptr;
    try
    {
        newNode = new Node{elem, nullptr};
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

    if(this->queueSize == 0)
    {
        this->head = this->tail = newNode;
        this->queueSize++;
        return;
    }
    
    this->tail->next = newNode;
    this->tail = tail->next;
    this->queueSize++;
}

template <typename T>
T LinkedQueue<T>::dequeue()
{
    if(this->empty())
    {
        throw std::logic_error("Empty queue!");
    }

    T result = this->head->data;

    Node* save = this->head;
    this->head = this->head->next;
    delete save;

    this->queueSize--;
    return result;
}

template <typename T>
void LinkedQueue<T>::push(const T& elem)
{
    this->enqueue(elem);
}

template <typename T>
void LinkedQueue<T>::pop()
{
    this->dequeue();
}

template <typename T>
T& LinkedQueue<T>::front()
{
    if(this->empty())
    {
        throw std::logic_error("Empty queue!");
    }

    return this->head->data;
}

template <typename T>
const T& LinkedQueue<T>::front() const
{
    if(this->empty())
    {
        throw std::logic_error("Empty queue!");
    }
    
    return this->head->data;
}

template <typename T>
T& LinkedQueue<T>::back()
{
    if(this->empty())
    {
        throw std::logic_error("Empty queue!");
    }

    return this->tail->data;
}

template <typename T>
const T& LinkedQueue<T>::back() const
{
    if(this->empty())
    {
        throw std::logic_error("Empty queue!");
    }
    
    return this->tail->data;
}

template <typename T>
size_t LinkedQueue<T>::size()  const
{
    return this->queueSize;
}

template <typename T>
bool LinkedQueue<T>::empty() const
{
    return this->queueSize == 0;
}

#endif
