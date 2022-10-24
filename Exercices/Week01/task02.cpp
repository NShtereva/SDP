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

int main()
{
    std::cout << isPrime(-9) << std::endl
              << isPrime(0) << std::endl
              << isPrime(2) << std::endl
              << isPrime(3) << std::endl
              << isPrime(17) << std::endl
              << isPrime(21) << std::endl
              << isPrime(2147483647) << std::endl;
    return 0;
}
