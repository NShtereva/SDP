#include <iostream>

int plus1(int x)
{
    return x + 1;
}

void mapModify(int* array, unsigned int size, int (*operation)(int))
{
    for(int i = 0; i < size; i++)
    {
        array[i] = operation(array[i]);
    }
}

int* map(const int* array, unsigned int size, int (*operation)(int))
{
    int* newArray = new(std::nothrow) int[size];
    if(!newArray)
    {
        std::cout << "Memory not allocated successfully!" << std::endl;
        return nullptr;
    }

    for(int i = 0; i < size; i++)
    {
        newArray[i] = operation(array[i]);
    }

    return newArray;
}

void print(const int* array, unsigned int size)
{
    for(int i = 0; i < size; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int array1[] = {1,2,3,4,5};
    unsigned int size = sizeof(array1) / sizeof(array1[0]);

    mapModify(array1, size, plus1);
    print(array1, size);

    std::cout << "----------" << std::endl;

    int* array2 = map(array1, size, plus1);

    print(array1, size);
    print(array2, size);

    delete[] array2;
    array2 = nullptr;
    return 0;
}
