#include <iostream>

bool isEven(int x)
{
    return x % 2 == 0;
}

int* filter(const int* array, unsigned int size, bool (*pred)(int), unsigned int& newSize)
{
    for(int i = 0; i < size; i++)
    {
        if(pred(array[i]))
            newSize++;
    }

    int* newArray = new(std::nothrow) int[newSize];
    if(!newArray)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return nullptr;
    }

    int index = 0;
    for(int i = 0; i < size; i++)
    {
        if(pred(array[i]))
        {
            newArray[index] = array[i];
            index++;
        }
    }

    return newArray;
}

int main()
{
    int array1[] = {1,2,3,4,5};
    unsigned int size = sizeof(array1) / sizeof(array1[0]);

    unsigned int newSize = 0;
    int* array2 = filter(array1, size, isEven, newSize);

    std::cout << "new size: " << newSize << std::endl;

    std::cout << "new array: ";
    for(int i = 0; i < newSize; i++)
    {
        std::cout << array2[i] << " ";
    }
    std::cout << std::endl;

    delete[] array2;
    array2 = nullptr;
    return 0;
}
