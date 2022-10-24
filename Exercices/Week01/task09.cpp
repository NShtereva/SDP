#include <iostream>
#include <cmath>

bool isPrime(const int& number)
{
    if(number < 2)
        return false;

    if(number % 2 == 0)
        return number == 2;

    int root = sqrt(number);
    for(int i = 3; i <= root; i += 2)
    {
        if(number % i == 0)
            return false;
    }

    return true;
}

bool isMersenneNumber(unsigned number)
{
    bool isCorrectNumber = false;
    int limit = log2(number + 1);

    for(int p = 2; p <= limit && !isCorrectNumber; p++)
    {
        if(pow(2, p) - 1 == number)
            isCorrectNumber = true;
    }

    return isCorrectNumber && isPrime(number);
}

int main()
{
    std::cout << isMersenneNumber(2)
              << std::endl
              << isMersenneNumber(3)            // #1
              << std::endl      
              << isMersenneNumber(6)        
              << std::endl      
              << isMersenneNumber(31)           // #3
              << std::endl      
              << isMersenneNumber(127)          // #4
              << std::endl      
              << isMersenneNumber(8191)         // #5
              << std::endl
              << isMersenneNumber(2147483647)   // #8
              << std::endl;
    return 0;
}
