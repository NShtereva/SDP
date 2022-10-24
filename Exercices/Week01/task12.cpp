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

void nPerfectNumbers(unsigned n)
{
    int number = 1;
    while(n > 0)
    {
        if(isPerfectNumber(number))
        {
            std::cout << number << " ";
            n--;
        }
        number++;
    }
    std::cout << std::endl;
}

int main()
{
    nPerfectNumbers(5);
    return 0;
} 
