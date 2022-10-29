#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <iostream>

#include "vectorIterator.hpp"

template <typename T>
class Vector
{
    private:
    static const size_t INITIAL_CAPACITY = 2;
        static const size_t INCREASE_STEP = 2;

        T* vector;
        size_t size;
        size_t capacity;

        void copy(const Vector& other);
        void deallocate();

    public:
        Vector();
        Vector (size_t size, const T& value = T());
        Vector(const Vector& other);
        ~Vector();

        Vector& operator = (const Vector& other);

        VectorIterator<T> begin() noexcept;
        VectorIterator<const T> begin() const noexcept;
        VectorIterator<const T> cbegin() const noexcept;
        VectorIterator<T> end() noexcept;
        VectorIterator<const T> end() const noexcept;
        VectorIterator<const T> cend() const noexcept;

        size_t getSize() const noexcept;
        size_t getCapacity() const noexcept;

        bool empty() const;

        void resize(size_t newSize, const T& defaultValue = T());
        void reserve(size_t newCapacity);

        T& operator [] (size_t pos);
        const T operator [] (size_t pos) const;

        T& at(size_t pos);
        const T& at(size_t pos) const;

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;

        T* data() noexcept;
        const T* data() const noexcept;

        void push_back(const T& element);
        void pop_back();

        void clear() noexcept;

        template <typename U>
        friend std::ostream& operator << (std::ostream& out, const Vector<U>& vector);
};

#include "vector.inl"

#endif
