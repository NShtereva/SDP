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

void allPrimes(const unsigned& n)
{
    for(int i = 2; i <= n; i++)
    {
        if(isPrime(i))
            std::cout << i << " ";
    }
}

int main()
{
    allPrimes(512);
    std::cout << std::endl;
    return 0;
}
