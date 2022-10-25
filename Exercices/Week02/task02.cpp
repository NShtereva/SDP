#include <iostream>

bool isDivisble(int x, int y)
{
    return x % y == 0;
}

int foo(const int* array, unsigned int size, bool (*isDivisble)(int, int))
{
    int counter = 0;

    for(int i = 0; i < size; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            counter += isDivisble(array[i], array[j]);
            counter += isDivisble(array[j], array[i]);
        }
    }

    return counter;
}

int main()
{
    int array[] = {1,2,3,4};
    unsigned int size = sizeof(array) / sizeof(array[0]);

    std::cout << foo(array, size, isDivisble) << std::endl; // -> 4
    return 0;
}
