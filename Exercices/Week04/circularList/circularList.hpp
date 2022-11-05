#ifndef __CIRCULAR_LIST
#define __CIRCULAR_LIST

#include <stdexcept>

template <typename T>
class CircularList
{
    private:
        struct Node
        {
            T data;
            Node* next;
        };

        Node* head;
        Node* tail;
        std::size_t listSize;

        void copy(const CircularList& other);
        void deallocate();

    public:
        CircularList();
        CircularList(const CircularList& other);
        ~CircularList();

        CircularList& operator = (const CircularList& other);

        class Iterator
        {
            private:
                friend CircularList;

                Node* pointer;

                operator Node*() { return this->pointer; }
                operator const Node*() const { return this->pointer; }

            public:
                Iterator(Node* pointer = nullptr) : pointer(pointer) { }
                Iterator(const Iterator& other) = default;
                ~Iterator() = default;

                Iterator& operator = (const Iterator& other) = default;

                T operator * ();
                const T& operator * () const;
                T* operator -> ();

                bool operator == (const Iterator& rhs) const;
                bool operator != (const Iterator& rhs) const;

                Iterator& operator ++ ();
                Iterator operator ++ (int);
        };

        void push_front(const T& element);
        void push_back(const T& element);
        void pop_front();

        Iterator insertAfter(const Iterator& it, const T& element);
        Iterator removeAfter(const Iterator& it);

        Iterator begin() const;
        Iterator end() const;

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;

        std::size_t size() const;
        bool empty() const;
        void print() const;
};

#include "circularList.inl"
#include "circularListIterator.inl"

#endif
