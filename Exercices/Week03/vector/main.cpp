#include <iostream>

#include "vectorTasks.hpp"

template <typename T>
void task1(const Vector<T>& v, const T& elem)
{
    VectorIterator<const T> it = find(v, elem);

    if(it != v.end())
    {
        std::cout << "Element " << *it << " has been found!" << std::endl;
    }
    else
    {
        std::cout << "Element " << elem << " not found!" << std::endl;
    }
}

template <typename T>
void task2(const Vector<T>& v)
{
    Vector<T> result = reverse(v);
    std::cout << result << std::endl;
}

template <typename T>
bool task3(const Vector<T>& v1, const Vector<T>& v2)
{
    return contains(v1, v2);
}

void square(int& num) 
{ 
    num *= num; 
}

template <typename T>
void task4(Vector<T>& v, void (*func)(T&))
{
    apply(v, func);
}

bool isEven(int num) 
{ 
    return num % 2 == 0; 
}

template <typename T>
Vector<T> task5(const Vector<T>& v, bool (*pred)(T))
{
    return filter(v, pred);
}

template <typename T>
VectorIterator<const T> task6(const Vector<T>& v, size_t k)
{
    return findKthLargest(v, k);
}

template <typename T>
Vector<T> task7(const Vector<T>& v)
{
    return getUnique(v);
}

int main()
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(5);
    v.push_back(6);
    v.push_back(2);
    v.push_back(0);

    std::cout << "vector: " << v << std::endl;

    std::cout << std::endl;
    task1(v, 9);
    task1(v, 2);

    std::cout << "\nreverse vector: ";
    task2(v);

    Vector<int> v1;
    v1.push_back(0);
    v1.push_back(5);
    v1.push_back(1);

    std::cout << "\n[ " << v << "]" << " conteins [ " << v1 << "]: " 
              << std::boolalpha << task3(v, v1) 
              << std::endl;

    v1.push_back(9);

    std::cout << "\n[ " << v << "]" << " conteins [ " << v1 << "]: " 
              << std::boolalpha << task3(v, v1) 
              << std::endl;

    v1 = v;
    std::cout << "\napply square: [ " << v1 << "]" << " -> [ ";
    task4(v1, square);
    std::cout << v1 << "]" << std::endl;

    std::cout << "\nfilter even: [ " << v << "] -> [ " 
              << task5(v, isEven) << "]" 
              << std::endl;

    VectorIterator<const int> it = task6(v, 3);
    if(*it)
    {
        std::cout << "\nthird largest: " << *it << std::endl;
    }
    else
    {
        std::cout << "\nIncorrect k or empty vector!" << std::endl;
    }

    std::cout << "\nunique: [ " << v << "] -> [ " 
              << task7(v) << "]" 
              << std::endl;

    v.push_back(6);
    v.push_back(1);
    v.push_back(0);

    std::cout << "\nunique: [ " << v << "] -> [ " 
              << task7(v) << "]" 
              << std::endl;
    return 0;
}
