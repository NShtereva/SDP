#include <iostream>
#include <cstring>

void sort(char** array, unsigned int size, bool (*pred)(const char*, const char*))
{
    for(int i = 0; i < size; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            if(pred(array[i], array[j]))
            {
                std::swap(array[i], array[j]);
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << std::endl;
    }
}

bool compare(const char* str1, const char* str2)
{
    return strcmp(str1, str2) > 0;
}

int main()
{
    char* array[] = {"i", "love", "eating", "pizza"};
    unsigned int size = sizeof(array) / sizeof(array[0]);

    sort(array, size, compare);
    return 0;
}
