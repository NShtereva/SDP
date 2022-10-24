#include <iostream>
#include <cmath>

const size_t LIMIT = 31;

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

void mersenneNumbers(unsigned size)
{
    for(int p = 2; p <= LIMIT && size > 0; p++)
    {
        unsigned number = pow(2, p) - 1;
        if(isPrime(number))
        {
            std::cout << number << " ";
            size--;
        }
    }
    std::cout << std::endl;
}

int main()
{
    mersenneNumbers(8);
    return 0;
}
