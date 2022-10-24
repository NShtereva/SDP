#include <iostream>

unsigned isPerfectNumber(const unsigned& number)
{
    unsigned sum = 1;
    for(int i = 2; i < number / 2 + 1; i++)
    {
        if(number % i == 0)
            sum += i;
    }
    return sum == number;
}

int main()
{
    std::cout << isPerfectNumber(6)
              << std::endl
              << isPerfectNumber(7)
              << std::endl
              << isPerfectNumber(28)
              << std::endl
              << isPerfectNumber(35)
              << std::endl
              << isPerfectNumber(8128)
              << std::endl;
    return 0;
} 
