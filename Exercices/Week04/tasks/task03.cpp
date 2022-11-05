#include <iostream>

#include "../circularList/circularList.hpp"

int main()
{
    size_t N;
    std::cout << "N: ";
    std::cin >> N;

    CircularList<int> list;
    for(int i = 1; i <= N; i++)
    {
        list.push_back(i);
    }

    CircularList<int>::Iterator it = list.begin();
    while(list.size() > 1)
    {
        it = list.removeAfter(it);
    }

    std::cout << "Position: " << list.front() << std::endl;
    return 0;
}

/*
1 -> 2 -> ... -> N
^                |
|----------------|

N = 1, 2, 4, 8  -> 1
N = 3, 5, 9     -> 3
N = 6, 10       -> 5
N = 7           -> 7
*/