#include <iostream>
#include <cmath>

void primeDivisors(int number)
{
    while(number % 2 == 0)
    {
        std::cout << 2 << " ";
        number = number / 2;
    }

    int root = sqrt(number);
    for(int i = 3; i <= root; i += 2)
    {
        while(number % i == 0)
        {
            std::cout << i << " ";
            number = number / i;
        }
    }

    if(number > 2)
        std::cout << number << " ";
}

int main()
{
    primeDivisors(24708);
    std::cout << std::endl;
    return 0;
}
