#include "vector.hpp"

template <typename T>
VectorIterator<const T> find(const Vector<T>& v, const T& elem)
{
    VectorIterator<const T> it = v.begin();
    for(; it != v.end(); ++it)
    {
        if(*it == elem)
        {
            return it;
        }
    }
    return v.end();
}

template <typename T>
Vector<T> reverse(const Vector<T>& v)
{
    size_t size = v.getSize();
    Vector<T> result(size);

    for(size_t i = 0; i < size; i++)
    {
        result[i] = v[size - i - 1];
    }

    return result;
}

template <typename T>
bool contains(const Vector<T>& v1, const Vector<T>& v2)
{
    size_t size1 = v1.getSize();
    size_t size2 = v2.getSize();

    for(size_t i = 0; i < size2; i++)
    {
        bool found = false;

        for(size_t j = 0; j < size1 && !found; j++)
        {
            if(v2[i] == v1[j])
            {
                found = true;
            }
        }

        if(!found)
        {
            return false;
        }
    }

    return true;
}

template <typename T>
void apply(Vector<T>& v, void (*func)(T&))
{
    size_t size = v.getSize();

    for(size_t i = 0; i < size; i++)
    {
        func(v.at(i));
    }
}

template <typename T>
Vector<T> filter(const Vector<T>& v, bool (*pred)(T))
{
    Vector<T> result;
    size_t size = v.getSize();
    
    for(size_t i = 0; i < size; i++)
    {
        if(pred(v[i]))
        {
            result.push_back(v[i]);
        }
    }

    return result;
}


template <typename T>
VectorIterator<const T> findKthLargest(const Vector<T>& v, size_t k)
{
    size_t size = v.getSize();

    if (k > size || v.empty())
    {
        return v.end();
    }

    Vector<T> temp(v);

    for(size_t i = 0; i < k; i++)
    {
        size_t maxIndex = i;

        for(size_t j = i; j < size; j++)
        {
            if(v[j] > v[maxIndex])
            {
                maxIndex = j;
            }
        }

        if(i != maxIndex)
        {
            std::swap(temp[i], temp[maxIndex]);
        }
    }

    const T& kthLargest = temp[k];
    return find(v, kthLargest);
}

template <typename T>
void sort(Vector<T>& v)
{
    size_t size = v.getSize();

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i + 1; j < size; j++)
        {
            if(v[i] > v[j])
            {
                std::swap(v[i], v[j]);
            }
        }
    }
}

template <typename T>
Vector<T> getUnique(const Vector<T>& v)
{
    Vector<T> temp(v);

    // std::sort(temp.begin(), temp.end()); // -> n*log(n)
    sort(temp); // n^2
    
    size_t tempSize = temp.getSize();
    Vector<int> unique;

    for (size_t i = 0; i < tempSize - 1; i++)
    {
        if(temp[i] != temp[i + 1])
        {
            unique.push_back(i);
            
            if(i == tempSize - 2)
            {
                unique.push_back(i + 1);
            }
        }

        while(temp[i] == temp[i + 1])
        {
            i++;
        }
    }

    size_t resultSize = unique.getSize();
    Vector<T> result;

    for (size_t i = 0; i < resultSize; i++)
    {
        result.push_back(temp[unique[i]]);
    }

    return result;
}
