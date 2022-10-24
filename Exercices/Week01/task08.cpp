#include <iostream>
#include <cmath>

unsigned sumOfDigits(unsigned number)
{
    unsigned sum = 0;
    while(number != 0)
    {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

bool isASmithNumber(unsigned number)
{
    unsigned sum = sumOfDigits(number);

    unsigned sumOfDigitsOfDivisors = 0;
    while(number % 2 == 0)
    {
        sumOfDigitsOfDivisors += 2;
        number = number / 2;
    }

    int root = sqrt(number);
    for(int i = 3; i <= root; i += 2)
    {
        while(number % i == 0)
        {
            sumOfDigitsOfDivisors += sumOfDigits(i);
            number = number / i;
        }
    }

    if(number > 2)
        sumOfDigitsOfDivisors += sumOfDigits(number);
    
    return sum == sumOfDigitsOfDivisors;
}

int main()
{
    std::cout << isASmithNumber(6) 
              << std::endl
              << isASmithNumber(666)
              <<std::endl;
    return 0;
}
