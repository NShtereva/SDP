#ifndef __VECTORITERATOR_HPP
#define __VECTORITERATOR_HPP

template <typename T>
class VectorIterator
{
    private:
        T* pointer;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;

        VectorIterator(T* pointer = nullptr);
        VectorIterator(const VectorIterator& other) = default;
        ~VectorIterator() = default;

        VectorIterator& operator = (const VectorIterator& other) = default;
        VectorIterator& operator = (T* pointer);

        operator bool() const;

        bool operator == (const VectorIterator& other) const;
        bool operator != (const VectorIterator& other) const;

        VectorIterator& operator += (const difference_type& movement);
        VectorIterator& operator -= (const difference_type& movement);
        VectorIterator& operator ++ ();
        VectorIterator& operator -- ();
        VectorIterator operator ++ (int);
        VectorIterator operator -- (int);
        VectorIterator operator + (const difference_type& movement) const;
        VectorIterator operator - (const difference_type& movement) const;

        difference_type operator - (const VectorIterator& other) const;

        T& operator * ();
        const T& operator * () const;

        T* operator -> ();
        const T* operator -> () const;
};

#include "vectorIterator.inl"

#endif
