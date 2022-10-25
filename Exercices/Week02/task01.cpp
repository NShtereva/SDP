#include <iostream>

int next(int x)
{
    return x + 3;
}

int sum(const int* array, unsigned int size, int (*next)(int))
{
    int sum = 0;
    for(int i = 0; i < size; i = next(i))
    {
        sum += array[i];
    }
    return sum;
}

int main()
{
    int array[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    unsigned int size = sizeof(array) / sizeof(array[0]);

    std::cout << sum(array, size, next) << std::endl; // -> 22
    return 0;
}
